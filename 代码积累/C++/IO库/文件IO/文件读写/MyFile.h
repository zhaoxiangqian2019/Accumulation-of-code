#pragma once
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <Windows.h>

using namespace std;

class MyFile
{
public:
	MyFile();
	MyFile(string fileName);
	~MyFile();

	bool open(unsigned int mode);
	bool open(fstream *&stream, unsigned int mode);
	void setFileName(string fileName);
	streamsize read(char *&_Str, int _Count);
	void write(char *&_Str, int _Count);
private:
	fstream m_stream;
	string m_fileName;
};

