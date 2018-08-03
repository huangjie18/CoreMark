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


char count_key=0; //实验用

//旋钮结构体
typedef struct
{
    Encoder_State encoder_state;  //旋钮状态
	

} Encoder_struct;
//旋钮实例化
Encoder_struct Encoder_sample[three+1];  //有三个旋钮
/*
 * 函数名：KEY_GPIO_Init
 * 描述  ：初始化按键的IO引脚
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void KEY_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	

    //配置输入模式 row1,row2,row3
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC6,7,8,采用矩阵扫描


    //配置输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化GPIOC9,10,11

    col1 = 1; //全部按键无效操作，为低电平的时候才是有效操作
    col2 = 1;
    col3 = 1;
}

/*
 * 函数名：KEY_Scan
 * 描述  ：按键矩阵扫描函数
 * 输入  ：mode: 1则支持连按，0不支持连按；
 * 输出  ：按键值
 * 调用  ：内部调用
 */

u8 KEY_Scan(u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    u8 i, j;
    static u8 key_up = 1;  //按键按松开标志
    if(mode)key_up = 1;    //支持连按
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
                    return KEY_Value[0][i - 1];   //第一行
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
		//按下了
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


//编码器引脚初始化
void Encoder_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
                                   | GPIO_Pin_5| GPIO_Pin_6; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOE, &GPIO_InitStructure);

}

//编码器检测
/********************
检测原理：
引脚都为上拉输入时，静止时A,B都为高电平，
当A低电平时说明旋钮动作，这时在A为低电平的这段时间里，如果B从0到1上拉动作，则为右转（左转）;
B从1到0下拉动作，左转（右转）
********************/
/**********************************方式1******************************************/
//旋钮编码器1检测， 返回值为检测到的旋钮动作状态
Encoder_State Encoder_Check_One(void)
{
	static u8 start_1 = 1;
    u8 encoder_now_b_1 = 0;   //B现在的状态
    u8 encoder_last_b_1 = 0 ; //B上一次的状态
    u8 updata1=0;
	u32  time_out=0; //循环超时
	
	if(start_1 == 0)
	{
		start_1 = ES1_A;
		return Encoder_static;
	}
	
	if(ES1_A)  //A和B都为高电平
	{
		updata1 = 0;
		Encoder_sample[one].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[one].encoder_state;  //返回旋钮状态
	}
	
	delay_ms(1); //消抖
	
	if(ES1_A)  //A和B都为高电平
	{
		updata1 = 0;
		Encoder_sample[one].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[one].encoder_state;  //返回旋钮状态
	}
	//如果程序能运行到这里说明旋钮动作了
	encoder_last_b_1 = ES1_B;  //记录B信号
	while((!ES1_A)&&(time_out<time_over))  //等待A由低变高
	{
		encoder_now_b_1 = ES1_B;  //记录等待期间的 B信号
		updata1 = 1;
		time_out++;  //防止进入死循环
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
			Encoder_sample[one].encoder_state = Encoder_static; //错误检测
		}
		return Encoder_sample[one].encoder_state;  //返回旋钮状态
	}
	return Encoder_static;
}


//旋钮编码器2检测， 返回值为检测到的旋钮动作状态
Encoder_State Encoder_Check_Two(void)
{
	static u8 start_2 = 1;
    u8 encoder_now_b_2 = 0;   //B现在的状态
	u8 encoder_last_b_2 = 0 ; //B上一次的状态
	u8 updata2=0;
	u32 time_out=0; //循环超时
	
	if(start_2 == 0)
	{
		start_2 = ES2_A;
		return Encoder_static;
	}
	
	if(ES2_A)  //A和B都为高电平
	{
		updata2 = 0;
		Encoder_sample[two].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[two].encoder_state;  //返回旋钮状态
	}
	
	delay_ms(1);
	
	if(ES2_A)  //A和B都为高电平
	{
		updata2 = 0;
		Encoder_sample[two].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[two].encoder_state;  //返回旋钮状态
	}
	//如果程序能运行到这里说明旋钮动作了
	encoder_last_b_2 = ES2_B;  //记录B信号
	while((!ES2_A)&&(time_out<time_over))  //等待A由低变高
	{
		encoder_now_b_2 = ES2_B;  //记录等待期间的 B信号
		updata2 = 1;
		time_out++;    //防止进入死循环
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
			Encoder_sample[two].encoder_state = Encoder_static; //错误检测
		}
		
		return Encoder_sample[two].encoder_state;  //返回旋钮状态
	}
	return Encoder_static;
}
 //编码器3
Encoder_State Encoder_Check_Three(void)
{
	static u8 start_3 = 1;  //重新开始
	u8 encoder_now_b_3 = 0;   //B现在的状态
    u8 encoder_last_b_3 = 0 ; //B上一次的状态
	u8 updata3=0;
	u32 time_out=0; //循环超时
	
	if(start_3 == 0)
	{
		start_3 = ES3_A;
		return Encoder_static;
	}
	
	if(ES3_A)  //A和B都为高电平
	{
		updata3 = 0;
		Encoder_sample[three].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[three].encoder_state;  //返回旋钮状态
	}
	
	delay_ms(1);
	
	if(ES3_A)  //A和B都为高电平
	{
		updata3 = 0;
		Encoder_sample[three].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[three].encoder_state;  //返回旋钮状态
	}
	//如果程序能运行到这里说明旋钮动作了
	encoder_last_b_3 = ES3_B;  //记录B信号
	while((!ES3_A)&&(time_out<time_over))  //等待A由低变高
	{
		encoder_now_b_3 = ES3_B;  //记录等待期间的 B信号
		updata3 = 1;
		time_out++;    //防止进入死循环
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
			Encoder_sample[three].encoder_state = Encoder_static; //错误检测
		}
		
		return Encoder_sample[three].encoder_state;  //返回旋钮状态
	}
	return Encoder_static;		
}
/*********************************方式2**********************************************/
//编码器1
//Encoder_State Encoder_Check_One(void)
//{
//    u8 encoder_now_b_1 = 0;   //B现在的状态
//    u8 encoder_last_b_1 = 0 ; //B上一次的状态
//	u8 updata1=0;
//	u32  time_out=0; //循环超时
//	
//	if(ES1_A)  //A和B都为高电平
//	{
//		updata1 = 0;
//		Encoder_sample[one].encoder_state = Encoder_static; //编码器静止状态
//		return Encoder_sample[one].encoder_state;  //返回旋钮状态
//	}
//	
//	//如果程序能运行到这里说明旋钮动作了
//	encoder_last_b_1 = ES1_B;  //记录B信号
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
//			Encoder_sample[one].encoder_state = Encoder_static; //错误检测
//		}
//		return Encoder_sample[one].encoder_state;  //返回旋钮状态
//	}
//	return Encoder_static;
//}

////编码器2
//Encoder_State Encoder_Check_Two(void)
//{
//	u8 encoder_now_b_2 = 0;   //B现在的状态
//	u8 encoder_last_b_2 = 0 ; //B上一次的状态
//	u8 updata2=0;
//	u32 time_out=0; //循环超时
//	
//	if(ES2_A)  //A和B都为高电平
//	{
//		updata2 = 0;
//		Encoder_sample[two].encoder_state = Encoder_static; //编码器静止状态
//		return Encoder_sample[two].encoder_state;  //返回旋钮状态
//	}
//	
//	//如果程序能运行到这里说明旋钮动作了
//	encoder_last_b_2 = ES2_B;  //记录B信号
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
//			Encoder_sample[two].encoder_state = Encoder_static; //错误检测
//		}
//		return Encoder_sample[two].encoder_state;  //返回旋钮状态
//	}
//	return Encoder_static;
//}

////旋钮编码器3检测， 返回值为检测到的旋钮动作状态
//Encoder_State Encoder_Check_Three(void)
//{
//    u8 encoder_now_b_3 = 0;   //B现在的状态
//    u8 encoder_last_b_3 = 0 ; //B上一次的状态
//	u8 updata3=0;
//	u32 time_out = 0;
//	

//	
//	if(ES3_A)  //A和B都为高电平
//	{
//		updata3=0;
//		Encoder_sample[three].encoder_state = Encoder_static; //编码器静止状态
//		return Encoder_sample[three].encoder_state;  //返回旋钮状态
//	}
//	
//	//如果程序能运行到这里说明旋钮动作了
//	
//	
//	
//	encoder_last_b_3 = ES3_B;  //立即记录B信号
////	while((!ES3_A)&&(time_out<65530))  //等待A由低变高
////	{
////		encoder_now_b_3 = ES3_B;  //记录等待期间的 B信号
////		updata3 = 1; //可以判断旋钮动作
////		time_out++;    //防止进入死循环
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
//			Encoder_sample[three].encoder_state = Encoder_static; //错误检测
//		}
//		return Encoder_sample[three].encoder_state;  //返回旋钮状态
//	}
//	
//	return Encoder_static;
//}

/*********************************方式3*********************************************/
//Encoder_State Encoder_Check_Three(void)
//{
//	static u8 last_A = 1;
//    u8 last_B = 1;
//	u8 now_B = 1;
//	u32 time_out = 0;  //超时
//	
//	if(!last_A) //上一次为0，表示不完整循环
//	{
//		last_A = ES3_A;
//		return Encoder_static;
//	}
//	
//	if(ES3_A&&ES3_B)
//	{
//		return Encoder_static; //返回旋钮静态
//	}
//	
//	last_B = ES3_B; //记录现在B的状态
//	
//	while((!ES3_A)&&(time_out<time_over))time_out++; //等待A变为高电平
//	last_A = ES3_A; //记录现在的A状态
//	
//	if(last_A == 1) //如果状态为1，代表一个完整的循环
//	{
////		time_out = 0;
////		do
////		{
////			now_B = ES3_B; //记录最新的B状态
////			time_out++;
////		}while((last_B == now_B)&&(time_out<time_over));
////		
////		if(time_out>=time_over)
////		{
////			return Encoder_static;
////		}
//		
//		now_B = ES3_B; //记录最新的B状态
//		if((last_B == 0)&&(now_B == 1)) //对比，B产生上升沿
//		{
//			Encoder_sample[three].encoder_state = Encoder3_right;
//		}
//		else if((last_B == 1)&&(now_B == 0)) //B产生下降沿
//		{
//			Encoder_sample[three].encoder_state = Encoder3_left;
//		}
//		else
//		{
//			Encoder_sample[three].encoder_state = Encoder_static; //错误检测
//		}
//		return Encoder_sample[three].encoder_state;  //返回旋钮状态
//	}
//	else //不完整循环
//	{
//		return Encoder_static;
//	}
//	
//	
//	
//}
/***************新的编码器检测1********************/


//Encoder_State Encoder_Check_Three(void)
//{
//	static u8 last_a = 1;
//	static u8 last_b = 1;
////	static u8 front_flag=0;
////	static u8 back_flag=0;

//	
//	if(ES3_A != last_a)//A脚发生变化
//	{
//		delay_ms(2);   //消抖
//		if(ES3_A != last_a)  //A脚发生变化
//		{
//			if(last_a) //说明是A产生下降沿
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
//			else   //说明A是上升沿
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
//	Encoder_sample[three].encoder_state = Encoder_static; //编码器静止状态
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
//	if(ES1_A != last_a)//A脚发生变化
//	{
//		delay_ms(2);   //消抖
//		if(ES1_A != last_a)  //A脚发生变化
//		{
//			if(last_a == 1) //说明是A产生下降沿
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
//			else   //说明A是上升沿
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
//	Encoder_sample[three].encoder_state = Encoder_static; //编码器静止状态
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