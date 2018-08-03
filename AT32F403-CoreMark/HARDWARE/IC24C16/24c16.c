#include "24c16.h"
#include "iic.h"
#include "delay.h"


u8 AT24CXX_ReadOneByte(u16 ReadAddr);
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);
/*
*********************************************************************************************************
*	�� �� ��: AT24C16_Check
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    �Σ�_Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
*********************************************************************************************************
*/

//u8 AT24C16_Check(void)
//{
//	u8 ucAck;
//	IIC_Start();  //��ʼ�ź�
//	
//	IIC_SendByte(0xA0);  //�豸��ַ
//	ucAck = IIC_WaitAck();  //���Ƿ�Ӧ��
//	
//	IIC_Stop();  //ֹͣ�ź�
//	return ucAck;
//}

/*
*********************************************************************************************************
*	�� �� ��: AT24C16_PageWrite
*	����˵��: ����EEPROMָ����ַд���������ݣ�����ҳд�������д��Ч��
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pWriteBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
u8 AT24C16_PageWrite(u8 *_pWriteBuf,u16 _usAddress,u16 _usSize)
{
	
	#if yehuo_use
	u16 i,m;
	u16 usAddr;
	/* 
		д����EEPROM�������������������ȡ�ܶ��ֽڣ�ÿ��д����ֻ����ͬһ��page��
		����24xx02��page size = 8
		����24xx16, page size = 16
		�򵥵Ĵ�����Ϊ�����ֽ�д����ģʽ��ûд1���ֽڣ������͵�ַ,�ɲο�����ԭ������
		Ϊ���������д��Ч��: ����������page wirte������
	*/
	usAddr = _usAddress;
	for(i = 0; i < _usSize; i++)
	{
		/* �����͵�1���ֽڻ���ҳ���׵�ַʱ����Ҫ���·��������źź͵�ַ */
		if((i == 0) || (usAddr & (EEPROM_PAGE_SIZE - 1)) == 0)
		{
			/*���ڣ�������ֹͣ�źţ������ڲ�д������*/
			IIC_Stop();
			
			/*Ӧ��һҳд��󣬸�5��10ms��������һ��д���� 
			ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
				CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
			*/
			for(m = 0; m < 1000; m++)
			{
				/* ��1��������I2C���������ź� */
				IIC_Start();
				
				/* ��2������������ֽڣ���7bit���豸��ַ+ҳ��ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
				IIC_SendByte(0xA0|((usAddr>>8)<<1));
				
				/* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ��,Ӧ����˵��ҳд�Ѿ����*/
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
			
			/* ��4���������ֽڵ�ַ*/
			IIC_SendByte(usAddr&255); //���͵͵�ַ
			
			/* ��5�����ȴ�ACK */
			if(IIC_WaitAck() != 0)
			{
				IIC_Stop();
				return 0;  /* EEPROM������Ӧ�� */
			}
		}
		
		/* ��6������ʼд������ */
		IIC_SendByte(_pWriteBuf[i]);
		
		/* ��7�����ȴ�ACK */
		if(IIC_WaitAck() != 0)
		{
			IIC_Stop();
			return 0;  /* EEPROM������Ӧ�� */
		}
		usAddr++;  /* ��ַ��1 */
	}
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
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
*	�� �� ��: ee_ReadBytes
*	����˵��: �Ӵ���EEPROMָ����ַ����ʼ��ȡ��������
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pReadBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/

u8 AT24C16_PageRead(u8 *_pReadBuf,u16 _usAddress, u16 _usSize)
{
	#if yehuo_use
	u16 i;
	
	/* ���ô���EEPROM�漴��ȡָ�����У�������ȡ�����ֽ� */
	
	/* ��1��������I2C���������ź� */
	IIC_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	IIC_SendByte(0xA0|((_usAddress>>8)<<1)); /* �˴���дָ�� */
	
	/* ��3�����ȴ�ACK */
	if(IIC_WaitAck() != 0)
	{
		IIC_Stop();
		return Fail;
	}
	
	/* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
	IIC_SendByte(_usAddress&255);

	
	/* ��5�����ȴ�ACK */
	if(IIC_WaitAck() != 0)
	{
		IIC_Stop();
		return Fail;
	}
	
	/* ��6������������I2C���ߡ�ǰ��Ĵ����Ŀ����EEPROM���͵�ַ�����濪ʼ��ȡ���� */
	IIC_Start();
	
	/* ��7������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	IIC_SendByte(0xA1|((_usAddress>>8)<<1));  //������
	
	/* ��8�����ȴ�ACK */
	if(IIC_WaitAck() != 0)
	{
		IIC_Stop();
		return Fail;
	}
	
	/* ��9����ѭ����ȡ���� */
	for(i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = IIC_ReadByte();
		
		/* ÿ����1���ֽں���Ҫ����Ack�� ���һ���ֽڲ���ҪAck����Nack */
		if (i != _usSize - 1)
		{
			IIC_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */
		}
		else
		{
			IIC_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
		}
	}
	
	/* ����I2C����ֹͣ�ź� */
	IIC_Stop();
	return 1;	/* ִ�гɹ� */
	
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
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else 
	{
		IIC_Send_Byte(0XA0|((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	
	}		

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr&255);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1|((ReadAddr/256)<<1));           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
   IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		IIC_Send_Byte(0XA0|((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr&255);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
#endif

