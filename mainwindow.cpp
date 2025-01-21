#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
