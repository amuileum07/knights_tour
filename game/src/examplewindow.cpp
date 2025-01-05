#include "examplewindow.h"
#include <QVBoxLayout>
#include <QLabel>

ExampleWindow::ExampleWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Example Window");
    setWindowState(Qt::WindowMaximized); // 전체 화면으로 전환하지만 제목 표시줄 유지

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Enter the vertical and horizontal size of the chess board (ex. 10 10)", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    inputField = new QLineEdit(this);
    inputField->setAlignment(Qt::AlignCenter);
    inputField->setPlaceholderText("Enter the vertical and horizontal size of the chess board (ex. 10 10)");
    layout->addWidget(inputField);

    connect(inputField, &QLineEdit::selectionChanged, this, &ExampleWindow::onInputFieldClicked);
}

void ExampleWindow::onInputFieldClicked()
{
    inputField->clear();
}