#inculde <windows.h>

//�ҹ���inline ����
class MyHookClass
{
public:
	MyHookClass()
	{
		m_pfnOld = nullptr;
		//ZeroMemory������΢��˾�����������SDK�е�һ���ꡣ ����������0�����һ���ڴ�����
		ZeroMemory(m_bOldBytes,5);
		ZeroMemory(m_bNewBytes,5);
	}
	~MyHookClass()
	{
		UnHook;
	}
		
	/**
	*	inline�ҹ�����
	*	@param szModuleName	Ŀ�꺯������ģ������
	*	@param	szFuncName	Ŀ�꺯������
	*	@param	pHookFunc	�ҹ�������ַ
	*	@return
	*/
	BOOL Hook(char *szModuleName,char *szFuncName,PROC pHookFunc)
	{
		BOOL bRet = FALSE;
		do
		{
			//��ȡ������dll�е�λ��
			m_pfnOld = GetProcAddress(GetModuleHandleA(szModuleName),szFuncName);
			if(!m_pfnOld)
			{
				break;
			}
			DWORD dwNum = 0;
			//��һ���ڴ���������� ������Ϊ���ݽ��̾������ý��̵�ĳ���ڴ�ռ�;
			ReadProcessMemory(GetCurrentProcess(),m_pfnOld,m_bOldBytes,5,&dwNum);	//GetCurrentProcess()��ȡ��ǰ���̵�һ��α���
			//jmp	0xe9
			m_bNewBytes[0] = '0xe9';
			*(DWORD *)(m_bNewBytes + 1) = (DWORD)pHookFunc - (DWORD)m_pfnOld - 5;
			WriteProcessMemory(GetCurrentProcess(),m_pfnOld,m_bNewBytes,5,&dwNum);
			bRet = TRUE;
		}while(FALSE)
		return bRet;
	}
	void UnHook()
	{
		if(m_pfnOld != nullptr)
		{
			DWORD dwNum = 0;
			WriteProcessMemory(GetCurrentProcess(),m_pfnOld,m_bOldBytes,5,&dwNum);
		}
	}
	BOOL ReHook()
	{
		BOOL bRet = FALSE;
		if(m_pfnOld)
		{
			DWORD dwNum = 0;
			WriteProcessMemory(GetCurrentProcess(),m_pfnOld,m_bNewBytes,5,&dwNum);
			bRet = TRUE;
		}
		return bRet;
	}
private:
	PROC m_pfnOld;	//�ɻָ���
	BYTE m_bOldBytes[5];
	BYTE m_bNewBytes[5];
}










