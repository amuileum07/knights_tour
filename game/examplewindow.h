#ifndef EXAMPLEWINDOW_H
#define EXAMPLEWINDOW_H

#include <QWidget>
#include <QLineEdit>

class ExampleWindow : public QWidget
{
    Q_OBJECT

public:
    ExampleWindow(QWidget *parent = nullptr);

private:
    QLineEdit *inputField;

private slots:
    void onInputFieldClicked();
};

#endif // EXAMPLEWINDOW_H