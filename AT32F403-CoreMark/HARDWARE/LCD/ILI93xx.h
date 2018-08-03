#ifndef __LCD_H
#define __LCD_H

//驱动为9341
#include "sys.h"

#define FSMC_Enable  1   //是否使用FSMC,1使用FSMC
//硬件相关的子函数
typedef struct 
{
	vu16 LCD_CMD;
}LCD_Typedef;

typedef struct 
{
	vu16 LCD_DATA;
}LCD_Typedef_data;
#define Bank1_LCD_D    ((u32)0x60020000)    //Disp Data ADDR
#define Bank1_LCD_C    ((u32)0x60000000)	   //Disp Reg ADDR
#define LCD_REG        ((LCD_Typedef*)Bank1_LCD_C)
#define LCD_RAM        ((LCD_Typedef_data*)Bank1_LCD_D)

#define LCD_RST  PDout(12)
#define LCD_WR   PDout(5)
#define LCD_RD   PDout(4)
#define LCD_CS   PDout(7)
#define LCD_RS   PDout(11)  
#define LCD_BL   PDout(13)  //LCD背光
#define DB0      PDout(14)
#define DB1      PDout(15)
#define DB2      PDout(0)
#define DB3      PDout(1)
#define DB4      PEout(7)
#define DB5      PEout(8)
#define DB6      PEout(9)
#define DB7      PEout(10)
#define DB8      PEout(11)
#define DB9      PEout(12)
#define DB10     PEout(13)
#define DB11     PEout(14)
#define DB12     PEout(15)
#define DB13     PDout(10)
#define DB14     PDout(9)
#define DB15     PDout(8)

#define DB0_IN     PDin(14)
#define DB1_IN     PDin(15)
#define DB2_IN     PDin(0)
#define DB3_IN     PDin(1)
#define DB4_IN     PEin(7)
#define DB5_IN     PEin(8)
#define DB6_IN     PEin(9)
#define DB7_IN     PEin(10)
#define DB8_IN     PEin(11)
#define DB9_IN     PEin(12)
#define DB10_IN    PEin(13)
#define DB11_IN    PEin(14)
#define DB12_IN    PEin(15)
#define DB13_IN    PDin(10)
#define DB14_IN    PDin(9)
#define DB15_IN    PDin(8)

#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

void Lcd_Initialize(void);
void Lcd_Clear(u16 Color);
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend);
void DrawPixel(u16 x, u16 y, int Color);
u16 GetPoint(u16 x, u16 y);
void Lcd_SetCursor(u16 x,u16 y);
void WriteComm(u16 CMD);
void WriteData(u16 tem_data);
void Lcd_ColorBox(u16 xStart,u16 yStart,u16 xLong,u16 yLong,u16 Color);
u16 LCD_RD_DATA(void);

u16 LCD_Color_trans(u16 Color); //掉转颜色位
#endif
