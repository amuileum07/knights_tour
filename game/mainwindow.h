#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QPushButton *gameButton;
    QPushButton *exampleButton;

private slots:
    void onGameClicked();
    void onExampleClicked();
    void updateTitleFontSize();
    void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINWINDOW_H