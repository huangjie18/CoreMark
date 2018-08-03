#ifndef __TOUCH_H
#define __TOUCH_H	
#include "sys.h"	


#define USE_TOUCH_MODE   0    //1使用自带触摸驱动，0自定义触摸
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //触摸IC读坐标积存器
#define  CMD_RDY  0x90
//IO连接
  
#define DCLK    PBout(3)
#define CS      PBout(2)
#define DIN     PBout(5)
#define DOUT    PBin(4)
#define Penirq  PBin(1)  //检测触摸屏响应信号

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

extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //当前触控坐标的AD值,前触控坐标的像素值   
extern u16 vx,vy;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
extern u16 chx,chy;//默认像素点坐标为0时的AD起始值
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //绘图函数
u16 ReadFromCharFrom7843();         //SPI 读数据


u8 TP_Init(void);  //引脚初始化
u16 TP_Read_XOY(u8 xy);							//带滤波的坐标读取(X/Y)
u16 TP_Read_XOY2(u8 xy);
void ReadTouch(void);
void Init_touch_adj(void);
#endif  