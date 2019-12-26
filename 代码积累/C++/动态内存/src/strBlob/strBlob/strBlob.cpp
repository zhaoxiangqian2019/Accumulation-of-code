#include "strBlob.h"



strBlob::strBlob() : data(make_shared<vector<string>>())
{
}

strBlob::strBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il))
{
}

strBlob::~strBlob()
{
}

void strBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

string& strBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

string& strBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

string& strBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->front();
}

string& strBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->front();
}

void strBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

void strBlob::printBlob()
{
	for_each(data->begin(), data->end(), [](const string& s) {cout << left << setw(12) << s; });
	cout << endl;
}

// 统计共享动态内存的引用计数
unsigned long strBlob::useCount()
{
	return data.use_count();
}