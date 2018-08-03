#include "24c16.h"
#include "iic.h"
#include "delay.h"


u8 AT24CXX_ReadOneByte(u16 ReadAddr);
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);
/*
*********************************************************************************************************
*	函 数 名: AT24C16_Check
*	功能说明: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
*	形    参：_Address：设备的I2C总线地址
*	返 回 值: 返回值 0 表示正确， 返回1表示未探测到
*********************************************************************************************************
*/

//u8 AT24C16_Check(void)
//{
//	u8 ucAck;
//	IIC_Start();  //开始信号
//	
//	IIC_SendByte(0xA0);  //设备地址
//	ucAck = IIC_WaitAck();  //看是否应答
//	
//	IIC_Stop();  //停止信号
//	return ucAck;
//}

/*
*********************************************************************************************************
*	函 数 名: AT24C16_PageWrite
*	功能说明: 向串行EEPROM指定地址写入若干数据，采用页写操作提高写入效率
*	形    参：_usAddress : 起始地址
*			 _usSize : 数据长度，单位为字节
*			 _pWriteBuf : 存放读到的数据的缓冲区指针
*	返 回 值: 0 表示失败，1表示成功
*********************************************************************************************************
*/
u8 AT24C16_PageWrite(u8 *_pWriteBuf,u16 _usAddress,u16 _usSize)
{
	
	#if yehuo_use
	u16 i,m;
	u16 usAddr;
	/* 
		写串行EEPROM不像读操作可以连续读取很多字节，每次写操作只能在同一个page。
		对于24xx02，page size = 8
		对于24xx16, page size = 16
		简单的处理方法为：按字节写操作模式，没写1个字节，都发送地址,可参考正点原子例程
		为了提高连续写的效率: 本函数采用page wirte操作。
	*/
	usAddr = _usAddress;
	for(i = 0; i < _usSize; i++)
	{
		/* 当发送第1个字节或是页面首地址时，需要重新发起启动信号和地址 */
		if((i == 0) || (usAddr & (EEPROM_PAGE_SIZE - 1)) == 0)
		{
			/*　第０步：发停止信号，启动内部写操作　*/
			IIC_Stop();
			
			/*应在一页写完后，隔5～10ms重新启动一次写操作 
			通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms 			
				CLK频率为200KHz时，查询次数为30次左右
			*/
			for(m = 0; m < 1000; m++)
			{
				/* 第1步：发起I2C总线启动信号 */
				IIC_Start();
				
				/* 第2步：发起控制字节，高7bit是设备地址+页地址，bit0是读写控制位，0表示写，1表示读 */
				IIC_SendByte(0xA0|((usAddr>>8)<<1));
				
				/* 第3步：发送一个时钟，判断器件是否正确应答,应答了说明页写已经完成*/
				if(IIC_WaitAck() == 0)
				{
					break;
				}
				
			}
			if(m == 1000)
			{
				IIC_Stop();
				return 0;
			}
			
			/* 第4步：发送字节地址*/
			IIC_SendByte(usAddr&255); //发送低地址
			
			/* 第5步：等待ACK */
			if(IIC_WaitAck() != 0)
			{
				IIC_Stop();
				return 0;  /* EEPROM器件无应答 */
			}
		}
		
		/* 第6步：开始写入数据 */
		IIC_SendByte(_pWriteBuf[i]);
		
		/* 第7步：等待ACK */
		if(IIC_WaitAck() != 0)
		{
			IIC_Stop();
			return 0;  /* EEPROM器件无应答 */
		}
		usAddr++;  /* 地址增1 */
	}
	/* 命令执行成功，发送I2C总线停止信号 */
	IIC_Stop();
	return 1;
	
	#else
	while(_usSize--)
	{
		AT24CXX_WriteOneByte(_usAddress,*_pWriteBuf);
		_usAddress++;
		_pWriteBuf++;
	}
	#endif
}

/*
*********************************************************************************************************
*	函 数 名: ee_ReadBytes
*	功能说明: 从串行EEPROM指定地址处开始读取若干数据
*	形    参：_usAddress : 起始地址
*			 _usSize : 数据长度，单位为字节
*			 _pReadBuf : 存放读到的数据的缓冲区指针
*	返 回 值: 0 表示失败，1表示成功
*********************************************************************************************************
*/

u8 AT24C16_PageRead(u8 *_pReadBuf,u16 _usAddress, u16 _usSize)
{
	#if yehuo_use
	u16 i;
	
	/* 采用串行EEPROM随即读取指令序列，连续读取若干字节 */
	
	/* 第1步：发起I2C总线启动信号 */
	IIC_Start();
	
	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	IIC_SendByte(0xA0|((_usAddress>>8)<<1)); /* 此处是写指令 */
	
	/* 第3步：等待ACK */
	if(IIC_WaitAck() != 0)
	{
		IIC_Stop();
		return Fail;
	}
	
	/* 第4步：发送字节地址，24C02只有256字节，因此1个字节就够了，如果是24C04以上，那么此处需要连发多个地址 */
	IIC_SendByte(_usAddress&255);

	
	/* 第5步：等待ACK */
	if(IIC_WaitAck() != 0)
	{
		IIC_Stop();
		return Fail;
	}
	
	/* 第6步：重新启动I2C总线。前面的代码的目的向EEPROM传送地址，下面开始读取数据 */
	IIC_Start();
	
	/* 第7步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	IIC_SendByte(0xA1|((_usAddress>>8)<<1));  //读命令
	
	/* 第8步：等待ACK */
	if(IIC_WaitAck() != 0)
	{
		IIC_Stop();
		return Fail;
	}
	
	/* 第9步：循环读取数据 */
	for(i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = IIC_ReadByte();
		
		/* 每读完1个字节后，需要发送Ack， 最后一个字节不需要Ack，发Nack */
		if (i != _usSize - 1)
		{
			IIC_Ack();	/* 中间字节读完后，CPU产生ACK信号(驱动SDA = 0) */
		}
		else
		{
			IIC_NAck();	/* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
		}
	}
	
	/* 发送I2C总线停止信号 */
	IIC_Stop();
	return 1;	/* 执行成功 */
	
	#else
	while(_usSize)
	{
		*_pReadBuf++=AT24CXX_ReadOneByte(_usAddress++);	
		_usSize--;
	}
	#endif
}


#if yehuo_use
#else
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//发送高地址
		IIC_Wait_Ack();		 
	}else 
	{
		IIC_Send_Byte(0XA0|((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	
	}		

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr&255);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1|((ReadAddr/256)<<1));           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
   IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//发送高地址
 	}else
	{
		IIC_Send_Byte(0XA0|((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr&255);   //发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}
#endif

