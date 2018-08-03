#include "iic.h"
#include "delay.h"
#include "interface.h"

//IIC��ַ����

u16 IIC_Addr[Addr_num]={0};

/*
*******************************************************************************************
* �� �� ��: IIC_Addr_Init
* ����˵��: ��ʼ����ַ
* �� ��: ��
* �� �� ֵ: ��
*******************************************************************************************
*/
static void IIC_Addr_Init(void)
{
	IIC_Addr[0] 	=	 0;   										//INPUT_First�����ݴ�ŵ�ַ
	IIC_Addr[1]		=	IIC_Addr[0] + sizeof(Input_First_data);		//IN1_Second�����ݴ�ŵ�ַ
	IIC_Addr[2]  	=	IIC_Addr[1] + sizeof(Input_Data);    		//IN2_Second�����ݴ�ŵ�ַ
	IIC_Addr[3]  	=	IIC_Addr[2] + sizeof(Input_Data);    		//IN3_Second�����ݴ�ŵ�ַ
	IIC_Addr[4]  	=	IIC_Addr[3] + sizeof(Input_Data);    		//IN4_Second�����ݴ�ŵ�ַ
	IIC_Addr[5]  	=	IIC_Addr[4] + sizeof(Input_Data);    		//IN5_Second�����ݴ�ŵ�ַ
	IIC_Addr[6]  	=	IIC_Addr[5] + sizeof(Input_Data);    		//IN6_Second�����ݴ�ŵ�ַ
	IIC_Addr[7]  	=	IIC_Addr[6] + sizeof(Input_Data);    		//IN7_Second�����ݴ�ŵ�ַ
	
	IIC_Addr[8]		=	IIC_Addr[7] + sizeof(Input_Data);			//IN1_Third�׵�ַ��ŵ�ַ
	IIC_Addr[9]		=	IIC_Addr[8] + sizeof(Input_Data3);			//IN2_Third�׵�ַ��ŵ�ַ
	IIC_Addr[10]	=	IIC_Addr[9] + sizeof(Input_Data3);			//IN3_Third�׵�ַ��ŵ�ַ
	IIC_Addr[11]	=	IIC_Addr[10] + sizeof(Input_Data3);			//IN4_Third�׵�ַ��ŵ�ַ
	IIC_Addr[12]	=	IIC_Addr[11] + sizeof(Input_Data3);			//IN5_Third�׵�ַ��ŵ�ַ
	IIC_Addr[13]	=	IIC_Addr[12] + sizeof(Input_Data3);			//IN6_Third�׵�ַ��ŵ�ַ
	IIC_Addr[14]	=	IIC_Addr[13] + sizeof(Input_Data3);			//IN7_Third�׵�ַ��ŵ�ַ
	
	IIC_Addr[15]	=	IIC_Addr[14] + sizeof(Input_Data3);			//IN1_Four�׵�ַ��ŵ�ַ
	IIC_Addr[16]	=	IIC_Addr[15] + sizeof(Input_Data4);			//IN2_Four�׵�ַ��ŵ�ַ
	IIC_Addr[17]	=	IIC_Addr[16] + sizeof(Input_Data4);			//IN3_Four�׵�ַ��ŵ�ַ
	IIC_Addr[18]	=	IIC_Addr[17] + sizeof(Input_Data4);			//IN4_Four�׵�ַ��ŵ�ַ
	IIC_Addr[19]	=	IIC_Addr[18] + sizeof(Input_Data4);			//IN5_Four�׵�ַ��ŵ�ַ
	IIC_Addr[20]	=	IIC_Addr[19] + sizeof(Input_Data4);			//IN6_Four�׵�ַ��ŵ�ַ
	IIC_Addr[21]	=	IIC_Addr[20] + sizeof(Input_Data4);			//IN7_Four�׵�ַ��ŵ�ַ
	
	IIC_Addr[22]	=	IIC_Addr[21] + sizeof(Input_Data4);   		//OUT_First���ݴ�ŵ�ַ
	IIC_Addr[23]	=	IIC_Addr[22] + sizeof(Output_First_data);   		//OUT_First���ݴ�ŵ�ַ
	
	
}


#if yehuo_use
/*
*******************************************************************************************
* �� �� ��: IIC_Init
* ����˵��: ��ʼ����ӦIO��
* �� ��: ��
* �� �� ֵ: ��
*******************************************************************************************
*/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(EEPROM_RCC_I2C_PORT, ENABLE);	/* ��GPIOʱ�� */

	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* ��©��� */
	GPIO_Init(EEPROM_GPIO_PORT_I2C, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 �����
	IIC_Addr_Init(); //��ʼ��24C16��Ӧ��ŵ�ַ
}

/*
*******************************************************************************************
* �� �� ��: IIC_Start
* ����˵��: ���Ϳ�ʼ�ź�
* �� ��: ��
* �� �� ֵ: ��
*******************************************************************************************
*/

void IIC_Start(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
	EEPROM_I2C_SDA_1();
	EEPROM_I2C_SCL_1();
	delay_us(4);
	EEPROM_I2C_SDA_0();
	delay_us(4);
	EEPROM_I2C_SCL_0();
	delay_us(4);
}
/*
*******************************************************************************************
* �� �� ��: IIC_Stop
* ����˵��: ����ֹͣ�ź�
* �� ��: ��
* �� �� ֵ: ��
*******************************************************************************************
*/

void IIC_Stop(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	EEPROM_I2C_SDA_0();
	EEPROM_I2C_SCL_1();
	delay_us(4);
	EEPROM_I2C_SDA_1();
	delay_us(4);
	
	
}

/*
*******************************************************************************************
* �� �� ��: IIC_SendByte
* ����˵��: ����һ���ֽ�
* �� ��: ��
* �� �� ֵ: ��
*******************************************************************************************
*/
void IIC_SendByte(u8 _ucByte)
{
	u8 i;
	EEPROM_I2C_SCL_0();
	for(i=0; i<8; i++)
	{
		if(_ucByte & 0x80)
		{
			EEPROM_I2C_SDA_1();
		}
		else
		{
			EEPROM_I2C_SDA_0();
		}
		delay_us(2);
		EEPROM_I2C_SCL_1();
		delay_us(2);
		EEPROM_I2C_SCL_0();
		delay_us(2);
		_ucByte <<= 1; /* ����һ��bit */
	}
	EEPROM_I2C_SDA_1(); //�ͷ����ߣ����Ƿ�����Ӧ��
}


void IIC_SendByte_16(u16 _ucByte)
{
	u8 i;
	EEPROM_I2C_SCL_0();
	for(i=0; i<16; i++)
	{
		if(_ucByte & 0x8000)
		{
			EEPROM_I2C_SDA_1();
		}
		else
		{
			EEPROM_I2C_SDA_0();
		}
		delay_us(2);
		EEPROM_I2C_SCL_1();
		delay_us(2);
		EEPROM_I2C_SCL_0();
		delay_us(2);
		_ucByte <<= 1; /* ����һ��bit */
	}
	EEPROM_I2C_SDA_1(); //�ͷ����ߣ����Ƿ�����Ӧ��
}
/*
*********************************************************************************************************
*	�� �� ��: IIC_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
u8 IIC_ReadByte(void)
{
	u8 i;
	u8 value = 0;
	
	for(i = 0; i < 8; i++)
	{
		value <<= 1;
		EEPROM_I2C_SCL_1();
		delay_us(2);
		if(EEPROM_I2C_SDA_READ())
		{
			value++;
		}
		EEPROM_I2C_SCL_0();
		delay_us(2);
	}
	return value;
}

/*
*********************************************************************************************************
*	�� �� ��: IIC_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
u8 IIC_WaitAck(void)
{
	u8 re;
	u8 time;
	EEPROM_I2C_SDA_1();  /* CPU�ͷ�SDA���� */
	delay_us(2);
	EEPROM_I2C_SCL_1();  /* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	delay_us(2);
	while(EEPROM_I2C_SDA_READ())  /* CPU��ȡSDA����״̬ */
	{
		time++;
		if(time>250)
		{
			IIC_Stop();
			return 1;   //��Ӧ��
		}   
	}

	EEPROM_I2C_SCL_0();
	delay_us(2);
	return 0;          //��Ӧ��
}

/*
*********************************************************************************************************
*	�� �� ��: IIC_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void IIC_Ack(void)
{
	EEPROM_I2C_SDA_0();  /* CPU����SDA = 0 */
	delay_us(2);
	EEPROM_I2C_SCL_1();  /* CPU����1��ʱ�� */
	delay_us(2);
	EEPROM_I2C_SCL_0();
	delay_us(2);
	EEPROM_I2C_SDA_1(); /* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: IIC_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void IIC_NAck(void)
{
	EEPROM_I2C_SDA_1(); /* CPU����SDA = 1 */
	delay_us(2);
	EEPROM_I2C_SCL_1();
	delay_us(2);
	EEPROM_I2C_SCL_0();
	delay_us(2);
}

#else
/*************************************************24C16�豸**********************************************/


//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//ʹ��GPIOBʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 �����
	IIC_Addr_Init();
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	delay_us(1);
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

#endif


