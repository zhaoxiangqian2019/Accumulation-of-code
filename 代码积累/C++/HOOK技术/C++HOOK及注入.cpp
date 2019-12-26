//访问别人的内存
	有两种方式：
		①官方的	使用系统API	跨进程读取数据	
		②注入

	注入DLL的方式：
		远线程注入
			步骤:
				1、知道他的进程PID
				2、打开进程
				3、在对方的进程中分配一块内存供我们写入东西
				4、往分配好的内存中写入我们需要写入的数据
				5、让他执行我们刚刚写入的东西
		APC注入					//原理：Sleep	在程序等待的这段时间，会进入APC，在APC里加入代码，实现注入
		DLL劫持注入				//程序在加载DLL的时候，会优先查找当前目录下的DLL，若没有，再去系统目录下查找
								//			因此DLL劫持注入的方法是(用user32.dll为例)
								//					①在当前目录下伪造一个usre32.dll
								//							注入我们需要需要注入的DLL ——> 我们要的功能
								//					②再加载系统的 user32.dll 具体的功能
												
		输入法注入				//自己做一个简单的输入法，通过输入法实现注入
		

通过修改汇编指令来修改函数的执行步骤：
eg：
	typedef void (*FUNC)();

	FUNC OldFunc = NULL;
	FUNC NewFunc = NULL;
	BYTE g_HookOldFunc[5] = { 0 };
	BYTE g_HookNewFunc[5] = { 0 };

	void func1()
	{
		cout << "哈哈哈" << endl;
	}

	void func2()
	{
		cout << "呵呵呵" << endl;
	}
	int main()
	{
		OldFunc = func1;
		NewFunc = func2;
		func1();
		
		//将func1的前5条汇编指令读到g_HookOldFunc中		INVALID_HANDLE_VALUE类似于NULL
		ReadProcessMemory(INVALID_HANDLE_VALUE,func1,(void *)g_HookOldFunc,5,NULL);
		//将跳转到func2的命令写入g_HookNewFunc中，修改入口命令，使其调到func2的函数中去
		g_HookNewFunc[0] = 0xe9;		//添加jmp指令
		*(DWORD *)(g_HookNewFunc + 1) = (DWORD)func2 - (DWORD)func1 - 5;	//添加func2函数地址
		WriteProcessMemory(INVALID_HANDLE_VALUE, func1, g_HookNewFunc, 5, NULL);	//将装有命令的g_HookNewFunc写入func1中，实现跳转（HOOK）
		func1();
		system("pause");
		return 0;
	}