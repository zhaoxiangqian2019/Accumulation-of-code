�õ����� QCryptographicHash Class
ע��
	�����ļ��м���	core
		QT += core
	ͷ�ļ�:
		#include <QCryptographicHash>
		
��ϸ����:
	QCryptographicHash���ṩ��һ����������ɢ�еķ�����
	QCrvptographicHash���������ɶ����ƻ��ı����ݵļ���ɢ��
		Ŀǰ֧��MD4��MD5��SHA-1��SHA-224��SHA-256��SHA-384��SHA-512
		
���ں���������
	//����һ�����󣬸ö��������ʹ�÷��������ݴ�������ɢ�С�
	QCryptographicHash::QCryptographicHash(Algorithm method);
		Algorithm method��
			enum QCryptographicHash::Algorithm

				Constant			Value				Description
		QCryptographicHash::Md4		  0				Generate an MD4 hash sum
		QCryptographicHash::Md5		  1				Generate an MD5 hash sum
		QCryptographicHash::Sha1	  2				Generate an SHA-1 hash sum
		QCryptographicHash::Sha224	  3				Generate an SHA-224 hash sum (SHA-2). Introduced in Qt 5.0
		QCryptographicHash::Sha256	  4				Generate an SHA-256 hash sum (SHA-2). Introduced in Qt 5.0
		QCryptographicHash::Sha384	  5				Generate an SHA-384 hash sum (SHA-2). Introduced in Qt 5.0
		QCryptographicHash::Sha512	  6				Generate an SHA-512 hash sum (SHA-2). Introduced in Qt 5.0
		QCryptographicHash::Sha3_224  7				Generate an SHA3-224 hash sum. Introduced in Qt 5.1
		QCryptographicHash::Sha3_256  8				Generate an SHA3-256 hash sum. Introduced in Qt 5.1
		QCryptographicHash::Sha3_384  9  			Generate an SHA3-384 hash sum. Introduced in Qt 5.1
		QCryptographicHash::Sha3_512  10  			Generate an SHA3-512 hash sum. Introduced in Qt 5.1
	
	//�ͷŶ���
	QCryptographicHash::~QCryptographicHash();
	//�����ݵĵ�һ�������ַ���ӵ�����ɢ���С�
	void addData(const char *data,int length);
	//
	void addData(const QByteArray &data);
	bool addData(QIODevice *device);
	void reset();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	