#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void tcpReadyRead();

    void on_pushButton_clicked();

    void reconnect();//连接host的函数

    void tcpConnect();
    void sendDa(void);


private:
    Ui::MainWindow *ui;
    QTcpSocket *mSocket;
    QTimer *mTimer;
    QTimer *mTimer2;
};
#endif // MAINWINDOW_H
