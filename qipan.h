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

public:
    /* 判断棋手是否获胜 */
    bool isCheckWin(int row, int col, Role role);

    /* 记录棋盘对应位置的玩家 */
    void setBoardInfo(int row, int col, Role role);
signals:
    /* 点击信号 */
    void chessClick(int row, int col);
public slots:

protected:
    /* 绘图事件 */
    void paintEvent(QPaintEvent *event) override;
    /* 鼠标移动事件 */
    void mouseMoveEvent(QMouseEvent *event) override;
    /* 鼠标按压事件 */
    void mousePressEvent(QMouseEvent *event) override;
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
