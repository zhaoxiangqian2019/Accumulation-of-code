#inculde <windows.h>

//挂钩类inline 钩子
class MyHookClass
{
public:
	MyHookClass()
	{
		m_pfnOld = nullptr;
		//ZeroMemory是美国微软公司的软件开发包SDK中的一个宏。 其作用是用0来填充一块内存区域。
		ZeroMemory(m_bOldBytes,5);
		ZeroMemory(m_bNewBytes,5);
	}
	~MyHookClass()
	{
		UnHook;
	}
		
	/**
	*	inline挂钩函数
	*	@param szModuleName	目标函数所在模块名称
	*	@param	szFuncName	目标函数名称
	*	@param	pHookFunc	挂钩函数地址
	*	@return
	*/
	BOOL Hook(char *szModuleName,char *szFuncName,PROC pHookFunc)
	{
		BOOL bRet = FALSE;
		do
		{
			//获取函数在dll中的位置
			m_pfnOld = GetProcAddress(GetModuleHandleA(szModuleName),szFuncName);
			if(!m_pfnOld)
			{
				break;
			}
			DWORD dwNum = 0;
			//是一个内存操作函数， 其作用为根据进程句柄读入该进程的某个内存空间;
			ReadProcessMemory(GetCurrentProcess(),m_pfnOld,m_bOldBytes,5,&dwNum);	//GetCurrentProcess()获取当前进程的一个伪句柄
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
	PROC m_pfnOld;	//可恢复的
	BYTE m_bOldBytes[5];
	BYTE m_bNewBytes[5];
}










