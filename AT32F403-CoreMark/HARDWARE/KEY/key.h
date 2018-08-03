#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define col1  PCout(9)
#define col2  PCout(10)
#define col3  PCout(11)
#define row1  PCin(6)
#define row2  PCin(7)
#define row3  PCin(8)
#define ES1_A PEin(6)
#define ES1_B PEin(5)
#define ES2_A PEin(4)
#define ES2_B PEin(3)
#define ES3_A PEin(2)
#define ES3_B PEin(1)
//#define ES3_B GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)

enum
{
	zero = 0,
	one,
	two,
	three,
	four,
	five,
};
//四个按钮事件
typedef enum
{
	KEY_NONE = 0,
	KEY_INPUT,  //输入按键
	KEY_ESC,    //退出按键
	KEY_OUTPUT, //输出按键
	KEY_SYSTEM, //系统按键
	KEY_EN_1, //编码器1
	KEY_EN_2, //编码器2
	KEY_EN_3, //编码器3
}KEY_ENUM;


//旋钮事件
typedef enum
{
    Encoder_static = 0,  //旋钮静止
//    Encoder_press,   //旋钮按下
    Encoder1_left,     //旋钮右转
    Encoder1_right,    //旋钮左转
	Encoder2_left,     //旋钮右转
    Encoder2_right,    //旋钮左转
	Encoder3_left,     //旋钮右转
    Encoder3_right,    //旋钮左转
} Encoder_State;


void KEY_GPIO_Init(void); //按键硬件初始化
u8 KEY_Scan(u8 mode);     //按键扫描函数
void Encoder_GPIO_Init(void);  //编码器初始化
Encoder_State Encoder_Check_One(void);    //旋钮1检测
Encoder_State Encoder_Check_Two(void);    //旋钮2检测
Encoder_State Encoder_Check_Three(void);  //旋钮3检测
#endif
