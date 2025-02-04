#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qipan.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    /* 槽函数 */
    void handleChessClickSlot(int row, int col);
    void handleTimeoutSlot();
private:
    /* 人机下棋 */
    void computerMove();
    /* 评估该坐标对于棋手的影响因素 */
    int evaluateValue(int row, int col, Role role);
private:
    Ui::MainWindow *ui;

    /* 棋盘类 */
    QiPan * m_qipan;

    /* 延时落子定时器 */
    QTimer * m_timer;
    /* 延时落子坐标 */
    int m_delayRow;
    int m_delayCol;
};

#endif // MAINWINDOW_H
