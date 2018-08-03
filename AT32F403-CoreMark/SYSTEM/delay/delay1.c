/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： delay.c
  * @作者       ： JieHuaHuang
  * @库版本     ： V0.0.0
  * @文件版本   ： V0.0.0
  * @日期       ： 2018年2月28
  * @摘要       ： 延时函数的编写,利用滴答定时器SysTick
  ******************************************************************************/

/* 包含的头文件 --------------------------------------------------------------*/
#include "delay.h"

/* 全局变量定义 --------------------------------------------------------------*/
static u8 fac_us = 0;
static u16 fac_ms = 0;

/************************************************
函数名称 ： delay_init
功    能 ： 延时函数初始化
参    数 ： 系统的时钟频率
返 回 值 ： 无
*************************************************/
void delay_init(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //设置滴答定时器的时钟源为AHB的8分频
	fac_us = SYSCLK / 8;
}

/************************************************
函数名称 ： delay_us
功    能 ： 延时us级
参    数 ： 延时多少us
返 回 值 ： 无
*************************************************/
void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus * fac_us; 					//时间加载
	SysTick->VAL = 0x00;        					//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数
	do
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));		//等待时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL = 0X00;      					 //清空计数器
}

/************************************************
函数名称 ： delay_ms
功    能 ： 延时ms级
参    数 ： 延时多少ms
返 回 值 ： 无
注    意 ： SysTick->LOAD为24位寄存器，即是(nms*1000*(SYSTICK/8))<=0XFFFFFF
			当72M条件下，nms<=1864
			所以采用分段延时来增大可延时范围
*************************************************/
void gd_delay_ms(u32 ms)
{
	u8 repeat = ms / 1000; //得到要延时多少秒
	u16 remain = ms % 1000;
	while (repeat)
	{
		gd_delay_us(1000000); //1s
		repeat--;
	}
	if (remain)
	{
		gd_delay_us(remain * 1000); //延时多少ms
	}
}