#include <stdio.h>  
#include <winsock2.h>  
 
#pragma comment(lib,"ws2_32.lib")  
 
int main(int argc, char* argv[])
{
	//��ʼ��WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//�����׽���  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}
	//��ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}
	//ѭ����������  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[1024];
	while (true)
	{
		printf("�ȴ�����...\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		//��������  
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}
		//��������  
		const char * sendData = "��ã�TCP�ͻ��ˣ�\n";
		send(sClient, sendData, strlen(sendData), 0);
	}
	closesocket(sClient);
	closesocket(slisten);
	WSACleanup();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
#include <winsock2.h>  
#include <WS2tcpip.h>
#include<stdio.h>
#include<iostream>
#include<cstring>
 
using namespace std;
#pragma comment(lib, "ws2_32.lib")
 
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	inet_pton(AF_INET, "127.0.0.1", &serAddr.sin_addr);
 
	while (true) 
	{
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket!");
			return 0;
		}
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //����ʧ�� 
			printf("connect error !");
			closesocket(sclient);
			return 0;
		}
		send(sclient, "asd", strlen("asd"), 0);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf(recData);
		}
		closesocket(sclient);
	}
	WSACleanup();
	return 0;
}

