#include "key.h"
#include "delay.h"
#include "Interface.h"
#include "led.h"

#define time_over  500000  //655300


u8 KEY_Value[][3] =
{
    {5, 6, 7},
    {3, 2, 4},
    {1},
};


char count_key=0; //ʵ����

//��ť�ṹ��
typedef struct
{
    Encoder_State encoder_state;  //��ť״̬
	

} Encoder_struct;
//��ťʵ����
Encoder_struct Encoder_sample[three+1];  //��������ť
/*
 * ��������KEY_GPIO_Init
 * ����  ����ʼ��������IO����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void KEY_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	

    //��������ģʽ row1,row2,row3
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC6,7,8,���þ���ɨ��


    //�������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��GPIOC9,10,11

    col1 = 1; //ȫ��������Ч������Ϊ�͵�ƽ��ʱ�������Ч����
    col2 = 1;
    col3 = 1;
}

/*
 * ��������KEY_Scan
 * ����  ����������ɨ�躯��
 * ����  ��mode: 1��֧��������0��֧��������
 * ���  ������ֵ
 * ����  ���ڲ�����
 */

u8 KEY_Scan(u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    u8 i, j;
    static u8 key_up = 1;  //�������ɿ���־
    if(mode)key_up = 1;    //֧������
    if(key_up)
    {
        col1 = 1;
        col2 = 1;
        col3 = 1;
        for(i = 1; i < 4; i++)
        {
            switch(i)
            {
                case 1:
					col2 = 1;
                    col1 = 0;
                    col3 = 1;
                    break;
                case 2:
					col3 = 1;
                    col2 = 0;
                    col1 = 1;
                    break;
                case 3:
					col1 = 1;
                    col3 = 0;
                    col2 = 1;
                    break;
                default :
                    break;
            }
            if(row1 == 0 || row2 == 0 || row3 == 0)
            {
                key_up = 0;

                if(row1 == 0)
                {
                    return KEY_Value[0][i - 1];   //��һ��
                }
                else if(row2 == 0)
                {
                    return KEY_Value[1][i - 1];
                }
                else if(row3 == 0)
                {
                    return KEY_Value[2][i - 1];
                }
            }
        }
    }
    else
    {
		//������
        col1 = 0;
        col2 = 0;
        col3 = 0;
        if(row1 == 1 && row2 == 1 && row3 == 1) 
		{
			key_up = 1;
		}
    }
    return 0;
}


//���������ų�ʼ��
void Encoder_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
                                   | GPIO_Pin_5| GPIO_Pin_6; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOE, &GPIO_InitStructure);

}

//���������
/********************
���ԭ��
���Ŷ�Ϊ��������ʱ����ֹʱA,B��Ϊ�ߵ�ƽ��
��A�͵�ƽʱ˵����ť��������ʱ��AΪ�͵�ƽ�����ʱ������B��0��1������������Ϊ��ת����ת��;
B��1��0������������ת����ת��
********************/
/**********************************��ʽ1******************************************/
//��ť������1��⣬ ����ֵΪ��⵽����ť����״̬
Encoder_State Encoder_Check_One(void)
{
	static u8 start_1 = 1;
    u8 encoder_now_b_1 = 0;   //B���ڵ�״̬
    u8 encoder_last_b_1 = 0 ; //B��һ�ε�״̬
    u8 updata1=0;
	u32  time_out=0; //ѭ����ʱ
	
	if(start_1 == 0)
	{
		start_1 = ES1_A;
		return Encoder_static;
	}
	
	if(ES1_A)  //A��B��Ϊ�ߵ�ƽ
	{
		updata1 = 0;
		Encoder_sample[one].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[one].encoder_state;  //������ť״̬
	}
	
	delay_ms(1); //����
	
	if(ES1_A)  //A��B��Ϊ�ߵ�ƽ
	{
		updata1 = 0;
		Encoder_sample[one].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[one].encoder_state;  //������ť״̬
	}
	//������������е�����˵����ť������
	encoder_last_b_1 = ES1_B;  //��¼B�ź�
	while((!ES1_A)&&(time_out<time_over))  //�ȴ�A�ɵͱ��
	{
		encoder_now_b_1 = ES1_B;  //��¼�ȴ��ڼ�� B�ź�
		updata1 = 1;
		time_out++;  //��ֹ������ѭ��
	}
	start_1 = ES1_A;
	
	if(updata1&&(time_out<time_over))
	{
		updata1 = 0;
		if((encoder_last_b_1==0)&&(encoder_now_b_1==1))
		{
			Encoder_sample[one].encoder_state = Encoder1_right;
			
		}
		else if((encoder_last_b_1==1)&&(encoder_now_b_1==0))
		{
			Encoder_sample[one].encoder_state = Encoder1_left;
			
		}
		else
		{
			Encoder_sample[one].encoder_state = Encoder_static; //������
		}
		return Encoder_sample[one].encoder_state;  //������ť״̬
	}
	return Encoder_static;
}


//��ť������2��⣬ ����ֵΪ��⵽����ť����״̬
Encoder_State Encoder_Check_Two(void)
{
	static u8 start_2 = 1;
    u8 encoder_now_b_2 = 0;   //B���ڵ�״̬
	u8 encoder_last_b_2 = 0 ; //B��һ�ε�״̬
	u8 updata2=0;
	u32 time_out=0; //ѭ����ʱ
	
	if(start_2 == 0)
	{
		start_2 = ES2_A;
		return Encoder_static;
	}
	
	if(ES2_A)  //A��B��Ϊ�ߵ�ƽ
	{
		updata2 = 0;
		Encoder_sample[two].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[two].encoder_state;  //������ť״̬
	}
	
	delay_ms(1);
	
	if(ES2_A)  //A��B��Ϊ�ߵ�ƽ
	{
		updata2 = 0;
		Encoder_sample[two].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[two].encoder_state;  //������ť״̬
	}
	//������������е�����˵����ť������
	encoder_last_b_2 = ES2_B;  //��¼B�ź�
	while((!ES2_A)&&(time_out<time_over))  //�ȴ�A�ɵͱ��
	{
		encoder_now_b_2 = ES2_B;  //��¼�ȴ��ڼ�� B�ź�
		updata2 = 1;
		time_out++;    //��ֹ������ѭ��
	}
	start_2 = ES2_A;
	
	if(updata2&&(time_out<time_over))
	{
		updata2 = 0;
		if((encoder_last_b_2==0)&&(encoder_now_b_2==1))
		{
			Encoder_sample[two].encoder_state = Encoder2_right;
			
		}
		else if((encoder_last_b_2==1)&&(encoder_now_b_2==0))
		{
			Encoder_sample[two].encoder_state = Encoder2_left;
			
		}
		else
		{
			Encoder_sample[two].encoder_state = Encoder_static; //������
		}
		
		return Encoder_sample[two].encoder_state;  //������ť״̬
	}
	return Encoder_static;
}
 //������3
Encoder_State Encoder_Check_Three(void)
{
	static u8 start_3 = 1;  //���¿�ʼ
	u8 encoder_now_b_3 = 0;   //B���ڵ�״̬
    u8 encoder_last_b_3 = 0 ; //B��һ�ε�״̬
	u8 updata3=0;
	u32 time_out=0; //ѭ����ʱ
	
	if(start_3 == 0)
	{
		start_3 = ES3_A;
		return Encoder_static;
	}
	
	if(ES3_A)  //A��B��Ϊ�ߵ�ƽ
	{
		updata3 = 0;
		Encoder_sample[three].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[three].encoder_state;  //������ť״̬
	}
	
	delay_ms(1);
	
	if(ES3_A)  //A��B��Ϊ�ߵ�ƽ
	{
		updata3 = 0;
		Encoder_sample[three].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[three].encoder_state;  //������ť״̬
	}
	//������������е�����˵����ť������
	encoder_last_b_3 = ES3_B;  //��¼B�ź�
	while((!ES3_A)&&(time_out<time_over))  //�ȴ�A�ɵͱ��
	{
		encoder_now_b_3 = ES3_B;  //��¼�ȴ��ڼ�� B�ź�
		updata3 = 1;
		time_out++;    //��ֹ������ѭ��
	}
	start_3 = ES3_A;
	
	if(updata3&&(time_out<time_over))
	{
		updata3 = 0;
		if((encoder_last_b_3==0)&&(encoder_now_b_3==1))
		{
			Encoder_sample[three].encoder_state = Encoder3_right;
		}
		else if((encoder_last_b_3==1)&&(encoder_now_b_3==0))
		{
			Encoder_sample[three].encoder_state = Encoder3_left;
		}
		else
		{
			Encoder_sample[three].encoder_state = Encoder_static; //������
		}
		
		return Encoder_sample[three].encoder_state;  //������ť״̬
	}
	return Encoder_static;		
}
/*********************************��ʽ2**********************************************/
//������1
//Encoder_State Encoder_Check_One(void)
//{
//    u8 encoder_now_b_1 = 0;   //B���ڵ�״̬
//    u8 encoder_last_b_1 = 0 ; //B��һ�ε�״̬
//	u8 updata1=0;
//	u32  time_out=0; //ѭ����ʱ
//	
//	if(ES1_A)  //A��B��Ϊ�ߵ�ƽ
//	{
//		updata1 = 0;
//		Encoder_sample[one].encoder_state = Encoder_static; //��������ֹ״̬
//		return Encoder_sample[one].encoder_state;  //������ť״̬
//	}
//	
//	//������������е�����˵����ť������
//	encoder_last_b_1 = ES1_B;  //��¼B�ź�
//	
//	while((!ES1_A)&&(time_out<time_over))time_out++;
//	
//	updata1 = 1;
//	time_out = 0;
//	
//	do{
//		encoder_now_b_1 = ES1_B;
//		time_out++;
//	}while((encoder_last_b_1 == encoder_now_b_1)&&(time_out<time_over));
//	
//	if(updata1&&(time_out<time_over))
//	{
//		updata1 = 0;
//		if((encoder_last_b_1==0)&&(encoder_now_b_1==1))
//		{
//			Encoder_sample[one].encoder_state = Encoder1_right;
//		}
//		else if((encoder_last_b_1==1)&&(encoder_now_b_1==0))
//		{
//			Encoder_sample[one].encoder_state = Encoder1_left;
//		}
//		else
//		{
//			Encoder_sample[one].encoder_state = Encoder_static; //������
//		}
//		return Encoder_sample[one].encoder_state;  //������ť״̬
//	}
//	return Encoder_static;
//}

////������2
//Encoder_State Encoder_Check_Two(void)
//{
//	u8 encoder_now_b_2 = 0;   //B���ڵ�״̬
//	u8 encoder_last_b_2 = 0 ; //B��һ�ε�״̬
//	u8 updata2=0;
//	u32 time_out=0; //ѭ����ʱ
//	
//	if(ES2_A)  //A��B��Ϊ�ߵ�ƽ
//	{
//		updata2 = 0;
//		Encoder_sample[two].encoder_state = Encoder_static; //��������ֹ״̬
//		return Encoder_sample[two].encoder_state;  //������ť״̬
//	}
//	
//	//������������е�����˵����ť������
//	encoder_last_b_2 = ES2_B;  //��¼B�ź�
//	
//	
//	while((!ES2_A)&&(time_out<time_over))time_out++;
//	
//	updata2 = 1;
//	time_out = 0;
//	
//	do{
//		encoder_now_b_2 = ES2_B;
//		time_out++;
//	}while((encoder_last_b_2 == encoder_now_b_2)&&(time_out<time_over));
//	
//	if(updata2&&(time_out<time_over))
//	{
//		updata2 = 0;
//		if((encoder_last_b_2==0)&&(encoder_now_b_2==1))
//		{
//			Encoder_sample[two].encoder_state = Encoder2_right;
//		}
//		else if((encoder_last_b_2==1)&&(encoder_now_b_2==0))
//		{
//			Encoder_sample[two].encoder_state = Encoder2_left;
//		}
//		else
//		{
//			Encoder_sample[two].encoder_state = Encoder_static; //������
//		}
//		return Encoder_sample[two].encoder_state;  //������ť״̬
//	}
//	return Encoder_static;
//}

////��ť������3��⣬ ����ֵΪ��⵽����ť����״̬
//Encoder_State Encoder_Check_Three(void)
//{
//    u8 encoder_now_b_3 = 0;   //B���ڵ�״̬
//    u8 encoder_last_b_3 = 0 ; //B��һ�ε�״̬
//	u8 updata3=0;
//	u32 time_out = 0;
//	

//	
//	if(ES3_A)  //A��B��Ϊ�ߵ�ƽ
//	{
//		updata3=0;
//		Encoder_sample[three].encoder_state = Encoder_static; //��������ֹ״̬
//		return Encoder_sample[three].encoder_state;  //������ť״̬
//	}
//	
//	//������������е�����˵����ť������
//	
//	
//	
//	encoder_last_b_3 = ES3_B;  //������¼B�ź�
////	while((!ES3_A)&&(time_out<65530))  //�ȴ�A�ɵͱ��
////	{
////		encoder_now_b_3 = ES3_B;  //��¼�ȴ��ڼ�� B�ź�
////		updata3 = 1; //�����ж���ť����
////		time_out++;    //��ֹ������ѭ��
////	}
//	while((!ES3_A)&&(time_out<time_over))time_out++;
//	
//	updata3 = 1;
//	time_out = 0;
//	
//	do
//	{
//		encoder_now_b_3 = ES3_B;
//		time_out++;
//	}while((encoder_now_b_3==encoder_last_b_3)&&(time_out<time_over));

//	
//	if(updata3&&(time_out<time_over))
//	{
//		updata3 = 0;
//		if((encoder_last_b_3==0)&&(encoder_now_b_3==1))
//		{
//			Encoder_sample[three].encoder_state = Encoder3_right;
//		}
//		else if((encoder_last_b_3==1)&&(encoder_now_b_3==0))
//		{
//			Encoder_sample[three].encoder_state = Encoder3_left;
//		}
//		else
//		{
//			Encoder_sample[three].encoder_state = Encoder_static; //������
//		}
//		return Encoder_sample[three].encoder_state;  //������ť״̬
//	}
//	
//	return Encoder_static;
//}

/*********************************��ʽ3*********************************************/
//Encoder_State Encoder_Check_Three(void)
//{
//	static u8 last_A = 1;
//    u8 last_B = 1;
//	u8 now_B = 1;
//	u32 time_out = 0;  //��ʱ
//	
//	if(!last_A) //��һ��Ϊ0����ʾ������ѭ��
//	{
//		last_A = ES3_A;
//		return Encoder_static;
//	}
//	
//	if(ES3_A&&ES3_B)
//	{
//		return Encoder_static; //������ť��̬
//	}
//	
//	last_B = ES3_B; //��¼����B��״̬
//	
//	while((!ES3_A)&&(time_out<time_over))time_out++; //�ȴ�A��Ϊ�ߵ�ƽ
//	last_A = ES3_A; //��¼���ڵ�A״̬
//	
//	if(last_A == 1) //���״̬Ϊ1������һ��������ѭ��
//	{
////		time_out = 0;
////		do
////		{
////			now_B = ES3_B; //��¼���µ�B״̬
////			time_out++;
////		}while((last_B == now_B)&&(time_out<time_over));
////		
////		if(time_out>=time_over)
////		{
////			return Encoder_static;
////		}
//		
//		now_B = ES3_B; //��¼���µ�B״̬
//		if((last_B == 0)&&(now_B == 1)) //�Աȣ�B����������
//		{
//			Encoder_sample[three].encoder_state = Encoder3_right;
//		}
//		else if((last_B == 1)&&(now_B == 0)) //B�����½���
//		{
//			Encoder_sample[three].encoder_state = Encoder3_left;
//		}
//		else
//		{
//			Encoder_sample[three].encoder_state = Encoder_static; //������
//		}
//		return Encoder_sample[three].encoder_state;  //������ť״̬
//	}
//	else //������ѭ��
//	{
//		return Encoder_static;
//	}
//	
//	
//	
//}
/***************�µı��������1********************/


//Encoder_State Encoder_Check_Three(void)
//{
//	static u8 last_a = 1;
//	static u8 last_b = 1;
////	static u8 front_flag=0;
////	static u8 back_flag=0;

//	
//	if(ES3_A != last_a)//A�ŷ����仯
//	{
//		delay_ms(2);   //����
//		if(ES3_A != last_a)  //A�ŷ����仯
//		{
//			if(last_a) //˵����A�����½���
//			{
////				key_value_b = ES3_B;
////				if(ES3_B == ES3_A) 
////				{
////					front_flag = 1;
////				}
////				else
////				{
////					back_flag = 1;
////				}
//			}
//			else   //˵��A��������
//			{
//				delay_us(200);
//				count_key++;
//				if(ES3_B)
//				{
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_RIGHT);
//				}
//				else
//				{
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_LEFT);
//				}
//				
//			}
//			WM_Exec();
//			last_a = ES3_A;
//			return 0;
//		}
//	}
//	Encoder_sample[three].encoder_state = Encoder_static; //��������ֹ״̬
//	return Encoder_sample[three].encoder_state;
//	
//	
//}


//Encoder_State Encoder_Check_One(void)
//{
//	static u8 last_a = 1;
//	static u8 last_b = 1;
////	static u8 front_flag=0;
////	static u8 back_flag=0;

//	
//	if(ES1_A != last_a)//A�ŷ����仯
//	{
//		delay_ms(2);   //����
//		if(ES1_A != last_a)  //A�ŷ����仯
//		{
//			if(last_a == 1) //˵����A�����½���
//			{
////				key_value_b = ES3_B;
////				if(ES3_B == ES3_A) 
////				{
////					front_flag = 1;
////				}
////				else
////				{
////					back_flag = 1;
////				}
//			}
//			else   //˵��A��������
//			{
//				delay_ms(1);
//				if(ES1_B)
//				{
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_RIGHT);
//				}
//				else
//				{
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_LEFT);
//				}
//				
//			}
//			WM_Exec();
//			last_a = ES1_A;
//			return 0;
//		}
//	}
//	Encoder_sample[three].encoder_state = Encoder_static; //��������ֹ״̬
//	return Encoder_sample[three].encoder_state;
//	
//	
//}
//Encoder_State Encoder_Check_Three(void)
//{
//	static u8 Last_ES3_A = 1;
//	if(!(ES3_A==Last_ES3_A))
//	{
//		delay_ms(1);
//		if(!(ES3_A==Last_ES3_A))
//		{
//			if(Last_ES3_A==0)
//			{
//				delay_ms(1);
//				if(ES3_B)
//				{
//					Encoder_sample[three].encoder_state = Encoder3_right;
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_RIGHT);
//					WM_Exec();
//				}
//				else
//				{
//					Encoder_sample[three].encoder_state = Encoder3_left;
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_LEFT);
//					WM_Exec();
//				}
//			}
//			Last_ES3_A = ES3_A;
//			return Encoder_sample[three].encoder_state;
//		}
//	}
//	return Encoder_static;
//	
//	

//}