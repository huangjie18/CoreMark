#ifndef __DELAY_H
#define __DELAY_H
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"

/* �� �� �� ��  --------------------------------------------------------------*/
void delay_init(u8 SYSCLK);  //��ʱ��ʼ������
void delay_ms(u32 nms);      //��ʱms����
void delay_us(u32 nus);      //��ʱus����
#endif
