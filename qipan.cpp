#include "qipan.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMessageBox>

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

    /* 绘制棋子 */
    for (int row = 0; row < m_boardSize; row++)
    {
        for (int col = 0; col < m_boardSize; col++)
        {
            if (m_board[row][col] == PLAYER)
            {
                painter.setBrush(Qt::black);
                painter.drawEllipse(QPoint(m_margin + row * m_cellSize, m_margin + col * m_cellSize), m_cellSize / 3, m_cellSize / 3);
            }
            else if (m_board[row][col] == COMPUTER)
            {
                painter.setBrush(Qt::white);
                painter.drawEllipse(QPoint(m_margin + row * m_cellSize, m_margin + col * m_cellSize), m_cellSize / 3, m_cellSize / 3);
            }
        }
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



/* 鼠标按压事件 */
void QiPan::mousePressEvent(QMouseEvent *event)
{
    int row = (event->x() - m_margin + m_cellSize / 2) / m_cellSize;
    int col = (event->y() - m_margin + m_cellSize / 2) / m_cellSize;

    /* 判断(row,col)是否在棋盘中 */
    if ((row >=0 && row < m_boardSize) && (col >= 0 && col < m_boardSize) && m_board[row][col] == EMPTY)
    {
        m_board[row][col] = PLAYER;

        /* 更新画面 - 绘图事件 */
        update();

        if (isCheckWin(row, col, PLAYER) == true)
        {
            QMessageBox::information(this, "游戏结束", "玩家获胜");
        }
    }
}



/* 判断棋手是否获胜 */
bool QiPan::isCheckWin(int row, int col, Role role)
{
    /* 四个方向 */
    int directions[4][2] =
    {
        {1, 0},     /* 水平方向 */
        {0, 1},     /* 竖直方向 */
        {1, -1},    /* 左上右下 */
        {1, 1},    /* 左下右上 */
    };


    /* 遍历每一个方向 */
    for (int direct = 0; direct < 4; direct++)
    {
        /* 计数 */
        int cnt = 1;

        /* 向一个方向去遍历 */
        for (int idx = 1; idx < 5; idx++)
        {
            int newRow = row + directions[direct][0] * idx;
            int newCol = col + directions[direct][1] * idx;

            if ((newRow >=0 && newRow < m_boardSize) && (newCol >= 0 && newCol < m_boardSize) && m_board[newRow][newCol] == role)
            {
                cnt++;
            }
            else
            {
                break;
            }
        }

        /* 向相反的方向探测 */
        for (int idx = 1; idx < 5; idx++)
        {
            int newRow = row - directions[direct][0] * idx;
            int newCol = col - directions[direct][1] * idx;

            if ((newRow >=0 && newRow < m_boardSize) && (newCol >= 0 && newCol < m_boardSize) && m_board[newRow][newCol] == role)
            {
                cnt++;
            }
            else
            {
                break;
            }
        }

        if (cnt >= 5)
        {
            return true;
        }
    }
    return false;
}
