#ifndef QIPAN_H
#define QIPAN_H

#include <QWidget>

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
private:
    /* 棋盘的尺寸 */
    static const int m_boardSize = 15;
    /* 每个格子的大小 */
    static const int m_cellSize = 40;
    /* 边缘尺寸 */
    static const int m_margin = m_cellSize / 2;
};

#endif // QIPAN_H
