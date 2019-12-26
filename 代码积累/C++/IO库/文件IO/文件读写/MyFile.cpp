#include "MyFile.h"
#include "MyFile.h"



MyFile::MyFile()
{
}

MyFile::MyFile(string fileName)
{

}

bool MyFile::open(unsigned int mode)
{
	m_stream.open(m_fileName, mode);
	if (!m_stream.is_open())
	{
		cout << "Open File failure!!!" << endl;
		return false;
	}
	return true;
}

bool MyFile::open(fstream *&stream, unsigned int mode)
{
	m_stream.open(m_fileName, mode);
	if (!m_stream.is_open())
	{
		cout << "Open File failure!!!" << endl;
		return false;
	}
	stream = &m_stream;
	return true;
}

void MyFile::setFileName(string fileName)
{
	fileName = fileName;
}

streamsize MyFile::read(char *&_Str, int _Count)
{
	m_stream.read(_Str, _Count);

	//返回实际读取到的字节数
	return m_stream.gcount();
}

void MyFile::write(char *&_Str, int _Count)
{
	m_stream.write(_Str, _Count);
}

MyFile::~MyFile()
{
}