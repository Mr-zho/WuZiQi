#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 设置程序的标题 */
    setWindowTitle("五子棋");

    m_qipan = new QiPan(this);

    /* 设置窗口的固定尺寸 */
    setFixedSize(800, 680);

    /* 设置布局 */
    QWidget * centerWidget = new QWidget(this);
    setCentralWidget(centerWidget);
    QVBoxLayout * layout = new QVBoxLayout(centerWidget);
    layout->addWidget(m_qipan);


    /* 信号和槽 */
    connect(m_qipan, &QiPan::chessClick, this, &MainWindow::handleChessClickSlot);
}

/* 槽函数 */
void MainWindow::handleChessClickSlot(int row, int col)
{
    m_qipan->setBoardInfo(row, col, PLAYER);

    /* 更新棋盘画面 */
    m_qipan->update();

    if (m_qipan->isCheckWin(row, col, PLAYER) == true)
    {
        QMessageBox::information(this, "游戏结束", "玩家获胜");
    }
    else
    {
        /* 人机下棋 */
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
