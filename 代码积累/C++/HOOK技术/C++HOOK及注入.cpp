//���ʱ��˵��ڴ�
	�����ַ�ʽ��
		�ٹٷ���	ʹ��ϵͳAPI	����̶�ȡ����	
		��ע��

	ע��DLL�ķ�ʽ��
		Զ�߳�ע��
			����:
				1��֪�����Ľ���PID
				2���򿪽���
				3���ڶԷ��Ľ����з���һ���ڴ湩����д�붫��
				4��������õ��ڴ���д��������Ҫд�������
				5������ִ�����Ǹո�д��Ķ���
		APCע��					//ԭ��Sleep	�ڳ���ȴ������ʱ�䣬�����APC����APC�������룬ʵ��ע��
		DLL�ٳ�ע��				//�����ڼ���DLL��ʱ�򣬻����Ȳ��ҵ�ǰĿ¼�µ�DLL����û�У���ȥϵͳĿ¼�²���
								//			���DLL�ٳ�ע��ķ�����(��user32.dllΪ��)
								//					���ڵ�ǰĿ¼��α��һ��usre32.dll
								//							ע��������Ҫ��Ҫע���DLL ����> ����Ҫ�Ĺ���
								//					���ټ���ϵͳ�� user32.dll ����Ĺ���
												
		���뷨ע��				//�Լ���һ���򵥵����뷨��ͨ�����뷨ʵ��ע��
		

ͨ���޸Ļ��ָ�����޸ĺ�����ִ�в��裺
eg��
	typedef void (*FUNC)();

	FUNC OldFunc = NULL;
	FUNC NewFunc = NULL;
	BYTE g_HookOldFunc[5] = { 0 };
	BYTE g_HookNewFunc[5] = { 0 };

	void func1()
	{
		cout << "������" << endl;
	}

	void func2()
	{
		cout << "�ǺǺ�" << endl;
	}
	int main()
	{
		OldFunc = func1;
		NewFunc = func2;
		func1();
		
		//��func1��ǰ5�����ָ�����g_HookOldFunc��		INVALID_HANDLE_VALUE������NULL
		ReadProcessMemory(INVALID_HANDLE_VALUE,func1,(void *)g_HookOldFunc,5,NULL);
		//����ת��func2������д��g_HookNewFunc�У��޸�������ʹ�����func2�ĺ�����ȥ
		g_HookNewFunc[0] = 0xe9;		//���jmpָ��
		*(DWORD *)(g_HookNewFunc + 1) = (DWORD)func2 - (DWORD)func1 - 5;	//���func2������ַ
		WriteProcessMemory(INVALID_HANDLE_VALUE, func1, g_HookNewFunc, 5, NULL);	//��װ�������g_HookNewFuncд��func1�У�ʵ����ת��HOOK��
		func1();
		system("pause");
		return 0;
	}