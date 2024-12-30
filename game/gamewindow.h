#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLineEdit>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);

private:
    QLineEdit *inputField;

private slots:
    void onInputFieldClicked();
};

#endif // GAMEWINDOW_H