#include <iostream>
#include <thread>
#include <list>
#include <mutex>		//线程锁的头文件	

using namespace std;

#if 0

void myThread(int num)
{
	cout << "编号为" << num << "的线程开始执行了！！！" << endl;
	/*
		函数功能模块
	*/
	cout << "编号为" << num << "的线程执行结束了！！！" << endl;
	return;
}

int main()
{
	vector<thread> myThreads;
	for (int i = 0; i < 10; i++)
	{
		myThreads.push_back(thread(myThread, i));
		//myThreads.back().join();
	}
	/*for (int i = 0; i < myThreads.size(); i++)
	{
		myThreads.at(i).join();
	}*/
	cout << "主线程函数执行！！！" << endl;
	system("pause");
	return 0;
}

#elif 1
class A
{
public:
std::unique_lock<std::mutex> rtn_unique_lock()
{
	std::unique_lock<std::mutex> tmpguard(m_mutex);
	return tmpguard;			//从函数返回一个局部的unique_lock对象是可以的。
								//返回这种局部对象的tmpguard会导致系统生成临时unique_lock对象，
								//并调用unique_lock的移动构造函数
}

	//把收到的消息入到一个队列的线程
	void inMesRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMesRecvQueue()执行，插入一个元素" << i << endl;
			lock_guard<mutex> m_guard(m_mutex);
			std::chrono::milliseconds dura(2000);	//1秒 = 1000毫秒，所以2000毫秒 = 2秒。
			std::this_thread::sleep_for(dura);;		//休息一定的时长。
			m_msgRecvQueue.push_back(i);	
		}
	}

	bool outMsgLULProc(int &command)
	{
		//lock_guard<mutex> m_guard(m_mutex);
		unique_lock<mutex> m_uniqueLock(m_mutex, try_to_lock);
		if (m_uniqueLock.owns_lock())
		{
			//拿到了锁
			cout << "拿到了锁！！！！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;
			if (!m_msgRecvQueue.empty())
			{
				command = m_msgRecvQueue.front();		//返回第一个元素，但不检查元素是否存在
				m_msgRecvQueue.pop_front();				//移除第一个元素，但不返回
				return true;
			}
			return false;
		}
		else
		{
			//没有拿到锁
			cout << "没有拿到锁，尝试做一些其他的！！！" << endl;
		}
	}

	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{
			bool result = outMsgLULProc(command);
			//消息不为空
			if (result == true)
			{
				cout << "outMsgRecvQueue()执行，取出第一个元素" << command << endl;
			}
			else
			{
				//消息队列为空
				cout << "outMsgRecvQueue()执行，但目前消息队列为空" << i << endl;
			}
		}
	}

private:
	list<int> m_msgRecvQueue;
	mutex m_mutex;
};


int main()
{
	A myToJob;
	thread myInMsgJob(&A::inMesRecvQueue, &myToJob);
	thread myOutMsgJob(&A::outMsgRecvQueue, &myToJob);

	myInMsgJob.join();
	myOutMsgJob.join();

	return 0;
}

#endif // 0