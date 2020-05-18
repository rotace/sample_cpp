#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    QByteArray datas = _socket.readAll();
    qDebug() << datas;
    _socket.write(QByteArray("ok !\n"));
}

void MainWindow::on_connectionBtn_clicked()
{
    switch(_socket.state())
    {
    case QAbstractSocket::UnconnectedState:
        _socket.connectToHost(QHostAddress("127.0.0.1"), 50000);
        connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        break;

    case QAbstractSocket::ConnectedState:
        _socket.disconnectFromHost();
        break;
    }
}
