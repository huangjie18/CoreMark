#ifndef __INTERFACE_H
#define __INTERFACE_H
#include "GUI.h"
#include "DIALOG.h"
#include "example.h"
#include "sys.h"
#include "24c16.h"
#include "iic.h"
//添加变量的声明转换
#ifdef Gen_GLOBALS //在.c文件中定义该类型,采用这方法不能赋初值
#define EXTERN1
#else 
#define EXTERN1  extern
#endif

//定义按钮的信息ID
#define MSG_KEY_ESC      (GUI_ID_USER + 0xF0)
#define MSG_KEY_SYSTEM   (GUI_ID_USER + 0xF1)
#define MSG_KEY_INPUT     (GUI_ID_USER + 0xF2)
#define MSG_KEY_OUTPUT   (GUI_ID_USER + 0xF3)
#define MSG_KEY_VOL_INPUT  (GUI_ID_USER + 0xF4)
#define MSG_KEY_VOL_OUTPUT (GUI_ID_USER + 0xF5)
#define MSG_KEY_CONTROL    (GUI_ID_USER + 0xF6)

//定义旋钮的信息ID
#define MSG_KNOB_INPUT_LEFT    (GUI_ID_USER + 0xF7)
#define MSG_KNOB_INPUT_RIGHT   (GUI_ID_USER + 0xF8)
#define MSG_KNOB_OUT_LEFT      (GUI_ID_USER + 0xF9)
#define MSG_KNOB_OUT_RIGHT     (GUI_ID_USER + 0xFA)
#define MSG_KNOB_CONTROL_LEFT  (GUI_ID_USER + 0xFB)
#define MSG_KNOB_CONTROL_RIGHT (GUI_ID_USER + 0xFC)
#define MSG_KNOB_NULL		   (GUI_ID_USER + 0xFD)  //没有旋钮动作


//定义一个变量来存放当前的页面的句柄
extern WM_HWIN hWin_now;


//皮肤设置函数
void Button_flex(void); //按钮皮肤设置
void Button_flex_2(void); //按钮皮肤设置
void Framewin_flex(void); //框架皮肤设置
int _DrawSkin_SLIDER1(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);//滑块皮肤设置
void Listbox_flex(void);
//界面函数
WM_HWIN CreateMainface(void); //主界面窗口

//IIC地址设置
#define Addr_num  100
extern u16 IIC_Addr[Addr_num];

/*********************************************第二次界面**********************************/
/******************************
***
***变量
***
*******************************/
extern BUTTON_SKINFLEX_PROPS Props_Default; 
extern char INPUT_CHANNEL;  //用来指示选中哪个输入通道

/******************************************Input_First  数据*********************************************/
//Input_First数据结构
typedef struct
{
	u8  IN_DATA_1;
	u8  IN_DATA_2;
	u8  IN_DATA_3;
	u8  IN_DATA_4;
	u8  IN_DATA_5;
	u8  IN_DATA_6;
	u8  IN_DATA_7;
	u8  IN_DATA_8;
}Input_First_data;


/******************************************Input_First  End*********************************************/

/******************************************Input_Second  数据****************************************/
//要保存的数据
typedef struct 
{
	//NOISEGATE的数据
	s16  RMSTC_DATA;       //存放RMSTC的数值,有符号
	s16  HOLD_DATA;		   //存放HOLD的数值
	s16  DECAY_DATA;	   //存放DECAY的数值
	
	//MUTE_AND_INVERT
	u8 IN_MUTE_STA;      //指示IN_MUTE当前状态
	u8 IN_INVERT_STA;    //指示IN_INVERT当前状态 
	
	//COMPRESSOR的数据
	char ON_OFF;           //存放开或关的数据
	u16  THRSH_DATA;       //存放THRSH的数据
	u16  RATIO_DATA;       //存放RATIO的数据
	u16  ATK_TIME_DATA;    //存放ATK_TIME的数据
	u16  RELEASE_DATA;     //存放RELEASE的数据
	u16  COM_HOLD_DATA;    //存放HOLD的数据
}Input_Data;

//Input_Second数据
typedef  struct 
{
	Input_Data data;      //要保存的数据

	//指示不同通道的数据
	char face_switch;      //指示第几个通道页面
	char Item;             //指示选中第几个子项目
	char *String;          //用来存放字符串
	
	//用来计算长短按的
	u16  Time_count;       //判断定时器长短按
	u16  Key_count;        //判断旋转按钮快慢
	
	//定时器的句柄
	WM_HTIMER  hItime;
	
	//用来判断按钮是否释放
	u16 Released;         //0代表已经释放，1代表没释放
	
}Input_Second_data;

//子项目
enum
{
	RMSTC_Item,
	HOLD_Item,
	DECAY_Item,
	IN_MUTE_Item,
	IN_INVERT_Item,
	ON_OFF_Item,
	THRSH_Item,
	RATIO_Item,
	ATK_TIME_Item,
	RELEASE_Item,
	COM_HOLD_Item,
};

//定时器
enum
{
	RMSTC_Time_left,
	RMSTC_Time_right,
	HOLD_Time_left,
	HOLD_Time_right,
	DECAY_Time_left,
	DECAY_Time_right,
	THRSH_Time_left,
	THRSH_Time_right,
	RATIO_Time_left,
	RATIO_Time_right,
	ATK_Time_left,
	ATK_Time_right,
	RELEASE_Time_left,
	RELEASE_Time_right,
	COM_HOLD_Time_left,
	COM_HOLD_Time_right,
};

/*******************************************Input_Second  End*******************************************/

/*******************************************Input_Third 数据**********************************/
typedef struct 
{
	u8 Aux1_SLIDER_DATA;
	u8 Aux2_SLIDER_DATA;
	u8 Aux3_SLIDER_DATA;
	u8 Aux4_SLIDER_DATA;
	u8 Aux5_SLIDER_DATA;
	u8 Aux6_SLIDER_DATA;
	u8 Aux7_SLIDER_DATA;
	u8 Aux8_SLIDER_DATA;
	u8 Aux1_CHECKBOX_STA;
	u8 Aux2_CHECKBOX_STA;
	u8 Aux3_CHECKBOX_STA;
	u8 Aux4_CHECKBOX_STA;
	u8 Aux5_CHECKBOX_STA;
	u8 Aux6_CHECKBOX_STA;
	u8 Aux7_CHECKBOX_STA;
	u8 Aux8_CHECKBOX_STA;
}Input_Data3;


typedef struct 
{
	Input_Data3  data;
	//指示不同通道的数据
	char face_switch;      //指示第几个通道页面
	char Item;             //指示选中第几个子项目
	char *String;          //用来存放字符串
	
	//用来计算长短按的
	u16  Time_count;       //判断定时器长短按
	u16  Key_count;        //判断旋转按钮快慢
	
	//定时器的句柄
	WM_HTIMER  hItime;
	
	//用来判断按钮是否释放
	u16 Released;         //0代表已经释放，1代表没释放
	
	//专门用来对应复选框
	char checkbox_sta;
	
	
}Input_Third_data;

/***********************************************Input_Four 数据**************************************************/
typedef struct 
{
	char 	ON_OFF;
	s16		BAND_DATA;
	s16		FREQ_DATA;
	s16		TYPE_DATA;
	s16		GAIN_DATA;
	s16		Q_DATA;
}Input_Data4;

typedef struct
{
	Input_Data4 data;
	
	//指示不同通道的数据
	char face_switch;      //指示第几个通道页面
	char Item;             //指示选中第几个子项目
	char *String;          //用来存放字符串
	
	//用来计算长短按的
	u16  Time_count;       //判断定时器长短按
	u16  Key_count;        //判断旋转按钮快慢
	
	//定时器的句柄
	WM_HTIMER  hItime;
	
}Input_Four_data;

//子项目标号
enum
{
	ON_OFF_Four,
	BAND_Four,
	FREQ_Four,
	TYPE_Four,
	GAIN_Four,
	Q_Four,
};

/***********************************************OUT_First 数据************************************************/
//Out_First数据结构
extern char OUTPUT_CHANNEL;

typedef struct
{
	u8  OUT_DATA_1;
	u8  OUT_DATA_2;
	u8  OUT_DATA_3;
	u8  OUT_DATA_4;
	u8  OUT_DATA_5;
	u8  OUT_DATA_6;
	u8  OUT_DATA_7;
	u8  OUT_DATA_8;
}Output_First_data;

/***********************************************OUT_Second 数据************************************************/
typedef struct 
{
	s16 RMSTC_DATA;   //RMSTC数值
	s16 DECAY_DATA;   //DECAT数值
	s16 THRSH_DATA;   //THRESHOLD数值
	s16 DELAY_DATA;   //DELAY数值
	
	u8  OUT_MUTE_STA; //OUT_MUTE状态
	u8  OUT_INVERT_STA; //OUT_INVERT状态
	
}Output_Data1;


typedef struct
{
	Output_Data1  data;
	
	//指示不同通道的数据
	char face_switch;      //指示第几个通道页面
	char Item;             //指示选中第几个子项目
	char *String;          //用来存放字符串
	
	//用来计算长短按的
	u16  Time_count;       //判断定时器长短按
	u16  Key_count;        //判断旋转按钮快慢
	
	//定时器的句柄
	WM_HTIMER  hItime;
	
	//专门用来对应复选框
	char checkbox_sta;
	
}Output_Second_Data;

enum
{
	RMSTC_Item_Out,
	DECAY_Item_Out,
	THRES_Item_Out,
	MUTE_Item_Out,
	INVERT_Item_Out,
	DELAY_Item_Out,
};

/*
*******************************************************************************************
* *********************************函 数 名***********************************************
* 
*
* 
*******************************************************************************************
*/

/*************************INPUT********************************/
WM_HWIN Input_First(void);
WM_HWIN Input_Second(void);
WM_HWIN Input_Third(void);
WM_HWIN Input_Four(void);

void Max_Min(void *p,u16 Max,u16 Min);  //最大和最小值
void Value_Change_add(void *p,u16 *time); //值增加
void Value_Change_dec(void *p,u16 *time); //值减少

/**************************OUTPUT********************************/
WM_HWIN Output_First(void);
WM_HWIN Output_Second(void);
WM_HWIN Output_Third(void);
WM_HWIN Output_Four(void);

#endif
