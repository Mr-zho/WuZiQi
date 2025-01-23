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
    Ui::MainWindow *ui;

    /* 棋盘类 */
    QiPan * m_qipan;
};

#endif // MAINWINDOW_H
