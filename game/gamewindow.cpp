#include "gamewindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), rows(0), cols(0)
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
        rows = dimensions[0].toInt(&ok1);
        cols = dimensions[1].toInt(&ok2);
        if (ok1 && ok2) {
            label->hide();
            inputField->hide();
            update(); // 체스판을 다시 그리기 위해 업데이트
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

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QRect rect(xOffset + j * cellSize, yOffset + i * cellSize, cellSize, cellSize);
                painter.fillRect(rect, (i + j) % 2 == 0 ? Qt::white : Qt::black);
            }
        }
    }
}