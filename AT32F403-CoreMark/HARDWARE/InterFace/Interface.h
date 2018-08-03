#ifndef __INTERFACE_H
#define __INTERFACE_H
#include "GUI.h"
#include "DIALOG.h"
#include "example.h"
#include "sys.h"
#include "24c16.h"
#include "iic.h"
//��ӱ���������ת��
#ifdef Gen_GLOBALS //��.c�ļ��ж��������,�����ⷽ�����ܸ���ֵ
#define EXTERN1
#else 
#define EXTERN1  extern
#endif

//���尴ť����ϢID
#define MSG_KEY_ESC      (GUI_ID_USER + 0xF0)
#define MSG_KEY_SYSTEM   (GUI_ID_USER + 0xF1)
#define MSG_KEY_INPUT     (GUI_ID_USER + 0xF2)
#define MSG_KEY_OUTPUT   (GUI_ID_USER + 0xF3)
#define MSG_KEY_VOL_INPUT  (GUI_ID_USER + 0xF4)
#define MSG_KEY_VOL_OUTPUT (GUI_ID_USER + 0xF5)
#define MSG_KEY_CONTROL    (GUI_ID_USER + 0xF6)

//������ť����ϢID
#define MSG_KNOB_INPUT_LEFT    (GUI_ID_USER + 0xF7)
#define MSG_KNOB_INPUT_RIGHT   (GUI_ID_USER + 0xF8)
#define MSG_KNOB_OUT_LEFT      (GUI_ID_USER + 0xF9)
#define MSG_KNOB_OUT_RIGHT     (GUI_ID_USER + 0xFA)
#define MSG_KNOB_CONTROL_LEFT  (GUI_ID_USER + 0xFB)
#define MSG_KNOB_CONTROL_RIGHT (GUI_ID_USER + 0xFC)
#define MSG_KNOB_NULL		   (GUI_ID_USER + 0xFD)  //û����ť����


//����һ����������ŵ�ǰ��ҳ��ľ��
extern WM_HWIN hWin_now;


//Ƥ�����ú���
void Button_flex(void); //��ťƤ������
void Button_flex_2(void); //��ťƤ������
void Framewin_flex(void); //���Ƥ������
int _DrawSkin_SLIDER1(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);//����Ƥ������
void Listbox_flex(void);
//���溯��
WM_HWIN CreateMainface(void); //�����洰��

//IIC��ַ����
#define Addr_num  100
extern u16 IIC_Addr[Addr_num];

/*********************************************�ڶ��ν���**********************************/
/******************************
***
***����
***
*******************************/
extern BUTTON_SKINFLEX_PROPS Props_Default; 
extern char INPUT_CHANNEL;  //����ָʾѡ���ĸ�����ͨ��

/******************************************Input_First  ����*********************************************/
//Input_First���ݽṹ
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

/******************************************Input_Second  ����****************************************/
//Ҫ���������
typedef struct 
{
	//NOISEGATE������
	s16  RMSTC_DATA;       //���RMSTC����ֵ,�з���
	s16  HOLD_DATA;		   //���HOLD����ֵ
	s16  DECAY_DATA;	   //���DECAY����ֵ
	
	//MUTE_AND_INVERT
	u8 IN_MUTE_STA;      //ָʾIN_MUTE��ǰ״̬
	u8 IN_INVERT_STA;    //ָʾIN_INVERT��ǰ״̬ 
	
	//COMPRESSOR������
	char ON_OFF;           //��ſ���ص�����
	u16  THRSH_DATA;       //���THRSH������
	u16  RATIO_DATA;       //���RATIO������
	u16  ATK_TIME_DATA;    //���ATK_TIME������
	u16  RELEASE_DATA;     //���RELEASE������
	u16  COM_HOLD_DATA;    //���HOLD������
}Input_Data;

//Input_Second����
typedef  struct 
{
	Input_Data data;      //Ҫ���������

	//ָʾ��ͬͨ��������
	char face_switch;      //ָʾ�ڼ���ͨ��ҳ��
	char Item;             //ָʾѡ�еڼ�������Ŀ
	char *String;          //��������ַ���
	
	//�������㳤�̰���
	u16  Time_count;       //�ж϶�ʱ�����̰�
	u16  Key_count;        //�ж���ת��ť����
	
	//��ʱ���ľ��
	WM_HTIMER  hItime;
	
	//�����жϰ�ť�Ƿ��ͷ�
	u16 Released;         //0�����Ѿ��ͷţ�1����û�ͷ�
	
}Input_Second_data;

//����Ŀ
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

//��ʱ��
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

/*******************************************Input_Third ����**********************************/
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
	//ָʾ��ͬͨ��������
	char face_switch;      //ָʾ�ڼ���ͨ��ҳ��
	char Item;             //ָʾѡ�еڼ�������Ŀ
	char *String;          //��������ַ���
	
	//�������㳤�̰���
	u16  Time_count;       //�ж϶�ʱ�����̰�
	u16  Key_count;        //�ж���ת��ť����
	
	//��ʱ���ľ��
	WM_HTIMER  hItime;
	
	//�����жϰ�ť�Ƿ��ͷ�
	u16 Released;         //0�����Ѿ��ͷţ�1����û�ͷ�
	
	//ר��������Ӧ��ѡ��
	char checkbox_sta;
	
	
}Input_Third_data;

/***********************************************Input_Four ����**************************************************/
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
	
	//ָʾ��ͬͨ��������
	char face_switch;      //ָʾ�ڼ���ͨ��ҳ��
	char Item;             //ָʾѡ�еڼ�������Ŀ
	char *String;          //��������ַ���
	
	//�������㳤�̰���
	u16  Time_count;       //�ж϶�ʱ�����̰�
	u16  Key_count;        //�ж���ת��ť����
	
	//��ʱ���ľ��
	WM_HTIMER  hItime;
	
}Input_Four_data;

//����Ŀ���
enum
{
	ON_OFF_Four,
	BAND_Four,
	FREQ_Four,
	TYPE_Four,
	GAIN_Four,
	Q_Four,
};

/***********************************************OUT_First ����************************************************/
//Out_First���ݽṹ
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

/***********************************************OUT_Second ����************************************************/
typedef struct 
{
	s16 RMSTC_DATA;   //RMSTC��ֵ
	s16 DECAY_DATA;   //DECAT��ֵ
	s16 THRSH_DATA;   //THRESHOLD��ֵ
	s16 DELAY_DATA;   //DELAY��ֵ
	
	u8  OUT_MUTE_STA; //OUT_MUTE״̬
	u8  OUT_INVERT_STA; //OUT_INVERT״̬
	
}Output_Data1;


typedef struct
{
	Output_Data1  data;
	
	//ָʾ��ͬͨ��������
	char face_switch;      //ָʾ�ڼ���ͨ��ҳ��
	char Item;             //ָʾѡ�еڼ�������Ŀ
	char *String;          //��������ַ���
	
	//�������㳤�̰���
	u16  Time_count;       //�ж϶�ʱ�����̰�
	u16  Key_count;        //�ж���ת��ť����
	
	//��ʱ���ľ��
	WM_HTIMER  hItime;
	
	//ר��������Ӧ��ѡ��
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
* *********************************�� �� ��***********************************************
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

void Max_Min(void *p,u16 Max,u16 Min);  //������Сֵ
void Value_Change_add(void *p,u16 *time); //ֵ����
void Value_Change_dec(void *p,u16 *time); //ֵ����

/**************************OUTPUT********************************/
WM_HWIN Output_First(void);
WM_HWIN Output_Second(void);
WM_HWIN Output_Third(void);
WM_HWIN Output_Four(void);

#endif
