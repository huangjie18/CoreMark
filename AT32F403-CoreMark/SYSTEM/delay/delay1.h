#ifndef __DELAY_H
#define __DELAY_H
/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f10x.h"

/* 函 数 定 义  --------------------------------------------------------------*/
void delay_init(u8 SYSCLK);  //延时初始化函数
void delay_ms(u32 nms);      //延时ms函数
void delay_us(u32 nus);      //延时us函数
#endif
