#include "gamewindow.h"
#include <QVBoxLayout>
#include <QLabel>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Game Window");
    showFullScreen();

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Enter the vertical and horizontal size of the chess board (ex. 10 10)", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    inputField = new QLineEdit(this);
    inputField->setAlignment(Qt::AlignCenter);
    inputField->setPlaceholderText("Enter the vertical and horizontal size of the chess board (ex. 10 10)");
    layout->addWidget(inputField);

    connect(inputField, &QLineEdit::selectionChanged, this, &GameWindow::onInputFieldClicked);
}

void GameWindow::onInputFieldClicked()
{
    inputField->clear();
}