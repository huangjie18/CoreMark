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
//�ĸ���ť�¼�
typedef enum
{
	KEY_NONE = 0,
	KEY_INPUT,  //���밴��
	KEY_ESC,    //�˳�����
	KEY_OUTPUT, //�������
	KEY_SYSTEM, //ϵͳ����
	KEY_EN_1, //������1
	KEY_EN_2, //������2
	KEY_EN_3, //������3
}KEY_ENUM;


//��ť�¼�
typedef enum
{
    Encoder_static = 0,  //��ť��ֹ
//    Encoder_press,   //��ť����
    Encoder1_left,     //��ť��ת
    Encoder1_right,    //��ť��ת
	Encoder2_left,     //��ť��ת
    Encoder2_right,    //��ť��ת
	Encoder3_left,     //��ť��ת
    Encoder3_right,    //��ť��ת
} Encoder_State;


void KEY_GPIO_Init(void); //����Ӳ����ʼ��
u8 KEY_Scan(u8 mode);     //����ɨ�躯��
void Encoder_GPIO_Init(void);  //��������ʼ��
Encoder_State Encoder_Check_One(void);    //��ť1���
Encoder_State Encoder_Check_Two(void);    //��ť2���
Encoder_State Encoder_Check_Three(void);  //��ť3���
#endif
