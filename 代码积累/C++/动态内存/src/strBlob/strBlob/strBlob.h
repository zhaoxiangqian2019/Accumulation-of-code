#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <algorithm>
#include <memory>
using namespace std;

class strBlob
{
public:
	typedef vector<string>::size_type size_type;

	strBlob();
	~strBlob();
	strBlob(initializer_list<string> il);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	// ��Ӻ�ɾ��Ԫ��
	void push_back(const string &t) { data->push_back(t); }
	void pop_back();

	// Ԫ�ط���
	string &front();
	string &front() const;
	string &back();
	string &back() const;

	// ��ӡԪ��
	void printBlob();
	// ͳ�ƹ���̬�ڴ����ü���
	unsigned long useCount();

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

