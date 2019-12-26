DLL概述
	DLL()，又称为“应用程序拓展”。是一个个独立的模块，包含资源文件、函数等，供应用程序需要时调用。
现阶段，大部分应用程序都会设计成主程序+DLL的框架。当主程序需要哪功能的时候，就会去链接并调用对应
DLL，因为DLL时彼此独立的，所以主程序的加载速度更快。这样也提升了工作效率。
	同时，由于DLL的独立性，使得应用程序的维护和更新变得更加容易，成本大大降低。因为程序只需要更新
相应的模块，而不是整体的更新。

	线程注入，是通过开启远程线程的方式，将DLL加载到目标宿主进程中的常用方式。目前，远程线程注入，
作为WinNT平台下最常见的DLL注入方式之一，在游戏、安全等领域扮演着极为重要的角色。
	由于WinNT系统下进程空间的独立性，获取其他进程的信息，就需要通过进入目标进程空间的方式，而使
用线程注入就可以轻易的实现目的。
	但是滥用线程注入，或者是注入一个具有编写BUG的DLL，很容易对宿主进程的稳定性造成破坏，进而导致
进程崩溃。

链接库分为动态链接库和静态链接库两种，后缀名分别为.dll和.lib
	静态链接库，在运行的时候直接把代码全部加载到程序中。通过如下方式调用
		#include <XXX.h>
		#pragma comment(lib,"XXX.lib")
	而使用动态链接库，在需要的时候加载，在不需要的时候就卸载释放资源
		使用		LoadLibrary		动态加载DLL
		使用		GetProcAddress	获取DLL中导出函数的指针
		最后使用	FreeLibrary		卸载指定DLL
		
在Visual Studio的编译环境下，DLL由分为三类：
	非MFC的DLL	--	即使用SDK API进行编程，能被其他所有语言调用；
	MFC规则DLL	--	可以使用MFC进行编程，能被其他所有语言调用；			使用MFC框架开发，可以使用封装类；
	MFC扩展DLL	--	可以使用MFC进行编程，但只能被用MFC编写的程序调用。	不常用
	
(MFC — Microsoft Foundation Class—Library	是微软用C++对API进行的封装，全部封装成了类，简明了使用)

DLL文件的入口点函数
	BOOL APIENTRY DLLMain(	HMODULE hModule,			//指向DLL本身的实例句柄
							DWORD ul_reason_for_call,	//指明了这个DLL被调用的原因，原因如下：
							LPVOID lpReserved,			//
						)
	{
		return TURE;	
	}
						
=>	DLL_PROCESS_ATTACH:		//当进程第一次链接DLL并通过它的入口点时，会得到这个参数
	DLL_PROCESS_DETACH:		//进程在空间内取消DLL的映射时，会得到这个参数
	DLL_THREAD_ATTACH:		//每当新线程创建时，系统会对所有映射的DLL传此参数调用入口函数
	DLL_THREAD_DETACH:		//每当线程退出或返回时，系统会对所有映射的DLL传此参数要求执行对用清理工作
	

DLL的导出函数		//程序要使用DLL时，要使用的目的函数，也就是调用封装而成的接口，供外界使用
	声明方式：
		extern "C" _declspec(dllexport)
	
DLL导入函数
	声明方式：
		extern "C"	_declspec(dllimport)
		
		
进程调用DLL
	使用LoadLibrary加载进程所需DLL
	HMODULE hMod = LoadLibrary(Dll路径)
	定义导入函数指针
	typedef int (*ADD_IMRORT) (int a,int b);	//定义一个指向返回值为int类型的函数指针
	使用GetProcADDress获得函数入口点
	ADD_IMRORT add_proc = (ADD_IMRORT)GetProcAddress(hMod,"ADD");
	在程序中使用
	int result = add_proc(1,2);
	
GetProcAddress是一个计算机函数，功能是检索指定的动态链接库(DLL)中的输出库函数地址。
	lpProcName参数能够识别DLL中的函数。
FARPROC GetProcAddress(
						HMODULE hModule, // DLL模块句柄
						LPCSTR lpProcName // 函数名
						);
	hModule
		[in] 包含此函数的DLL模块的句柄。LoadLibrary、AfxLoadLibrary 或者GetModuleHandle函数可以返回此句柄。
	lpProcName
		[in] 包含函数名的以NULL结尾的字符串，或者指定函数的序数值。如果此参数是一个序数值，它必须在一个字的低字节，高字节必须为0。
	返回值：
		如果函数调用成功，返回值是DLL中的输出函数地址。
		如果函数调用失败，返回值是NULL。得到进一步的错误信息，调用函数GetLastError。


DLL创建过程
	打开VS	->	新建项目 ->	Win32 ->  确定  -> 下一步 -> (在Win32应用程序向导窗口中	-> 钩中DLL -> 完成)
	在头文件中添加新建头文件
<XXX.h>
[
	#pragma once			//防止重复包含
	/*
	#pragma once 与 #ifndef	的区别
	为了避免同一个文件被include多次

	#ifndef方式
	#pragma once方式

在能够支持这两种方式的编译器上，二者并没有太大的区别，但是两者仍然还是有一些细微的区别。
    方式一：

    #ifndef __SOMEFILE_H__
    #define __SOMEFILE_H__
    ... ... // 一些声明语句
    #endif

    方式二：

    #pragma once
    ... ... // 一些声明语句


    #ifndef的方式依赖于宏名字不能冲突，这不光可以保证同一个文件不会被包含多次，也能保证内容完全相同的两个文件不会被不小心同时包含。当然，缺点就是如果不同头文件的宏名不小心"撞车"，可能就会导致头文件明明存在，编译器却硬说找不到声明的状况

    #pragma once则由编译器提供保证：同一个文件不会被包含多次。注意这里所说的"同一个文件"是指物理上的一个文件，而不是指内容相同的两个文件。带来的好处 是，你不必再费劲想个宏名了，当然也就不会出现宏名碰撞引发的奇怪问题。对应的缺点就是如果某个头文件有多份拷贝，本方法不能保证他们不被重复包含。当 然，相比宏名碰撞引发的"找不到声明"的问题，重复包含更容易被发现并修正。

   方式一由语言支持所以移植性好，方式二 可以避免名字冲突
	*/
	
	#include "stdafx.h"

	#define ExportFunc _declspec(dllexport)

	extern "C"	ExportFunc int Add(int a, int b);
	extern "C"	ExportFunc int Sub(int a, int b);
]

<XXX.cpp>
[
	// sumDLL.cpp : 定义 DLL 应用程序的导出函数。
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

<执行文件中>
[
	HMODULE hModule = LoadLibraryW(_T("D:\\WORK\\测试文件\\sumDLL\\Debug\\sumDLL.dll"));
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

远程线程注入
	注入的可行性：
		kernel32.dll和user32.dll是两个在大部分程序上都会调用的DLL
	同一个DLL，在不同的进程中，不一定被映射（加载）在同一个内存地址下。
	但是kernel32.dll和user.dll例外。他们总是被映射到进程的内存首选地址，
	因此，在所有使用这两个DLL的进程中，这两个DLL的内存地址是相同的。
	我们在本进程获取的kernel.dll中函数的地址，在目标进程中也是一样的
	
	目标进程 -> 传入DLL地址 -> 开启远程线程 -> 加载DLL -> 实现DLL的注入
	
	实现线程注入
		依次使用以下函数：
			OpenProcess				//获取已知进程的句柄
			VirtualAllocEx			//在进程中申请空间
			WriteProcessMessage		//向进程中写入东西
			GetProcAddress			//取得函数在DLL中的地址
			GreateRemoteThreadEx	//在其他进程中创建新线程
			CloseHandle				//关闭句柄
			
	完成线程注入













						
						
						
						
						
						
						
						
						
						
						
						
						
						
						
						
	