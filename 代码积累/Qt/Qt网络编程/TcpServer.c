#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>
TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    //初始化服务器server对象
    mServer = new QTcpServer();
    //关联客户端连接信号newConnection
    connect(mServer,SIGNAL(newConnection()),this,SLOT(new_client())); //连接客户端
    //启动服务器监听
    mServer->listen(QHostAddress::Any,9988);

}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::new_client()
{
    qDebug()<<"新客户段连接";
    mSocket = mServer->nextPendingConnection();//与客户端通信的套接字
    //关联接收客户端数据信号readyRead信号（客户端有数据就会发readyRead信号）
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_client_data()));
    //检测掉线信号
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));

}

void TcpServer::read_client_data()
{
    //可以实现同时读取多个客户端发送过来的消息
    QTcpSocket *obj = (QTcpSocket*)sender();
    QString msg = obj->readAll();
    qDebug()<<msg;
}

void TcpServer::client_dis()
{
     QTcpSocket *obj = (QTcpSocket*)sender();//掉线对象
     qDebug()<<obj->peerAddress().toString();//打印出掉线对象的ip
}