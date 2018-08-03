/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： sys.c
  * @作者       ： JieHuaHuang
  * @库版本     ： V0.0.0
  * @文件版本   ： V0.0.0
  * @日期       ： 2018年2月28
  * @摘要       ： 系统级函数编写
  ******************************************************************************/
/* 包含的头文件 --------------------------------------------------------------*/
#include "sys.h"

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令
//等待中断指令
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

