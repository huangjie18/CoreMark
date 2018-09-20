#include "systick.h"

static volatile uint32_t sysTickMillis = 0;
static uint32_t sysTickPerUs = 72;//系统内核时钟 ，单位（Mhz）
uint32_t idleMax=0;

void delay_x_ms(uint32_t xms)
{
	
	uint32_t x,i;
	for(i=0;i<xms;i++){
	if(idleMax!=0&&idleMax>700){
	x=idleMax;
	}else{
	x=732;//约等于1ms
	}
	while(x--){
	}
	}
}
void initSystick(void)
{
//	sysTickPerUs = SystemCoreClock / 1000000;
	SysTick_Config(SystemCoreClock / 1000);//1ms中断
}


static  int systick_check_underflow(void)
{
    return SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
}

extern __IO uint32_t counter;
void SysTick_Handler(void)
{
//    __disable_irq();
//    systick_check_underflow();
//    sysTickMillis++;
//    __enable_irq();
//Ticks++;
   counter++;
}

unsigned int millis(void)
{
    return sysTickMillis;
}


unsigned int micros(void)
{
    uint32_t cycle, timeMs;

    do
    {
        timeMs = sysTickMillis;
        cycle = SysTick->VAL;
        __ASM volatile("nop");
        __ASM volatile("nop");
    }
    while (timeMs != sysTickMillis);

    if (systick_check_underflow())
    {
        timeMs++;
        cycle = SysTick->VAL;
    }

    return (timeMs * 1000) + (SysTick->LOAD + 1 - cycle) / sysTickPerUs;
}


int GetIdleMax(void)
{
  unsigned int t0 = millis();
	unsigned int lastTime;
	int idleLoops;
	int idleMax;
  while (millis() == t0)
        ;

  lastTime = micros();
  idleLoops = 0;

  __disable_irq();

	while (1)
	{
		unsigned int currentTime;
		unsigned int timePassed;
		idleLoops++;
		currentTime = micros();
		timePassed = currentTime - lastTime;

		if (timePassed >= 500U) //获取500 us 空循环计数值
		{
				break;
		}
	 }

    __enable_irq();
		
    idleMax = 2 * idleLoops; //  每毫秒下的空闲最大计数值
    idleLoops = 0;

    return idleMax;
}

