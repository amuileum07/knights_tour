#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel> 

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLineEdit *inputField;
    QLabel *label;
    int rows;
    int cols;

private slots:
    void onInputFieldClicked();
    void onInputFieldReturnPressed();
};

#endif // GAMEWINDOW_H