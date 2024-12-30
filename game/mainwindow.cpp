#include "mainwindow.h"
#include "gamewindow.h"
#include "examplewindow.h"
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Knight's Tour");
    resize(600, 500);
    setStyleSheet("background-color: black;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("Knight's Tour", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white;");
    mainLayout->addWidget(titleLabel);

    gameButton = new QPushButton("Game", this);
    exampleButton = new QPushButton("Example", this);

    gameButton->setStyleSheet("background-color: darkgray; border: 1px solid white; color: black;");
    exampleButton->setStyleSheet("background-color: gray; border: 1px solid white; color: black;");
    
    gameButton->setMinimumHeight(150); // 세로 크기 증가
    exampleButton->setMinimumHeight(150); // 세로 크기 증가
    gameButton->setMaximumWidth(300); // 가로 길이 증가
    exampleButton->setMaximumWidth(300); // 가로 길이 증가

    mainLayout->addWidget(gameButton);
    mainLayout->addWidget(exampleButton);

    connect(gameButton, &QPushButton::clicked, this, &MainWindow::onGameClicked);
    connect(exampleButton, &QPushButton::clicked, this, &MainWindow::onExampleClicked);

    updateTitleFontSize();
}

void MainWindow::updateTitleFontSize()
{
    int windowHeight = height();
    int fontSize = windowHeight / 10; // 폰트 크기를 윈도우 높이의 1/10로 설정
    QFont font = titleLabel->font();
    font.setPointSize(fontSize);
    titleLabel->setFont(font);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateTitleFontSize();
}

void MainWindow::onGameClicked()
{
    GameWindow *gameWindow = new GameWindow();
    gameWindow->show();
    this->close();
}

void MainWindow::onExampleClicked()
{
    ExampleWindow *exampleWindow = new ExampleWindow();
    exampleWindow->show();
    this->close();
}