#include <iostream>
#include <thread>
#include <list>
#include <mutex>		//�߳�����ͷ�ļ�	

using namespace std;

#if 0

void myThread(int num)
{
	cout << "���Ϊ" << num << "���߳̿�ʼִ���ˣ�����" << endl;
	/*
		��������ģ��
	*/
	cout << "���Ϊ" << num << "���߳�ִ�н����ˣ�����" << endl;
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
	cout << "���̺߳���ִ�У�����" << endl;
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
	return tmpguard;			//�Ӻ�������һ���ֲ���unique_lock�����ǿ��Եġ�
								//�������־ֲ������tmpguard�ᵼ��ϵͳ������ʱunique_lock����
								//������unique_lock���ƶ����캯��
}

	//���յ�����Ϣ�뵽һ�����е��߳�
	void inMesRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMesRecvQueue()ִ�У�����һ��Ԫ��" << i << endl;
			lock_guard<mutex> m_guard(m_mutex);
			std::chrono::milliseconds dura(2000);	//1�� = 1000���룬����2000���� = 2�롣
			std::this_thread::sleep_for(dura);;		//��Ϣһ����ʱ����
			m_msgRecvQueue.push_back(i);	
		}
	}

	bool outMsgLULProc(int &command)
	{
		//lock_guard<mutex> m_guard(m_mutex);
		unique_lock<mutex> m_uniqueLock(m_mutex, try_to_lock);
		if (m_uniqueLock.owns_lock())
		{
			//�õ�����
			cout << "�õ���������������������������������������������������������������" << endl;
			if (!m_msgRecvQueue.empty())
			{
				command = m_msgRecvQueue.front();		//���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
				m_msgRecvQueue.pop_front();				//�Ƴ���һ��Ԫ�أ���������
				return true;
			}
			return false;
		}
		else
		{
			//û���õ���
			cout << "û���õ�����������һЩ�����ģ�����" << endl;
		}
	}

	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{
			bool result = outMsgLULProc(command);
			//��Ϣ��Ϊ��
			if (result == true)
			{
				cout << "outMsgRecvQueue()ִ�У�ȡ����һ��Ԫ��" << command << endl;
			}
			else
			{
				//��Ϣ����Ϊ��
				cout << "outMsgRecvQueue()ִ�У���Ŀǰ��Ϣ����Ϊ��" << i << endl;
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