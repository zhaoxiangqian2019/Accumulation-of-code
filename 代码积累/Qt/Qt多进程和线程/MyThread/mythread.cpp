#include "mythread.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    m_flag = true;
    m_flagTrue = true;
    a = 0;
}

void MyThread::DoWork()
{
    while(m_flagTrue)
    {
        while(m_flag)
        {
            sig_SendMsg(a++);
            QThread::sleep(1);
        }
    }
}

void MyThread::SetFlag(bool flag)
{
    m_flag = flag;
}

