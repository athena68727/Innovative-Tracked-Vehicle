#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "string"
#include "winsock2.h"
#include <QApplication>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
    QObject::connect(socket,&QTcpSocket::readyRead,this,&MainWindow::on_connectButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    socket->abort();
    socket->connectToHost("192.168.3.30", 1234);
    if(!socket->waitForConnected(30000))
    {
        ui->label->setText("连接失败，请重试！");
    }
    else
    {
        ui->label->setText("连接成功！");
    }
}

void MainWindow::on_upButton_pressed()
{
    socket->write("UPUP");
}

void MainWindow::on_upButton_released()
{
    socket->write("STOP");
}

void MainWindow::on_breakButton_clicked()
{
    socket->write("QUIT");
    ui->label->setText("未连接！");
}

void MainWindow::on_downButton_pressed()
{
    socket->write("DOWN");
}

void MainWindow::on_downButton_released()
{
    socket->write("STOP");
}

void MainWindow::on_leftButton_pressed()
{
    socket->write("LEFT");
}

void MainWindow::on_leftButton_released()
{
    socket->write("STOP");
}

void MainWindow::on_rightButton_pressed()
{
    socket->write("RIGHT");
}

void MainWindow::on_rightButton_released()
{
    socket->write("STOP");
}
