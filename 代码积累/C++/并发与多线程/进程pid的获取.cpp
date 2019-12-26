/**	
	@根据文件名获取文件的PID
	@DWORD &findPID	接收文件PID的变量
	@string findExeName	文件名
	@所用到的头文件<tlhelp32.h>
**/
bool getpid(DWORD &findPID, string findExeName)
{
	//findExeName名称中包含.exe
	bool hasfind = false;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("CreateToolhelp32Snapshot调用失败!"), NULL, NULL);
		return hasfind;
	}

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{

		//wchar_t exeName = pe32.szExeFile;

		int pSize = WideCharToMultiByte(CP_OEMCP, 0, pe32.szExeFile, wcslen(pe32.szExeFile), NULL, 0, NULL, NULL);
		char* pCStrKey = new char[pSize + 1];
		//第二次调用将双字节字符串转换成单字节字符串
		WideCharToMultiByte(CP_OEMCP, 0, pe32.szExeFile, wcslen(pe32.szExeFile), pCStrKey, pSize, NULL, NULL);
		pCStrKey[pSize] = '\0';

		//如果想要转换成string，直接赋值即可
		string exeName = pCStrKey;

		DWORD pid = pe32.th32ProcessID;
		if (exeName == findExeName)
		{
			findPID = pid;
			hasfind = true;
			break;
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	::CloseHandle(hProcessSnap);

	return hasfind;
}

/**
	@由文件PID查询文件的基地址
	@DWORD dwPID	所要查询文件的PID
	@DWORD& baseAddr	接收文件基地址的变量
**/
BOOL getProcessAddr(DWORD dwPID, DWORD& baseAddr)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// 在目标进程中获取所有进程的snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(_T("CreateToolhelp32Snapshot (of modules) fail"));
		MessageBoxW(NULL, _T("CreateToolhelp32Snapshot (of modules) fail"),NULL,NULL);
		return(FALSE);
	}

	// 设置MODULEENTRY32数据结构大小字段
	me32.dwSize = sizeof(MODULEENTRY32);

	//检索第一个模块的信息，不成功则返回
	if (!Module32First(hModuleSnap, &me32))
	{
		//AfxMessageBox(_T("Module32First fail")); // 显示调用失败
		MessageBoxW(NULL, _T("Module32First fail"), NULL, NULL);
		CloseHandle(hModuleSnap);    // 清除句柄对象
		return(FALSE);
	}

	// 从me32中得到基址
	baseAddr = (DWORD)me32.modBaseAddr;

	// 别忘了最后清除模块句柄对象
	CloseHandle(hModuleSnap);
	return(TRUE);
}

/**
	@字符串(string)类型转宽字符(wchar_t)类型转宽字符
	@const string& str	所要转换的数据
	@返回值		wchar_t宽字符型
		char是8位字符类型，最多只能包含256种字符，许多外文字符集所含的字符数目超过256个，char型无法表示。
		wchar_t数据类型一般为16位或32位，但不同的C或C++库有不同的规定，如GNU Libc规定wchar_t为32位，总之，wchar_t所能表示的字符数远超char型。
		标准C中的wprintf()函数以及标准C++的iostream类库中的类和对象能提供wchar_t宽字符类型的相关操作
		wchar_t用来表示Unicode字符(类似于ASCII码，是一种国际的字符编码)
**/
wchar_t* ANSIToUnicode(const string& str)
{
	int len = 0;
	len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t * pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	//wstring rt;
	//rt = (wchar_t*)pUnicode;
	return pUnicode;
	//return rt;//注意内存泄漏
}

/**
	@由进程pid寻找进程中指定函数的偏移地址(创建进程快照的方式寻找所要的函数地址)
	@DWORD pid	进程的pid
	@LPCTSTR Exename	所要找的函数的函数名
**/
DWORD ProcessFind(DWORD pid, LPCTSTR Exename)
{
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL, pid);
	if (!hProcess)
		return FALSE;
	PROCESSENTRY32 info;
	info.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcess, &info))
		return FALSE;
	while (true)
	{
		if (wcscmp(info.szExeFile, Exename) == 0)
			return info.th32DefaultHeapID;
		if (!Process32Next(hProcess, &info))
			return FALSE;
	}
	return FALSE;
}


BOOL ReadProcessMemory(
						HANDLE hProcess, // 被读取进程的句柄；
						LPCVOID lpBaseAddress, // 读的起始地址；
						LPVOID lpBuffer, // 存放读取数据缓冲区；
						DWORD nSize, // 一次读取的字节数；
						LPDWORD lpNumberOfBytesRead // 实际读取的字节数；
					);