#include "iic.h"
#include "delay.h"
#include "interface.h"

//IIC地址设置

u16 IIC_Addr[Addr_num]={0};

/*
*******************************************************************************************
* 函 数 名: IIC_Addr_Init
* 功能说明: 初始化地址
* 形 参: 无
* 返 回 值: 无
*******************************************************************************************
*/
static void IIC_Addr_Init(void)
{
	IIC_Addr[0] 	=	 0;   										//INPUT_First首数据存放地址
	IIC_Addr[1]		=	IIC_Addr[0] + sizeof(Input_First_data);		//IN1_Second首数据存放地址
	IIC_Addr[2]  	=	IIC_Addr[1] + sizeof(Input_Data);    		//IN2_Second首数据存放地址
	IIC_Addr[3]  	=	IIC_Addr[2] + sizeof(Input_Data);    		//IN3_Second首数据存放地址
	IIC_Addr[4]  	=	IIC_Addr[3] + sizeof(Input_Data);    		//IN4_Second首数据存放地址
	IIC_Addr[5]  	=	IIC_Addr[4] + sizeof(Input_Data);    		//IN5_Second首数据存放地址
	IIC_Addr[6]  	=	IIC_Addr[5] + sizeof(Input_Data);    		//IN6_Second首数据存放地址
	IIC_Addr[7]  	=	IIC_Addr[6] + sizeof(Input_Data);    		//IN7_Second首数据存放地址
	
	IIC_Addr[8]		=	IIC_Addr[7] + sizeof(Input_Data);			//IN1_Third首地址存放地址
	IIC_Addr[9]		=	IIC_Addr[8] + sizeof(Input_Data3);			//IN2_Third首地址存放地址
	IIC_Addr[10]	=	IIC_Addr[9] + sizeof(Input_Data3);			//IN3_Third首地址存放地址
	IIC_Addr[11]	=	IIC_Addr[10] + sizeof(Input_Data3);			//IN4_Third首地址存放地址
	IIC_Addr[12]	=	IIC_Addr[11] + sizeof(Input_Data3);			//IN5_Third首地址存放地址
	IIC_Addr[13]	=	IIC_Addr[12] + sizeof(Input_Data3);			//IN6_Third首地址存放地址
	IIC_Addr[14]	=	IIC_Addr[13] + sizeof(Input_Data3);			//IN7_Third首地址存放地址
	
	IIC_Addr[15]	=	IIC_Addr[14] + sizeof(Input_Data3);			//IN1_Four首地址存放地址
	IIC_Addr[16]	=	IIC_Addr[15] + sizeof(Input_Data4);			//IN2_Four首地址存放地址
	IIC_Addr[17]	=	IIC_Addr[16] + sizeof(Input_Data4);			//IN3_Four首地址存放地址
	IIC_Addr[18]	=	IIC_Addr[17] + sizeof(Input_Data4);			//IN4_Four首地址存放地址
	IIC_Addr[19]	=	IIC_Addr[18] + sizeof(Input_Data4);			//IN5_Four首地址存放地址
	IIC_Addr[20]	=	IIC_Addr[19] + sizeof(Input_Data4);			//IN6_Four首地址存放地址
	IIC_Addr[21]	=	IIC_Addr[20] + sizeof(Input_Data4);			//IN7_Four首地址存放地址
	
	IIC_Addr[22]	=	IIC_Addr[21] + sizeof(Input_Data4);   		//OUT_First数据存放地址
	IIC_Addr[23]	=	IIC_Addr[22] + sizeof(Output_First_data);   		//OUT_First数据存放地址
	
	
}


#if yehuo_use
/*
*******************************************************************************************
* 函 数 名: IIC_Init
* 功能说明: 初始化对应IO口
* 形 参: 无
* 返 回 值: 无
*******************************************************************************************
*/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(EEPROM_RCC_I2C_PORT, ENABLE);	/* 打开GPIO时钟 */

	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* 开漏输出 */
	GPIO_Init(EEPROM_GPIO_PORT_I2C, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
	IIC_Addr_Init(); //初始化24C16对应存放地址
}

/*
*******************************************************************************************
* 函 数 名: IIC_Start
* 功能说明: 发送开始信号
* 形 参: 无
* 返 回 值: 无
*******************************************************************************************
*/

void IIC_Start(void)
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
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
* 函 数 名: IIC_Stop
* 功能说明: 发送停止信号
* 形 参: 无
* 返 回 值: 无
*******************************************************************************************
*/

void IIC_Stop(void)
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	EEPROM_I2C_SDA_0();
	EEPROM_I2C_SCL_1();
	delay_us(4);
	EEPROM_I2C_SDA_1();
	delay_us(4);
	
	
}

/*
*******************************************************************************************
* 函 数 名: IIC_SendByte
* 功能说明: 发送一个字节
* 形 参: 无
* 返 回 值: 无
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
		_ucByte <<= 1; /* 左移一个bit */
	}
	EEPROM_I2C_SDA_1(); //释放总线，看是否会产生应答
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
		_ucByte <<= 1; /* 左移一个bit */
	}
	EEPROM_I2C_SDA_1(); //释放总线，看是否会产生应答
}
/*
*********************************************************************************************************
*	函 数 名: IIC_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
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
*	函 数 名: IIC_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
u8 IIC_WaitAck(void)
{
	u8 re;
	u8 time;
	EEPROM_I2C_SDA_1();  /* CPU释放SDA总线 */
	delay_us(2);
	EEPROM_I2C_SCL_1();  /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	delay_us(2);
	while(EEPROM_I2C_SDA_READ())  /* CPU读取SDA口线状态 */
	{
		time++;
		if(time>250)
		{
			IIC_Stop();
			return 1;   //无应答
		}   
	}

	EEPROM_I2C_SCL_0();
	delay_us(2);
	return 0;          //有应答
}

/*
*********************************************************************************************************
*	函 数 名: IIC_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void IIC_Ack(void)
{
	EEPROM_I2C_SDA_0();  /* CPU驱动SDA = 0 */
	delay_us(2);
	EEPROM_I2C_SCL_1();  /* CPU产生1个时钟 */
	delay_us(2);
	EEPROM_I2C_SCL_0();
	delay_us(2);
	EEPROM_I2C_SDA_1(); /* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*	函 数 名: IIC_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void IIC_NAck(void)
{
	EEPROM_I2C_SDA_1(); /* CPU驱动SDA = 1 */
	delay_us(2);
	EEPROM_I2C_SCL_1();
	delay_us(2);
	EEPROM_I2C_SCL_0();
	delay_us(2);
}

#else
/*************************************************24C16设备**********************************************/


//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
	IIC_Addr_Init();
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	delay_us(1);
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

#endif


