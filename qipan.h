#ifndef QIPAN_H
#define QIPAN_H

#include <QWidget>
#include <QMouseEvent>



enum Role
{
    EMPTY,
    PLAYER,
    COMPUTER,
};

class QiPan : public QWidget
{
    Q_OBJECT
public:
    explicit QiPan(QWidget *parent = nullptr);

signals:

public slots:

protected:
    /* 绘图事件 */
    void paintEvent(QPaintEvent *event) override;
    /* 鼠标移动事件 */
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    /* 棋盘的尺寸 */
    static const int m_boardSize = 15;
    /* 每个格子的大小 */
    static const int m_cellSize = 40;
    /* 边缘尺寸 */
    static const int m_margin = m_cellSize / 2;

    /* 棋盘的棋子 */
    Role m_board[m_boardSize][m_boardSize];

    /* 维护上一次悬停点的坐标 */
    int m_hoverRow;
    int m_hoverCol;
    bool m_hoverFlag;
};

#endif // QIPAN_H
