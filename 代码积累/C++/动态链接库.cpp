DLL����
	DLL()���ֳ�Ϊ��Ӧ�ó�����չ������һ����������ģ�飬������Դ�ļ��������ȣ���Ӧ�ó�����Ҫʱ���á�
�ֽ׶Σ��󲿷�Ӧ�ó��򶼻���Ƴ�������+DLL�Ŀ�ܡ�����������Ҫ�Ĺ��ܵ�ʱ�򣬾ͻ�ȥ���Ӳ����ö�Ӧ
DLL����ΪDLLʱ�˴˶����ģ�����������ļ����ٶȸ��졣����Ҳ�����˹���Ч�ʡ�
	ͬʱ������DLL�Ķ����ԣ�ʹ��Ӧ�ó����ά���͸��±�ø������ף��ɱ���󽵵͡���Ϊ����ֻ��Ҫ����
��Ӧ��ģ�飬����������ĸ��¡�

	�߳�ע�룬��ͨ������Զ���̵߳ķ�ʽ����DLL���ص�Ŀ�����������еĳ��÷�ʽ��Ŀǰ��Զ���߳�ע�룬
��ΪWinNTƽ̨�������DLLע�뷽ʽ֮һ������Ϸ����ȫ����������ż�Ϊ��Ҫ�Ľ�ɫ��
	����WinNTϵͳ�½��̿ռ�Ķ����ԣ���ȡ�������̵���Ϣ������Ҫͨ������Ŀ����̿ռ�ķ�ʽ����ʹ
���߳�ע��Ϳ������׵�ʵ��Ŀ�ġ�
	���������߳�ע�룬������ע��һ�����б�дBUG��DLL�������׶��������̵��ȶ�������ƻ�����������
���̱�����

���ӿ��Ϊ��̬���ӿ�;�̬���ӿ����֣���׺���ֱ�Ϊ.dll��.lib
	��̬���ӿ⣬�����е�ʱ��ֱ�ӰѴ���ȫ�����ص������С�ͨ�����·�ʽ����
		#include <XXX.h>
		#pragma comment(lib,"XXX.lib")
	��ʹ�ö�̬���ӿ⣬����Ҫ��ʱ����أ��ڲ���Ҫ��ʱ���ж���ͷ���Դ
		ʹ��		LoadLibrary		��̬����DLL
		ʹ��		GetProcAddress	��ȡDLL�е���������ָ��
		���ʹ��	FreeLibrary		ж��ָ��DLL
		
��Visual Studio�ı��뻷���£�DLL�ɷ�Ϊ���ࣺ
	��MFC��DLL	--	��ʹ��SDK API���б�̣��ܱ������������Ե��ã�
	MFC����DLL	--	����ʹ��MFC���б�̣��ܱ������������Ե��ã�			ʹ��MFC��ܿ���������ʹ�÷�װ�ࣻ
	MFC��չDLL	--	����ʹ��MFC���б�̣���ֻ�ܱ���MFC��д�ĳ�����á�	������
	
(MFC �� Microsoft Foundation Class��Library	��΢����C++��API���еķ�װ��ȫ����װ�����࣬������ʹ��)

DLL�ļ�����ڵ㺯��
	BOOL APIENTRY DLLMain(	HMODULE hModule,			//ָ��DLL�����ʵ�����
							DWORD ul_reason_for_call,	//ָ�������DLL�����õ�ԭ��ԭ�����£�
							LPVOID lpReserved,			//
						)
	{
		return TURE;	
	}
						
=>	DLL_PROCESS_ATTACH:		//�����̵�һ������DLL��ͨ��������ڵ�ʱ����õ��������
	DLL_PROCESS_DETACH:		//�����ڿռ���ȡ��DLL��ӳ��ʱ����õ��������
	DLL_THREAD_ATTACH:		//ÿ�����̴߳���ʱ��ϵͳ�������ӳ���DLL���˲���������ں���
	DLL_THREAD_DETACH:		//ÿ���߳��˳��򷵻�ʱ��ϵͳ�������ӳ���DLL���˲���Ҫ��ִ�ж���������
	

DLL�ĵ�������		//����Ҫʹ��DLLʱ��Ҫʹ�õ�Ŀ�ĺ�����Ҳ���ǵ��÷�װ���ɵĽӿڣ������ʹ��
	������ʽ��
		extern "C" _declspec(dllexport)
	
DLL���뺯��
	������ʽ��
		extern "C"	_declspec(dllimport)
		
		
���̵���DLL
	ʹ��LoadLibrary���ؽ�������DLL
	HMODULE hMod = LoadLibrary(Dll·��)
	���嵼�뺯��ָ��
	typedef int (*ADD_IMRORT) (int a,int b);	//����һ��ָ�򷵻�ֵΪint���͵ĺ���ָ��
	ʹ��GetProcADDress��ú�����ڵ�
	ADD_IMRORT add_proc = (ADD_IMRORT)GetProcAddress(hMod,"ADD");
	�ڳ�����ʹ��
	int result = add_proc(1,2);
	
GetProcAddress��һ������������������Ǽ���ָ���Ķ�̬���ӿ�(DLL)�е�����⺯����ַ��
	lpProcName�����ܹ�ʶ��DLL�еĺ�����
FARPROC GetProcAddress(
						HMODULE hModule, // DLLģ����
						LPCSTR lpProcName // ������
						);
	hModule
		[in] �����˺�����DLLģ��ľ����LoadLibrary��AfxLoadLibrary ����GetModuleHandle�������Է��ش˾����
	lpProcName
		[in] ��������������NULL��β���ַ���������ָ������������ֵ������˲�����һ������ֵ����������һ���ֵĵ��ֽڣ����ֽڱ���Ϊ0��
	����ֵ��
		����������óɹ�������ֵ��DLL�е����������ַ��
		�����������ʧ�ܣ�����ֵ��NULL���õ���һ���Ĵ�����Ϣ�����ú���GetLastError��


DLL��������
	��VS	->	�½���Ŀ ->	Win32 ->  ȷ��  -> ��һ�� -> (��Win32Ӧ�ó����򵼴�����	-> ����DLL -> ���)
	��ͷ�ļ�������½�ͷ�ļ�
<XXX.h>
[
	#pragma once			//��ֹ�ظ�����
	/*
	#pragma once �� #ifndef	������
	Ϊ�˱���ͬһ���ļ���include���

	#ifndef��ʽ
	#pragma once��ʽ

���ܹ�֧�������ַ�ʽ�ı������ϣ����߲�û��̫������𣬵���������Ȼ������һЩϸ΢������
    ��ʽһ��

    #ifndef __SOMEFILE_H__
    #define __SOMEFILE_H__
    ... ... // һЩ�������
    #endif

    ��ʽ����

    #pragma once
    ... ... // һЩ�������


    #ifndef�ķ�ʽ�����ں����ֲ��ܳ�ͻ���ⲻ����Ա�֤ͬһ���ļ����ᱻ������Σ�Ҳ�ܱ�֤������ȫ��ͬ�������ļ����ᱻ��С��ͬʱ��������Ȼ��ȱ����������ͬͷ�ļ��ĺ�����С��"ײ��"�����ܾͻᵼ��ͷ�ļ��������ڣ�������ȴӲ˵�Ҳ���������״��

    #pragma once���ɱ������ṩ��֤��ͬһ���ļ����ᱻ������Ρ�ע��������˵��"ͬһ���ļ�"��ָ�����ϵ�һ���ļ���������ָ������ͬ�������ļ��������ĺô� �ǣ��㲻���ٷѾ���������ˣ���ȻҲ�Ͳ�����ֺ�����ײ������������⡣��Ӧ��ȱ��������ĳ��ͷ�ļ��ж�ݿ��������������ܱ�֤���ǲ����ظ��������� Ȼ����Ⱥ�����ײ������"�Ҳ�������"�����⣬�ظ����������ױ����ֲ�������

   ��ʽһ������֧��������ֲ�Ժã���ʽ�� ���Ա������ֳ�ͻ
	*/
	
	#include "stdafx.h"

	#define ExportFunc _declspec(dllexport)

	extern "C"	ExportFunc int Add(int a, int b);
	extern "C"	ExportFunc int Sub(int a, int b);
]

<XXX.cpp>
[
	// sumDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ExportDLL.h"

int Add(int a, int b)
{
	return a + b;
}

int Sub(int a,int b)
{
	return a - b;
}

]

<ִ���ļ���>
[
	HMODULE hModule = LoadLibraryW(_T("D:\\WORK\\�����ļ�\\sumDLL\\Debug\\sumDLL.dll"));
	if (!hModule)
		return;

	ADD Add;
	SUB Sub;
	Add = (ADD)GetProcAddress(hModule, "Add");
	Sub = (SUB)GetProcAddress(hModule, "Sub");
	
	if (!Add || !Sub)
		return;
	int Result;
	Result = 0;
	Result = Add(10, 24);
	CString result;
	result.Format(_T("%d"), Result);
	MessageBox(result);

	Result = Sub(48, 34);
	result.Format(_T("%d"), Result);
	MessageBox(result);

	FreeLibrary(hModule);
]

Զ���߳�ע��
	ע��Ŀ����ԣ�
		kernel32.dll��user32.dll�������ڴ󲿷ֳ����϶�����õ�DLL
	ͬһ��DLL���ڲ�ͬ�Ľ����У���һ����ӳ�䣨���أ���ͬһ���ڴ��ַ�¡�
	����kernel32.dll��user.dll���⡣�������Ǳ�ӳ�䵽���̵��ڴ���ѡ��ַ��
	��ˣ�������ʹ��������DLL�Ľ����У�������DLL���ڴ��ַ����ͬ�ġ�
	�����ڱ����̻�ȡ��kernel.dll�к����ĵ�ַ����Ŀ�������Ҳ��һ����
	
	Ŀ����� -> ����DLL��ַ -> ����Զ���߳� -> ����DLL -> ʵ��DLL��ע��
	
	ʵ���߳�ע��
		����ʹ�����º�����
			OpenProcess				//��ȡ��֪���̵ľ��
			VirtualAllocEx			//�ڽ���������ռ�
			WriteProcessMessage		//�������д�붫��
			GetProcAddress			//ȡ�ú�����DLL�еĵ�ַ
			GreateRemoteThreadEx	//�����������д������߳�
			CloseHandle				//�رվ��
			
	����߳�ע��













						
						
						
						
						
						
						
						
						
						
						
						
						
						
						
						
	