#include "qipan.h"
#include <QPainter>
#include <QColor>
#include <QDebug>

QiPan::QiPan(QWidget *parent) : QWidget(parent)
{
    /* 初始化 */
    m_hoverRow = m_hoverCol = -1;
    m_hoverFlag = false;

    for (int row = 0; row < m_boardSize; row++)
    {
        for (int col = 0; col < m_boardSize; col++)
        {
            m_board[row][col] = EMPTY;
        }
    }

    /* 启动鼠标追踪 */
    setMouseTracking(true);
}


/* 绘图事件 */
void QiPan::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    /* 启动抗锯齿 - 平滑 */
    painter.setRenderHint(QPainter::Antialiasing);

    /* 绘制棋盘的背景 */
    QColor backGroundColor = QColor(118, 104, 154);
    painter.fillRect(rect(), backGroundColor);

    for (int idx = 0; idx < m_boardSize; idx++)
    {
        /* 绘制竖线 */
        painter.drawLine(m_margin + idx * m_cellSize, m_margin, m_margin + idx * m_cellSize, m_margin + (m_boardSize - 1) * m_cellSize);
        /* 绘制横线 */
        painter.drawLine(m_margin, m_margin + idx * m_cellSize, m_margin + (m_boardSize - 1) * m_cellSize, m_margin + idx * m_cellSize);
    }


    /* 绘制悬停点 */
    if (m_hoverFlag &&
        ((m_hoverRow >= 0) && (m_hoverRow < m_boardSize)) &&
        ((m_hoverCol >= 0) && (m_hoverCol < m_boardSize)) &&
         m_board[m_hoverRow][m_hoverCol] == EMPTY)
    {
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPoint(m_margin + m_hoverRow * m_cellSize, m_margin + m_hoverCol * m_cellSize), m_cellSize / 6, m_cellSize / 6);
    }

}


/* 鼠标移动事件 */
void QiPan::mouseMoveEvent(QMouseEvent *event)
{
    int row = (event->x() - m_margin + m_cellSize / 2) / m_cellSize;
    int col = (event->y() - m_margin + m_cellSize / 2) / m_cellSize;

    /* 判断鼠标书法都再棋盘内部 */
    if ((row >=0 && row < m_boardSize) && (col >= 0 && col < m_boardSize))
    {
        if (m_hoverRow != row || m_hoverCol != col)
        {
            m_hoverRow = row;
            m_hoverCol = col;

            m_hoverFlag = true;

            /* 更新棋盘画面 */
            update();
        }
    }
    else
    {
        /* 不在棋盘里面 */
        if (m_hoverFlag)
        {
            m_hoverFlag = false;

            m_hoverRow = m_hoverCol = -1;

            /* 更新绘画事件 */
            update();
        }
    }
}
