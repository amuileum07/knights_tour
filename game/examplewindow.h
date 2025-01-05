#ifndef EXAMPLEWINDOW_H
#define EXAMPLEWINDOW_H

#include <QWidget>
#include <QLineEdit>

class ExampleWindow : public QWidget
{
    Q_OBJECT

public:
    ExampleWindow(QWidget *parent = nullptr);

private slots:
    void onInputFieldClicked();

private:
    QLineEdit *inputField;
};

#endif // EXAMPLEWINDOW_H


