用到的类 QCryptographicHash Class
注：
	工程文件中加入	core
		QT += core
	头文件:
		#include <QCryptographicHash>
		
详细描述:
	QCryptographicHash类提供了一种生成密码散列的方法。
	QCrvptographicHash可用于生成二进制或文本数据的加密散列
		目前支持MD4、MD5、SHA-1、SHA-224、SHA-256、SHA-384和SHA-512
		
类内函数描述：
	//构造一个对象，该对象可用于使用方法从数据创建加密散列。
	QCryptographicHash::QCryptographicHash(Algorithm method);
		Algorithm method：
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
	
	//释放对象
	QCryptographicHash::~QCryptographicHash();
	//将数据的第一个长度字符添加到加密散列中。
	void addData(const char *data,int length);
	//
	void addData(const QByteArray &data);
	bool addData(QIODevice *device);
	void reset();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	