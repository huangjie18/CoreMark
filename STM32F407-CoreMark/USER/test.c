//#include "sys.h"
//#include "delay.h" 
//#include "usart.h" 
//#include "led.h"
////ALIENTEK ̽����STM32F407������ ʵ��4
////����ͨ��ʵ��  
////����֧�֣�www.openedv.com
////������������ӿƼ����޹�˾
//  
//int main(void)
//{ 
//	u8 t;
//	u8 len;	
//	u16 times=0;   
//	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
//	delay_init(168);		//��ʱ��ʼ�� 
//	uart_init(84,115200);	//���ڳ�ʼ��Ϊ115200
//	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�   
//	while(1)
//	{
//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			}
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK ̽����STM32F407������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\r\n");  
//			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(10);   
//		}
//	}
//}

















