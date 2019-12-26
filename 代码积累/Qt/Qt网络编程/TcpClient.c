#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QDebug>
TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    //��ʼ���׽��ֶ���
    mSocket = new QTcpSocket();
    //���������ź�
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::read_data()
{
    QString msg = mSocket->readAll();
    qDebug()<<msg;
}

void TcpClient::on_btn_connectServer_clicked()
{
    //������ӳɹ��źŹ����ۺ���
    connect(mSocket,SIGNAL(connected()),this,SLOT(connect_suc()));
    //�������ź�
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
    //���ӷ�����������ip�Ͷ˿ں�
    mSocket->connectToHost(ui->ipEdit->text(),ui->portEdit->text().toInt());

}

void TcpClient::on_btn_send_clicked()
{
    //ȡ������Ϣ�༭������
    QString msg = ui->sendEdit->toPlainText();
    mSocket->write(msg.toUtf8());//ת����
}

void TcpClient::connect_suc()
{
    ui->btn_connectServer->setEnabled(false);//������ӳɹ������Ӱ�ť���ܰ���
}
void TcpClient::client_dis()
{
    ui->btn_connectServer->setEnabled(true);//�������û�гɹ������Ӱ�ť�����԰���
}