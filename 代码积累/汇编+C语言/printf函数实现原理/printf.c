//带有汇编指令的代码编译的时候添加 "-masm=intel";
	//gcc 1.c -o 1.out -masm=intel
		//代表该汇编是按因特尔的标准编写

int main()
{
	char A[] = {"Hello\n"};
	__asm__(
			"mov rax, 1 \n\t"
			"mov rdi, 1 \n\t"
			"syscall \n\t"
			:
			:"S" (A), "d"(6)
			);
	/*
		__asm__(); 	//它是汇编代码的一个标识，用来区分汇编代码和C代码
					//如果我们不按照这个格式写
					//那么，C实现就无法判断这段代码到底是汇编代码，还是C代码
					//那么，C实现就会按照C语言的语法对代码进行解析，这必然会导致编译失败
					
		"  \n\t"	//它和C语言中的 ; 作用相同，表示 mov rax,1 是一条完整的代码
		
		"mov rax, 1 \n\t" 	//将rax寄存器的值设置为1 --> 系统服务号 --> 1号系统服务 --> 写文件和设备服务
		"mov rdi, 1 \n\t" 	//将rdi寄存器的值设置为1 --> 写哪个文件和设备？ --> 写控制台
		
		"syscall \n\t"		//向操作系统请求系统服务
		
		"S" (A) 			//S表示rsi寄存器，用于存储要显示字符的内存地址
		"d"(6)				//d表示rdx寄存器，用于存储要显示的字符数量
		
		：	//寄存器和C语言的变量进行交换数据的指令前面要加上冒号，以示和其他指令的区别
		
	*/
	return 0;
}
 
 
void m_printf(char *A)
{
	int B = 0;
	for(char *C = A; *C++ != '\0'; B++);
	
	__asm__(
			"mov rax, 1 \n\t"
			"mov rdi, 1 \n\t"
			"syscall \n\t"
			:
			:"S" (A), "d"(B)
			);
}
 
int main(void)
{
	m_printf("123\n");
	m_printf("456\n");
	m_printf("789\n");
	
	return 0;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 