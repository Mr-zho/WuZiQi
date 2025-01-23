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

/* 评估该坐标对于棋手的影响因素 */
int MainWindow::evaluateValue(int row, int col, Role role)
{
    /* 考虑连子数 */
    /* 考虑开放端 */
    int score = 0;

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
        /* 连子数量 */
        int cnt = 0;
        /* 开放端 */
        int openEnd = 0;

        /* 向一个方向的正方向探测 */
        for (int idx = 1; idx < 5; idx++)
        {
            int newRow = row + directions[direct][0] * idx;
            int newCol = col + directions[direct][1] * idx;

            /* 保证新的坐标在棋盘中 */
            if ((newRow >= 0 && newRow < m_qipan->getBoardSize()) && (newCol > 0 && newCol < m_qipan->getBoardSize()))
            {
                if (m_qipan->getBoardInfo(newRow, newCol) == role)
                {
                    cnt++;
                }
                else if (m_qipan->getBoardInfo(newRow, newCol) == EMPTY)
                {
                    openEnd++;
                    break;
                }
                else
                {
                    break;
                }
            }
        }


        /* 向一个方向的反方向探测 */
        for (int idx = 1; idx < 5; idx++)
        {
            int newRow = row - directions[direct][0] * idx;
            int newCol = col - directions[direct][1] * idx;

            /* 保证新的坐标在棋盘中 */
            if ((newRow >= 0 && newRow < m_qipan->getBoardSize()) && (newCol > 0 && newCol < m_qipan->getBoardSize()))
            {
                if (m_qipan->getBoardInfo(newRow, newCol) == role)
                {
                    cnt++;
                }
                else if (m_qipan->getBoardInfo(newRow, newCol) == EMPTY)
                {
                    openEnd++;
                    break;
                }
                else
                {
                    break;
                }
            }
        }


        if (cnt == 4 && openEnd > 0)
        {
            score = 1000;
        }
        else if (cnt == 3 && openEnd > 0)
        {
            score = 100;
        }
        else if (cnt == 2 && openEnd > 0)
        {
            score = 10;
        }
        else if (cnt == 1 && openEnd > 0)
        {
            score = 1;
        }
    }

    return  score;
}


/* 人机下棋 */
void MainWindow::computerMove()
{
    int maxValue = -1;
    int bestRow = -1;
    int bestCol = -1;

    for (int row = 0; row < m_qipan->getBoardSize(); row++)
    {
        for (int col = 0; col < m_qipan->getBoardSize(); col++)
        {
            if (m_qipan->getBoardInfo(row, col) == EMPTY)
            {
                /* 人机能在这个地方下棋 */
                int score = evaluateValue(row, col, COMPUTER) + evaluateValue(row, col, PLAYER);
                if (score > maxValue)
                {
                    maxValue = score;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }

    m_qipan->setBoardInfo(bestRow, bestCol, COMPUTER);
    /* 更新棋盘的画面 */
    m_qipan->update();


    if (m_qipan->isCheckWin(bestRow, bestCol, COMPUTER) == true)
    {
        QMessageBox::information(this, "游戏结束", "人机获胜");
    }
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
        computerMove();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
