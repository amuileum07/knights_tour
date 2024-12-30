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
    QVBoxLayout *layout;
    QLabel *titleLabel;
    QPushButton *gameButton;
    QPushButton *exampleButton;

    void updateTitleFontSize();
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onGameClicked();
    void onExampleClicked();
};

#endif // MAINWINDOW_H