#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket* socket;

private slots:
    void on_connectButton_clicked();

    void on_upButton_pressed();

    void on_upButton_released();

    void on_breakButton_clicked();

    void on_downButton_pressed();

    void on_downButton_released();

    void on_leftButton_pressed();

    void on_leftButton_released();

    void on_rightButton_pressed();

    void on_rightButton_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
