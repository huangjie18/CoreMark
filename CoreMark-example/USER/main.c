/******************************************
 * 文件名  ：main.c
 * 描述    ：通过电脑的超级终端向单片机发送数据，单片机将接收到的数据发回电脑，
 *         ：并显示在超级终端上。用的是串口1的中断方式。         
 * 库版本  ：ST3.5.0
 *
*********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "coremark.h"
/*
移植 CoreMark 到ST芯片。
Author： Helix （康朝阳）
date: 2016/10/7
QQ: 547336083

main() 函数见 core_main.c文件的 99行 。

串口1打印输出评测信息。
115200bps，8bit，1 stop， 无校验位。

移植不成功的见启动文件 栈 内存分配大小。
如下：


Stack_Size      EQU     0x00002000  ;0x00000400
									;运行CoreMark需要很大的栈内存，所以改成了0x00002000这么大，原值是0x00000400
									
*/
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
//int main(void)
//{	
//	/* USART1 config 115200 8-N-1 */
//	USART1_Config();
//	NVIC_Configuration();
//#ifdef MY_PRINTF 
//	//如果定义了此宏,那么使用我自己实现的 printf() 打印输出
//	ee_printf("\r\n this is a USART Interrupt demo useing myPrintf() Func\r\n");

//	myPrintf("\r\n***************串口实验--接受中断实验****************\r\n");
//	myPrintf("\r\n描述:使用超级终端来测试比较好,在超级终端敲入一系列字符，\r\n 单片机接收到自己之后直接将接收到的字符按原样打印出来\r\n");
//	myPrintf("\r\n请开始输入字符串:\r\n");
//#else
//	
//	//否则 ，使用系统提供的 printf() 打印输出
//	printf("\r\n this is a USART Interrupt demo useing system printf() Func\r\n");

//	printf("\r\n***************串口实验--接受中断实验****************\r\n");
//	printf("\r\n描述:使用超级终端来测试比较好,在超级终端敲入一系列字符，\r\n 单片机接收到自己之后直接将接收到的字符按原样打印出来\r\n");
//	printf("\r\n请开始输入字符串:\r\n");
//	
//	
//	#endif
//	for(;;)
//	{
//		
//	}
//}
/**********************END OF FILE************/
