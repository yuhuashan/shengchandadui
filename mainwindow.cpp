 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket,SIGNAL(readyRead()),this,SLOT(tcpReadyRead()));


    mTimer = new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(reconnect()));//定时器时间到，执行重连
    connect(mSocket,SIGNAL(connected()),mTimer,SLOT(stop()));
    connect(mSocket,SIGNAL(disconnected()),mTimer,SLOT(start()));//socket断开后，定时器重新计时
    mTimer->start(2000);//500秒超时

    connect(mSocket,SIGNAL(connected()),this,SLOT(tcpConnect()));

}
//服务端到客户端 每一秒发送一次数据“11111”
void MainWindow::tcpConnect()
{
    mTimer2 = new QTimer(this);//来一次连接就new一个timer
    connect(mTimer2,SIGNAL(timeout()),this,SLOT(sendDa()));
    connect(mSocket,SIGNAL(disconnected()),mTimer2,SLOT(deleteLater()));
    //断开一次连接就delete 一次timer
    mTimer2->start(1000);
}


void MainWindow::sendDa()
{
    if(mSocket->state() == QAbstractSocket::UnconnectedState)
      return;
      mSocket->write("11111");

}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tcpReadyRead()
{
    ui->textEdit->append(mSocket->readAll());
}

void MainWindow::on_pushButton_clicked()
{
    if(mSocket->state() == QAbstractSocket::UnconnectedState)
        return;
    mSocket->write(ui->lineEdit->text().toLatin1());
}

void MainWindow::reconnect()
{
    if(mSocket->state() == QAbstractSocket::UnconnectedState)
    {
       //QDebug()<<"try to connectToHost";
       mSocket->connectToHost(QHostAddress::LocalHost,1234);
    }

}


