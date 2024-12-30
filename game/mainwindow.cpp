#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Knight's Tour");
    resize(600, 500);
    setStyleSheet("background-color: black;");

    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Knight's Tour", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; font-size: 48px;");
    layout->addWidget(titleLabel);

    gameButton = new QPushButton("Game", this);
    exampleButton = new QPushButton("Example", this);

    gameButton->setStyleSheet("background-color: darkgray; border: 1px solid white; color: black;");
    exampleButton->setStyleSheet("background-color: gray; border: 1px solid white; color: black;");
    layout->addWidget(gameButton);
    layout->addWidget(exampleButton);

    connect(gameButton, &QPushButton::clicked, this, &MainWindow::onGameClicked);
    connect(exampleButton, &QPushButton::clicked, this, &MainWindow::onExampleClicked);

    updateTitleFontSize();
}

void MainWindow::updateTitleFontSize()
{
    // Implement font size update logic here
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateTitleFontSize();
}

void MainWindow::onGameClicked()
{
    QMessageBox::information(this, "Game", "Game button clicked");
}

void MainWindow::onExampleClicked()
{
    QMessageBox::information(this, "Example", "Example button clicked");
}