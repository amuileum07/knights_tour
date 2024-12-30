#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <vector>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLineEdit *inputField;
    QLabel *label;
    int rows;
    int cols;
    int currentRow;
    int currentCol;
    int order;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> previousBoard;
    std::vector<int> di;
    std::vector<int> dj;

    void initializeBoard(int n1, int n2);
    void updateBoard();
    void solveFromCurrentPosition();

private slots:
    void onInputFieldClicked();
    void onInputFieldReturnPressed();
};

#endif // GAMEWINDOW_H