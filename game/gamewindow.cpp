#include "gamewindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdint.h>

// XorShift-based random number generator from https://en.wikipedia.org/wiki/Xorshift
static inline uint32_t xorshift32(uint32_t *state) 
{
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

static inline void num_ofcase(std::vector<std::vector<int>>& board, int size, int i, int j, int move[8], int di[], int dj[]) 
{
    for (int a = 0; a <= 7; a++) 
    {
        int ni = i + di[a];
        int nj = j + dj[a];
        
        int cnt = 0;
        if (ni >= 0 && ni < size && nj >= 0 && nj < size && board[ni][nj] == 0) 
        {
            for (int b = 0; b < 8; b++) 
            {
                int mi = ni + di[b];
                int mj = nj + dj[b];
                if (mi >= 0 && mi < size && mj >= 0 && mj < size && board[mi][mj] == 0) cnt += 1;
            }
        }
        move[a] = cnt;
    }
}

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), rows(0), cols(0), currentRow(-1), currentCol(-1), order(1)
{
    setWindowTitle("Knight Tour Game");
    setWindowState(Qt::WindowMaximized); // 전체 화면으로 전환하지만 제목 표시줄 유지

    QVBoxLayout *layout = new QVBoxLayout(this);

    label = new QLabel("Enter the vertical and horizontal size of the chess board (ex. 10 10)", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    inputField = new QLineEdit(this);
    inputField->setAlignment(Qt::AlignCenter);
    inputField->setPlaceholderText("Enter the vertical and horizontal size of the chess board (ex. 10 10)");
    layout->addWidget(inputField);

    connect(inputField, &QLineEdit::selectionChanged, this, &GameWindow::onInputFieldClicked);
    connect(inputField, &QLineEdit::returnPressed, this, &GameWindow::onInputFieldReturnPressed);

    di = {-2, -2, -1, -1, 1, 1, 2, 2};
    dj = {-1, 1, -2, 2, -2, 2, -1, 1};
}

void GameWindow::initializeBoard(int n1, int n2)
{
    rows = n1;
    cols = n2;
    board.resize(rows);
    for (int i = 0; i < rows; ++i) {
        board[i].resize(cols);
        std::fill(board[i].begin(), board[i].end(), 0);
    }
    previousBoard = board;
}

void GameWindow::updateBoard()
{
    previousBoard = board;
    update();
}

void GameWindow::solveFromCurrentPosition()
{
    std::vector<int> move(8);
    uint32_t rng_state = static_cast<uint32_t>(time(nullptr));

    while (true) {
        num_ofcase(board, rows, currentRow, currentCol, move.data(), di.data(), dj.data());

        int min = 9, min_a = -1;
        for (int a = 0; a <= 7; a++) {
            if (move[a] < min && move[a] > 0) {
                min = move[a];
                min_a = a;
            } else if (move[a] == min) {
                int val = xorshift32(&rng_state) % 2;
                if (val) {
                    min = move[a];
                    min_a = a;
                }
            }
        }

        if (min_a == -1) {
            for (int a = 0; a <= 7; a++) {
                int ni = currentRow + di[a];
                int nj = currentCol + dj[a];
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == 0) {
                    board[ni][nj] = order++;
                    break;
                }
            }
            break;
        }

        currentRow += di[min_a];
        currentCol += dj[min_a];
        board[currentRow][currentCol] = order++;
        updateBoard();
    }
}

void GameWindow::onInputFieldClicked()
{
    inputField->clear();
}

void GameWindow::onInputFieldReturnPressed()
{
    QString text = inputField->text();
    QStringList dimensions = text.split(" ");
    if (dimensions.size() == 2) {
        bool ok1, ok2;
        int n1 = dimensions[0].toInt(&ok1);
        int n2 = dimensions[1].toInt(&ok2);
        if (ok1 && ok2) {
            label->hide();
            inputField->hide();
            initializeBoard(n1, n2);
            updateBoard();
        }
    }
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (rows > 0 && cols > 0) {
        QPainter painter(this);
        int cellSize = qMin(width() / cols, height() / rows);
        int boardWidth = cellSize * cols;
        int boardHeight = cellSize * rows;
        int xOffset = (width() - boardWidth) / 2;
        int yOffset = (height() - boardHeight) / 2;

        QVector<QPoint> knightPath(rows * cols, QPoint(-1, -1));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QRect rect(xOffset + j * cellSize, yOffset + i * cellSize, cellSize, cellSize);
                if (board[i][j] == 1) {
                    painter.fillRect(rect, Qt::red);
                } else if (board[i][j] == -2) {
                    painter.fillRect(rect, Qt::green);
                } else {
                    painter.fillRect(rect, (i + j) % 2 == 0 ? Qt::white : Qt::black);
                }
                painter.drawRect(rect);

                if (board[i][j] > 0) {
                    knightPath[board[i][j] - 1] = rect.center();
                }
            }
        }

        painter.setPen(QPen(Qt::blue, 2));
        for (int i = 0; i < knightPath.size() - 1; ++i) {
            if (knightPath[i] != QPoint(-1, -1) && knightPath[i + 1] != QPoint(-1, -1)) {
                painter.drawLine(knightPath[i], knightPath[i + 1]);
            }
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if (rows > 0 && cols > 0) {
        int cellSize = qMin(width() / cols, height() / rows);
        int boardWidth = cellSize * cols;
        int boardHeight = cellSize * rows;
        int xOffset = (width() - boardWidth) / 2;
        int yOffset = (height() - boardHeight) / 2;

        int x = event->x();
        int y = event->y();

        int col = (x - xOffset) / cellSize;
        int row = (y - yOffset) / cellSize;

        if (col >= 0 && col < cols && row >= 0 && row < rows) {
            if (board[row][col] == 0) {
                board[row][col] = order++;
                currentRow = row;
                currentCol = col;
                for (int k = 0; k < 8; ++k) {
                    int ni = row + di[k];
                    int nj = col + dj[k];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == 0) {
                        board[ni][nj] = -2;
                    }
                }
            } else if (board[row][col] == -2) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (board[i][j] == -2) {
                            board[i][j] = 0;
                        }
                    }
                }
                board[row][col] = order++;
                currentRow = row;
                currentCol = col;
                for (int k = 0; k < 8; ++k) {
                    int ni = row + di[k];
                    int nj = col + dj[k];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == 0) {
                        board[ni][nj] = -2;
                    }
                }
            } else {
                QMessageBox::warning(this, "Invalid Move", "You cannot move to this position.");
                return;
            }
            updateBoard();
        }
    }
}