#include "led.h"

void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    /* config tft back_light gpio base on the PT4101 BL*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;		
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//±³ºóµÄled
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//µÆÈ«ÁÁ
//	GPIO_SetBits(GPIOC,GPIO_Pin_0);
//	GPIO_SetBits(GPIOC,GPIO_Pin_1);
//	GPIO_SetBits(GPIOC,GPIO_Pin_2);
//	GPIO_SetBits(GPIOC,GPIO_Pin_3);
	LED = 1;
	Input_led_On;
}