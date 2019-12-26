#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QDebug>
TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    //初始化套接字对象
    mSocket = new QTcpSocket();
    //关联数据信号
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
    //检测链接成功信号关联槽函数
    connect(mSocket,SIGNAL(connected()),this,SLOT(connect_suc()));
    //检测掉线信号
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
    //连接服务器，设置ip和端口号
    mSocket->connectToHost(ui->ipEdit->text(),ui->portEdit->text().toInt());

}

void TcpClient::on_btn_send_clicked()
{
    //取发送信息编辑框内容
    QString msg = ui->sendEdit->toPlainText();
    mSocket->write(msg.toUtf8());//转编码
}

void TcpClient::connect_suc()
{
    ui->btn_connectServer->setEnabled(false);//如果连接成功则连接按钮不能按下
}
void TcpClient::client_dis()
{
    ui->btn_connectServer->setEnabled(true);//如果连接没有成功则连接按钮还可以按下
}