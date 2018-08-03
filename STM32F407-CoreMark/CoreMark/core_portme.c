/*
Copyright 2018 Embedded Microprocessor Benchmark Consortium (EEMBC)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Original Author: Shay Gal-on
*/

#include <stdio.h>
#include <stdlib.h>
#include "coremark.h"
#include "sys.h"
#include "usart.h"


#define ITERATIONS 2000         //如果有错请增大此数

#if VALIDATION_RUN
	volatile ee_s32 seed1_volatile=0x3415;
	volatile ee_s32 seed2_volatile=0x3415;
	volatile ee_s32 seed3_volatile=0x66;
#endif
#if PERFORMANCE_RUN
	volatile ee_s32 seed1_volatile=0x0;
	volatile ee_s32 seed2_volatile=0x0;
	volatile ee_s32 seed3_volatile=0x66;
#endif
#if PROFILE_RUN
	volatile ee_s32 seed1_volatile=0x8;
	volatile ee_s32 seed2_volatile=0x8;
	volatile ee_s32 seed3_volatile=0x8;
#endif
	volatile ee_s32 seed4_volatile=ITERATIONS;
	volatile ee_s32 seed5_volatile=0;
/* Porting : Timing functions
	How to capture time and convert to seconds must be ported to whatever is supported by the platform.
	e.g. Read value from on board RTC, read value from cpu clock cycles performance counter etc. 
	Sample implementation for standard time.h and windows.h definitions included.
*/
/* Define : TIMER_RES_DIVIDER
	Divider to trade off timer resolution and total time that can be measured.

	Use lower values to increase resolution, but make sure that overflow does not occur.
	If there are issues with the return value overflowing, increase this value.
	*/
//#define NSECS_PER_SEC CLOCKS_PER_SEC
//#define CORETIMETYPE clock_t 
//#define GETMYTIME(_t) (*_t=clock())
//#define MYTIMEDIFF(fin,ini) ((fin)-(ini))
//#define TIMER_RES_DIVIDER 1
//#define SAMPLE_TIME_IMPLEMENTATION 1
//#define EE_TICKS_PER_SEC (NSECS_PER_SEC / TIMER_RES_DIVIDER)

/** Define Host specific (POSIX), or target specific global time variables. */
//static CORETIMETYPE start_time_val, stop_time_val;
#define EE_TICKS_PER_SEC 1000
/* Function : start_time
	This function will be called right before starting the timed portion of the benchmark.

	Implementation may be capturing a system timer (as implemented in the example code) 
	or zeroing some system parameters - e.g. setting the cpu clocks cycles to 0.
*/
#define SystemCoreClock		72000000
#define SysTick_Counter_Disable ((uint32_t)0xFFFFFFFE)
#define SysTick_Counter_Enable ((uint32_t)0x00000001)
#define SysTick_Counter_Clear ((uint32_t)0x00000000)
__IO uint32_t Tick;

//滴答定时器中断
void SysTick_Handler(void)
{
//  HAL_IncTick();
//	extern __IO uint32_t Tick;
	Tick++;
}

void start_time(void) {
//	GETMYTIME(&start_time_val );   
	Tick = 0;
	SysTick_Config(SystemCoreClock/1000);

}
/* Function : stop_time
	This function will be called right after ending the timed portion of the benchmark.

	Implementation may be capturing a system timer (as implemented in the example code) 
	or other system parameters - e.g. reading the current value of cpu cycles counter.
*/
void stop_time(void) {
//	GETMYTIME(&stop_time_val );     
	SysTick->CTRL &=SysTick_Counter_Disable;
/* Clear the SysTick Counter */
	SysTick->VAL = SysTick_Counter_Clear;	
}
/* Function : get_time
	Return an abstract "ticks" number that signifies time on the system.
	
	Actual value returned may be cpu cycles, milliseconds or any other value,
	as long as it can be converted to seconds by <time_in_secs>.
	This methodology is taken to accomodate any hardware or simulated platform.
	The sample implementation returns millisecs by default, 
	and the resolution is controlled by <TIMER_RES_DIVIDER>
*/
CORE_TICKS get_time(void) {
//	CORE_TICKS elapsed=(CORE_TICKS)(MYTIMEDIFF(stop_time_val, start_time_val));
//	return elapsed;
	CORE_TICKS elapsed =(CORE_TICKS)Tick;
	return elapsed;
}
/* Function : time_in_secs
	Convert the value returned by get_time to seconds.

	The <secs_ret> type is used to accomodate systems with no support for floating point.
	Default implementation implemented by the EE_TICKS_PER_SEC macro above.
*/
secs_ret time_in_secs(CORE_TICKS ticks) {
	secs_ret retval=((secs_ret)ticks) / (secs_ret)EE_TICKS_PER_SEC;
	return retval;
}

ee_u32 default_num_contexts=1;

/* Function : portable_init
	Target specific initialization code 
	Test for some common mistakes.
*/
void portable_init(core_portable *p, int *argc, char *argv[])
{

//	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz
	Stm32_Clock_Init(144,4,4,7);//设置时钟,72Mhz
	uart_init(36,115200);	//串口初始化为115200,改了主频第一个参数也要改为主频的一半
	
	printf("Chip_MHz:%d\r\n",SystemCoreClock);
	printf("The CoreMark is runing,Please Wait...\r\n");
	if (sizeof(ee_ptr_int) != sizeof(ee_u8 *)) {
		ee_printf("ERROR! Please define ee_ptr_int to a type that holds a pointer!\n");
	}
	if (sizeof(ee_u32) != 4) {
		ee_printf("ERROR! Please define ee_u32 to a 32b unsigned type!\n");
	}
	p->portable_id=1;
}
/* Function : portable_fini
	Target specific final code 
*/
void portable_fini(core_portable *p)
{
	p->portable_id=0;
}


