A����������      

         1.����QTcpServer����
         2.���������������������ó�Ա����listen��QHostAddress::Any,�˿ںţ�
         3.���пͻ�������ʱ��ᷢ��newConnection�źţ������ۺ����������ӣ��õ�һ����ͻ���ͨ�ŵ��׽���QTcpSocket��
         4.QTcpsocket���������ó�Ա����write��
         5.�����ݵ��ͻ�������������QTcpSocket����ͻᷢ��readyRead�źţ������ۺ�����ȡ����

B���ͻ���  ��  

        1.����QTcpSocket����
        2.���ӷ�����connectToHost(QHostAddress("ip"),�˿ں�)
        3.QTcpsocket���������ó�Ա����write��
        4.�����ݵ��Է�����������QTcpSocket����ͻᷢ��readyRead�źţ������ۺ�����ȡ����

ע����Ҫ���õ���ͷ�ļ���
	#include <QTcpServer>
	#include <QTcpSocket>
    ��Ҫ�ڹ����ļ��м��� network
	QT	+= network
------------------------------------------------------------------------------------------------------------
�������������������������裺

1����ʼ��������server����

  mServer = new QTcpServer();
2����������������

  mServer->listen(QHostAddress::Any,9988);//9988Ϊ�˿ں�
3�����пͻ�������ʱ��ᷢ��newConnection�źţ������ۺ����������ӣ��õ�һ����ͻ���ͨ�ŵ��׽���QTcpSocket��

 connect(mServer,SIGNAL(newConnection()),this,SLOT(new_client()));
 mSocket = mServer->nextPendingConnection();//��ͻ���ͨ�ŵ��׽���
4����������

 mSocket->write(msg.toUtf8());
5�������ݵ��ͻ�������������QTcpSocket����ͻᷢ��readyRead�źţ������ۺ�����ȡ����

 connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_client_data()));
6�����Ӷ���ͻ���

 //����ʵ��ͬʱ��ȡ����ͻ��˷��͹�������Ϣ
 QTcpSocket *obj = (QTcpSocket*)sender();
7��������

 connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis())); //�������ź�

------------------------------------------------------------------------------------------------------------
˵������������Ǽ����������ͻ�������ôʵ�ֵģ�

1������QTcpSocket����

 mSocket = new QTcpSocket();
2�����ӷ�����connectToHost(QHostAddress("ip"),�˿ں�)�����ӷ�����ip�Ͷ˿ں�

 mSocket->connectToHost(ui->ipEdit->text(),ui->portEdit->text().toInt()); //ui->ipEdit->text()��ip��ui->portEdit->text().toInt()���˿ں�
3����������

//ȡ������Ϣ�༭������
QString msg = ui->sendEdit->toPlainText();
mSocket->write(msg.toUtf8());//ת����
4��������ӳɹ��źŹ����ۺ���

 connect(mSocket,SIGNAL(connected()),this,SLOT(connect_suc()));
5���������ź�

 connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
6���������Ϳͻ��˹رն�����ʹ��close

 mSocket->close();

------------------------------------------------------------------------------------------------------------