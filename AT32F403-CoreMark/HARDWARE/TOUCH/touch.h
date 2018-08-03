#ifndef __TOUCH_H
#define __TOUCH_H	
#include "sys.h"	


#define USE_TOUCH_MODE   0    //1ʹ���Դ�����������0�Զ��崥��
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //����IC�����������
#define  CMD_RDY  0x90
//IO����
  
#define DCLK    PBout(3)
#define CS      PBout(2)
#define DIN     PBout(5)
#define DOUT    PBin(4)
#define Penirq  PBin(1)  //��ⴥ������Ӧ�ź�

#define TP_DCLK  DCLK
#define TP_CS   CS
#define TP_DIN  DIN
#define TP_DOUT DOUT
#define TP_IRQ  Penirq

#define TCLK    DCLK
#define TDIN    DIN
#define TCS     CS
#define PEN     Penirq


struct tp_pix_
{
	u16 x;
	u16 y;
};
struct tp_pixu32_
{
	u32 x;
	u32 y;
};

extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //��ǰ���������ADֵ,ǰ�������������ֵ   
extern u16 vx,vy;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
extern u16 chx,chy;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //��ͼ����
u16 ReadFromCharFrom7843();         //SPI ������


u8 TP_Init(void);  //���ų�ʼ��
u16 TP_Read_XOY(u8 xy);							//���˲��������ȡ(X/Y)
u16 TP_Read_XOY2(u8 xy);
void ReadTouch(void);
void Init_touch_adj(void);
#endif  