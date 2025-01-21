#include "qipan.h"
#include <QPainter>
#include <QColor>

QiPan::QiPan(QWidget *parent) : QWidget(parent)
{

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
}
