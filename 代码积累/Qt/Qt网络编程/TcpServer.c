#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>
TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    //��ʼ��������server����
    mServer = new QTcpServer();
    //�����ͻ��������ź�newConnection
    connect(mServer,SIGNAL(newConnection()),this,SLOT(new_client())); //���ӿͻ���
    //��������������
    mServer->listen(QHostAddress::Any,9988);

}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::new_client()
{
    qDebug()<<"�¿ͻ�������";
    mSocket = mServer->nextPendingConnection();//��ͻ���ͨ�ŵ��׽���
    //�������տͻ��������ź�readyRead�źţ��ͻ��������ݾͻᷢreadyRead�źţ�
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_client_data()));
    //�������ź�
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));

}

void TcpServer::read_client_data()
{
    //����ʵ��ͬʱ��ȡ����ͻ��˷��͹�������Ϣ
    QTcpSocket *obj = (QTcpSocket*)sender();
    QString msg = obj->readAll();
    qDebug()<<msg;
}

void TcpServer::client_dis()
{
     QTcpSocket *obj = (QTcpSocket*)sender();//���߶���
     qDebug()<<obj->peerAddress().toString();//��ӡ�����߶����ip
}