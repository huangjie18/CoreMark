#ifndef __SYSTICK_H_
#define __SYSTICK_H_

#include "stm32f10x.h"

extern uint32_t idleMax;

void initSystick(void);

unsigned int millis(void);
unsigned int micros(void);
int GetIdleMax(void);

void delay_x_ms(uint32_t xms);
#endif
