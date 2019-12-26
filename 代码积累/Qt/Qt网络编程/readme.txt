A、服务器：      

         1.创建QTcpServer对象
         2.启动服务器（监听）调用成员方法listen（QHostAddress::Any,端口号）
         3.当有客户端链接时候会发送newConnection信号，触发槽函数接受链接（得到一个与客户端通信的套接字QTcpSocket）
         4.QTcpsocket发送数据用成员方法write，
         5.读数据当客户端有数据来，QTcpSocket对象就会发送readyRead信号，关联槽函数读取数据

B、客户端  ：  

        1.创建QTcpSocket对象
        2.链接服务器connectToHost(QHostAddress("ip"),端口号)
        3.QTcpsocket发送数据用成员方法write，
        4.读数据当对方有数据来，QTcpSocket对象就会发送readyRead信号，关联槽函数读取数据

注：需要调用到的头文件：
	#include <QTcpServer>
	#include <QTcpSocket>
    需要在工程文件中加入 network
	QT	+= network
------------------------------------------------------------------------------------------------------------
下面我们来看看服务器程序步骤：

1、初始化服务器server对象

  mServer = new QTcpServer();
2、启动监听服务器

  mServer->listen(QHostAddress::Any,9988);//9988为端口号
3、当有客户端链接时候会发送newConnection信号，触发槽函数接受链接（得到一个与客户端通信的套接字QTcpSocket）

 connect(mServer,SIGNAL(newConnection()),this,SLOT(new_client()));
 mSocket = mServer->nextPendingConnection();//与客户端通信的套接字
4、发送数据

 mSocket->write(msg.toUtf8());
5、读数据当客户端有数据来，QTcpSocket对象就会发送readyRead信号，关联槽函数读取数据

 connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_client_data()));
6、连接多个客户端

 //可以实现同时读取多个客户端发送过来的消息
 QTcpSocket *obj = (QTcpSocket*)sender();
7、检测掉线

 connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis())); //检测掉线信号

------------------------------------------------------------------------------------------------------------
说完服务器那我们继续来看看客户端是怎么实现的：

1、创建QTcpSocket对象

 mSocket = new QTcpSocket();
2、链接服务器connectToHost(QHostAddress("ip"),端口号)，连接服务器ip和端口号

 mSocket->connectToHost(ui->ipEdit->text(),ui->portEdit->text().toInt()); //ui->ipEdit->text()：ip，ui->portEdit->text().toInt()：端口号
3、发送数据

//取发送信息编辑框内容
QString msg = ui->sendEdit->toPlainText();
mSocket->write(msg.toUtf8());//转编码
4、检测链接成功信号关联槽函数

 connect(mSocket,SIGNAL(connected()),this,SLOT(connect_suc()));
5、检测掉线信号

 connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
6、服务器和客户端关闭都可以使用close

 mSocket->close();

------------------------------------------------------------------------------------------------------------