#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

#define yehuo_use  1      //0��ʹ��Ұ����룬1ʹ��Ұ�����ע��Ұ�����ֻ֧��24C16ϵ�����µ�
/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define EEPROM_GPIO_PORT_I2C	GPIOB			/* GPIO�˿� */
#define EEPROM_RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define EEPROM_I2C_SCL_PIN		GPIO_Pin_6			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define EEPROM_I2C_SDA_PIN		GPIO_Pin_7			/* ���ӵ�SDA�����ߵ�GPIO */


#define EEPROM_I2C_SCL_1()  EEPROM_GPIO_PORT_I2C->BSRR = EEPROM_I2C_SCL_PIN				/* SCL = 1 */
#define EEPROM_I2C_SCL_0()  EEPROM_GPIO_PORT_I2C->BRR = EEPROM_I2C_SCL_PIN				/* SCL = 0 */
	
#define EEPROM_I2C_SDA_1()  EEPROM_GPIO_PORT_I2C->BSRR = EEPROM_I2C_SDA_PIN				/* SDA = 1 */
#define EEPROM_I2C_SDA_0()  EEPROM_GPIO_PORT_I2C->BRR = EEPROM_I2C_SDA_PIN				/* SDA = 0 */
	
#define EEPROM_I2C_SDA_READ()  ((EEPROM_GPIO_PORT_I2C->IDR & EEPROM_I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */


//IO��������
 
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //����SDA 

#if yehuo_use
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(u8 _ucByte);
u8 IIC_ReadByte(void);
u8 IIC_WaitAck(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_SendByte_16(u16 _ucByte);

#else
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�

#endif


#endif
