#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qipan.h"


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

private:
    /* 人机下棋 */
    void computerMove();
    /* 评估该坐标对于棋手的影响因素 */
    int evaluateValue(int row, int col, Role role);
private:
    Ui::MainWindow *ui;

    /* 棋盘类 */
    QiPan * m_qipan;
};

#endif // MAINWINDOW_H
