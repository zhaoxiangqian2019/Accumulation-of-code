/**	
	@�����ļ�����ȡ�ļ���PID
	@DWORD &findPID	�����ļ�PID�ı���
	@string findExeName	�ļ���
	@���õ���ͷ�ļ�<tlhelp32.h>
**/
bool getpid(DWORD &findPID, string findExeName)
{
	//findExeName�����а���.exe
	bool hasfind = false;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("CreateToolhelp32Snapshot����ʧ��!"), NULL, NULL);
		return hasfind;
	}

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{

		//wchar_t exeName = pe32.szExeFile;

		int pSize = WideCharToMultiByte(CP_OEMCP, 0, pe32.szExeFile, wcslen(pe32.szExeFile), NULL, 0, NULL, NULL);
		char* pCStrKey = new char[pSize + 1];
		//�ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
		WideCharToMultiByte(CP_OEMCP, 0, pe32.szExeFile, wcslen(pe32.szExeFile), pCStrKey, pSize, NULL, NULL);
		pCStrKey[pSize] = '\0';

		//�����Ҫת����string��ֱ�Ӹ�ֵ����
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
	@���ļ�PID��ѯ�ļ��Ļ���ַ
	@DWORD dwPID	��Ҫ��ѯ�ļ���PID
	@DWORD& baseAddr	�����ļ�����ַ�ı���
**/
BOOL getProcessAddr(DWORD dwPID, DWORD& baseAddr)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// ��Ŀ������л�ȡ���н��̵�snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(_T("CreateToolhelp32Snapshot (of modules) fail"));
		MessageBoxW(NULL, _T("CreateToolhelp32Snapshot (of modules) fail"),NULL,NULL);
		return(FALSE);
	}

	// ����MODULEENTRY32���ݽṹ��С�ֶ�
	me32.dwSize = sizeof(MODULEENTRY32);

	//������һ��ģ�����Ϣ�����ɹ��򷵻�
	if (!Module32First(hModuleSnap, &me32))
	{
		//AfxMessageBox(_T("Module32First fail")); // ��ʾ����ʧ��
		MessageBoxW(NULL, _T("Module32First fail"), NULL, NULL);
		CloseHandle(hModuleSnap);    // ����������
		return(FALSE);
	}

	// ��me32�еõ���ַ
	baseAddr = (DWORD)me32.modBaseAddr;

	// ������������ģ��������
	CloseHandle(hModuleSnap);
	return(TRUE);
}

/**
	@�ַ���(string)����ת���ַ�(wchar_t)����ת���ַ�
	@const string& str	��Ҫת��������
	@����ֵ		wchar_t���ַ���
		char��8λ�ַ����ͣ����ֻ�ܰ���256���ַ�����������ַ����������ַ���Ŀ����256����char���޷���ʾ��
		wchar_t��������һ��Ϊ16λ��32λ������ͬ��C��C++���в�ͬ�Ĺ涨����GNU Libc�涨wchar_tΪ32λ����֮��wchar_t���ܱ�ʾ���ַ���Զ��char�͡�
		��׼C�е�wprintf()�����Լ���׼C++��iostream����е���Ͷ������ṩwchar_t���ַ����͵���ز���
		wchar_t������ʾUnicode�ַ�(������ASCII�룬��һ�ֹ��ʵ��ַ�����)
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
	//return rt;//ע���ڴ�й©
}

/**
	@�ɽ���pidѰ�ҽ�����ָ��������ƫ�Ƶ�ַ(�������̿��յķ�ʽѰ����Ҫ�ĺ�����ַ)
	@DWORD pid	���̵�pid
	@LPCTSTR Exename	��Ҫ�ҵĺ����ĺ�����
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
						HANDLE hProcess, // ����ȡ���̵ľ����
						LPCVOID lpBaseAddress, // ������ʼ��ַ��
						LPVOID lpBuffer, // ��Ŷ�ȡ���ݻ�������
						DWORD nSize, // һ�ζ�ȡ���ֽ�����
						LPDWORD lpNumberOfBytesRead // ʵ�ʶ�ȡ���ֽ�����
					);