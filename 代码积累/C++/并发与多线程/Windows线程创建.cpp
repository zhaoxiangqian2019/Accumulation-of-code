/* ������һ���̡߳������̽����������̡߳� */

#include<Windows.h>
#include<stdio.h>

DWORD WINAPI ThreadFunc(LPVOID);

void main()
{
    HANDLE hThread;
    DWORD  threadId;

    hThread = CreateThread(NULL, 0, ThreadFunc, 0, 0, &threadId); // �����߳�
    printf("�������̣߳� pid = %d\n", GetCurrentThreadId());  //������߳�pid
    Sleep(2000);
}

DWORD WINAPI ThreadFunc(LPVOID p)
{   
    printf("�������̣߳� pid = %d\n", GetCurrentThreadId());   //������߳�pid
    return 0;
}
