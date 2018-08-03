#include "touch.h"
#include "sys.h"
#include "interface.h"
#include "delay.h"
#include "GUI.h"
#include "stdlib.h"
#include "math.h"

//variable
struct tp_pix_  tp_pixad, tp_pixlcd; //��ǰ���������ADֵ,ǰ�������������ֵ
/***********************
T_BUSY  PB0
T_IQR   PB1
T_CS    PB2
T_SCK   PB3
T_MISO  PB4
T_MOSI  PB5
***********************/
#define GUI_TOUCH_AD_TOP		3820  	//���´������Ķ�����д�� X ��ģ������ֵ��
#define GUI_TOUCH_AD_BOTTOM		150 	//���´������ĵײ���д�� X ��ģ������ֵ��
#define GUI_TOUCH_AD_LEFT 		3760    //���´���������࣬д�� Y ��ģ������ֵ��
#define GUI_TOUCH_AD_RIGHT		380	    //���´��������Ҳ࣬д�� Y ��ģ������ֵ��

//TP_Init,���ų�ʼ��
u8 TP_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //ʹ��PB�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,
                           ENABLE);     //ʹ�ø��ù��ܣ���Ϊ�õ�PB3��PB4
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,
                        ENABLE); //JTAG-DP ʧ�� + SW-DP ʹ��

    //PB0--T_BUSY  PB2--T_CS   PB5--T_MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 |
                                  GPIO_Pin_5;              // PB�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PB3--T_SCK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;   //PB3
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PB4--T_MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                // PB4�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;   //PB3
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PB1--T_IQR
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  //���������ź�
    GPIO_Init(GPIOB, &GPIO_InitStructure);


}

//�ж��Ƿ���
u8 tpstate(void)
{
    return  Penirq;
}
//��һ��������
//����У׼�õ�
void Drow_Touch_Point(u16 x, u16 y)
{
    GUI_SetColor(GUI_WHITE);  //��ɫ
    GUI_DrawHLine(y, x - 12, x + 13); //����
    GUI_DrawVLine(x, y - 12, y + 13); //����

    GUI_DrawCircle(x, y, 6); //������Ȧ
}
////////////////////////////////////////////////////////////

static void WR_CMD (unsigned char cmd)
{
    unsigned char buf;
    unsigned char i;
//     TP_CS(1);
    TP_DIN = 0;
    TP_DCLK = 0;
//     TP_CS(0);
    for(i = 0; i < 8; i++)
    {
        buf = (cmd >> (7 - i)) & 0x1;
        TP_DIN = buf;
        //Delayus(5);
        TP_DCLK = 1;
        //Delayus(5);
        TP_DCLK = 0;
    }
}
//====================================================================================
static unsigned short RD_AD(void)
{
    unsigned short buf = 0, temp;
    unsigned char i;
    TP_DIN = 0;
    TP_DCLK = 1;
    for(i = 0; i < 12; i++)
    {
        TP_DCLK = 0;
        temp = (TP_DOUT) ? 1 : 0;
        buf |= (temp << (11 - i));
        //Delayus(5);
        TP_DCLK = 1;
    }
//     TP_CS(1);
    buf &= 0x0fff;
    return(buf);
}
//SPIд����
//������ICд��1byte����
//num:Ҫд�������
void TP_Write_Byte(u8 num)
{
    u8 count = 0;
    for(count = 0; count < 8; count++)
    {
        if(num & 0x80)TDIN = 1;
        else TDIN = 0;
        num <<= 1;
        TCLK = 0;
        delay_us(1);
        TCLK = 1;   //��������Ч
    }
}

u16 TP_Read_XOY2(u8 xy)
{
    int i[5], temp;
    u8 cou = 0, k = 0;
    WR_CMD(xy);
    RD_AD();
    while(cou < 5)  //ѭ������5��
    {
        WR_CMD(xy);
        cou++;
        i[cou] = RD_AD();
    }
    //��������������
    for(k = 0; k < 4; k++)
    {
        for(cou = 1; cou < 5 - k; cou++)
        {
            if(i[cou] > i[cou + 1])
            {
                temp = i[cou + 1];
                i[cou + 1] = i[cou];
                i[cou] = temp;
            }
        }
    }
    return (i[1] + i[2] + i[3]) / 3;
}








//SPI������
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������
u16 TP_Read_AD(u8 CMD)
{
    u8 count = 0;
    u16 Num = 0;
    TCLK = 0;   //������ʱ��
    TDIN = 0;   //����������
    TCS = 0;    //ѡ�д�����IC
    TP_Write_Byte(CMD);//����������
    delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
    TCLK = 0;
    delay_us(1);
    TCLK = 1;   //��1��ʱ�ӣ����BUSY
    delay_us(1);
    TCLK = 0;
    for(count = 0; count < 16; count++) //����16λ����,ֻ�и�12λ��Ч
    {
        Num <<= 1;
        TCLK = 0; //�½�����Ч
        delay_us(1);
        TCLK = 1;
        if(DOUT)Num++;
    }
    Num >>= 4;  //ֻ�и�12λ��Ч.
    TCS = 1;    //�ͷ�Ƭѡ
    return(Num);
}
//��ȡһ������ֵ(x����y)
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ
//xy:ָ�CMD_RDX/CMD_RDY��
//����ֵ:����������
#define READ_TIMES 10   //��ȡ����
#define LOST_VAL 2      //����ֵ
u16 TP_Read_XOY(u8 xy)
{
    u16 i, j;
    u16 buf[READ_TIMES];
    u16 sum = 0;
    u16 temp;
    for(i = 0; i < READ_TIMES; i++)buf[i] = TP_Read_AD(xy);
    for(i = 0; i < READ_TIMES - 1; i++) //����
    {
        for(j = i + 1; j < READ_TIMES; j++)
        {
            if(buf[i] > buf[j]) //��������
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }
    sum = 0;
    for(i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++)sum += buf[i];
    temp = sum / (READ_TIMES - 2 * LOST_VAL);
    return temp;
}
//��ȡx,y����
//��Сֵ��������100.
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
u8 TP_Read_XY(u16 *x, u16 *y)
{
    u16 xtemp, ytemp;
    xtemp = TP_Read_XOY(CMD_RDX);
    ytemp = TP_Read_XOY(CMD_RDY);
    //if(xtemp<100||ytemp<100)return 0;//����ʧ��
    *x = xtemp;
    *y = ytemp;
    return 1;//�����ɹ�
}
//����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
//ERR_RANGE,��������,����Ϊ������ȷ,�����������.
//�ú����ܴ�����׼ȷ��
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
#define ERR_RANGE 50 //��Χ 
u8 TP_Read_XY2(u16 *x, u16 *y)
{
    u16 x1, y1;
    u16 x2, y2;
    u8 flag;
    flag = TP_Read_XY(&x1, &y1);
    if(flag == 0)return(0);
    flag = TP_Read_XY(&x2, &y2);
    if(flag == 0)return(0);
    if(((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 &&
            x2 < x1 + ERR_RANGE)) //ǰ�����β�����+-50��
       && ((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE)))
    {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    }
    else return 0;
}

//������У׼����
//�õ��ĸ�У׼����
#define tp_pianyi 50   //У׼����ƫ���� 
#define tp_xiaozhun 1000   //У׼����
void Touch_Adjust(void)
{
    u16 x1, y1;
    u16 pos_temp[4][2];//���껺��ֵ
    u8  cnt = 0;
    u16 d1, d2;
    u32 tem1, tem2;
    double fac;
    u16 outtime = 0;
    cnt = 0;
    Drow_Touch_Point(tp_pianyi, tp_pianyi); //����1
    while(1)
    {
        if(Penirq == 0) //����������
        {
            while(!TP_Read_XY2(&tp_pixad.x, &tp_pixad.y));
            delay_ms(10);
            while(!TP_Read_XY2(&x1, &y1));
            if(tp_pixad.x == x1 && tp_pixad.y == y1)
            {
                GUI_DispHex(tp_pixad.x, 4);
            }

        }
    }
}


////////////////////////////////////////////
#define CALIB_POINT_COUT  4  //���ٵ�У׼,�������Ϊ5�㣬�ĵ����ܿ���9��У׼
/*
������У׼�������Ļ�����Ľǵ�ƫ������
��1���� �� x1 = CALIB_OFFSET, y1 = CALIB_OFFSET
��2���� �� x2 = LCD_GetWidth() - CALIB_OFFSET, y2 = LCD_GetHeight() - CALIB_OFFSET
*/
#define CALIB_OFFSET	20
#define TP_X1	CALIB_OFFSET
#define TP_Y1	CALIB_OFFSET

#define TP_X2	(LCD_GetXSize() - CALIB_OFFSET)
#define TP_Y2	(LCD_GetYSize() - CALIB_OFFSET)

#define TP_X3	CALIB_OFFSET
#define TP_Y3	(LCD_GetYSize() - CALIB_OFFSET)

#define TP_X4	(LCD_GetXSize() - CALIB_OFFSET)
#define TP_Y4	CALIB_OFFSET

#define TP_X5   (LCD_GetXSize()/2)
#define TP_Y5   (LCD_GetYSize()/2)
//����ָ��
static int lcd_x[5] = {20, 380, 20, 380, 200};
static int lcd_y[5] = {20, 220, 220, 20, 120};
static int Adc_x[5] = {3613, 320, 3674, 316, 1980};
static int Adc_y[5] = {3546, 600, 650, 3600, 2100};
/*********************************************************************
*
*       _WaitForPressedState
*
* Function description
*   Waits until the touch is in the given pressed state for at least 250 ms
*/
static void _WaitForPressedState(int Pressed) {
  GUI_PID_STATE State;

  do {
    GUI_TOUCH_GetState(&State);
    GUI_Delay(1);
    if (State.Pressed == Pressed) {
      int TimeStart = GUI_GetTime();
      do {
        GUI_TOUCH_GetState(&State);
        GUI_Delay(1);
        if (State.Pressed != Pressed) {
          break;
        } else if ((GUI_GetTime() - 50) > TimeStart) {
          return;
        }
      } while (1);
    }
  } while (1);
}
/*********************************************************************
*
*       _DispStringCentered
*
* Function description
*   Shows the given text horizontally and vertically centered
*/
static void _DispStringCentered(const char * pString) {
  GUI_RECT Rect;

  Rect.x0 = Rect.y0 = 0;
  Rect.x1 = LCD_GetXSize() - 1;
  Rect.y1 = LCD_GetYSize() - 1;
  GUI_DispStringInRect(pString, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
}
/********************************************************************
*
*       _Explain
*
* Funtion description
*   Shows a text to give a short explanation of the sample program
*/
static u8 _Explain(void) {
  u16 count=0;
  GUI_SetBkColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font13B_ASCII);
  _DispStringCentered("The touch screen is calibrated at four points,\n"
                      "and the uncalibrated touch screen will\n"
                      "return to the main interface automatically\n"
                      "within ten seconds.\n"
					  "Please press the touch screen to continue...");
  GUI_DispStringHCenterAt("TOUCH_Calibrate", LCD_GetXSize() / 2, 5);
  while(Penirq)
  {
	  if(count >= 500)  //x���Զ��˳�
	  {
		  return 0;  //������У׼ֱ���˳�
	  }
	  count++;
	  GUI_Delay(10);
  }
//  _WaitForPressedState(1);  //�ȴ���������
  _WaitForPressedState(0);  //�ȴ������ͷ�
  return 1;  //����У׼
}

//��ʾУ׼��
static void TOUCH_DispPoint(uint8_t _ucIndex)
{
	if(_ucIndex == 0)
	{
		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();  //����
		
		/* ����Ļ���ػ���2�����ο�(���ڼ������Ե�����Ƿ�����) */
		GUI_DrawRect(0,0,399,239);
		GUI_DrawRect(2,2,397,237);
		
		_DispStringCentered("Runtime calibration,\n"
                      "please touch the screen\n"
                      "at the center of the ring."); /* Ask user to press the touch */
		//��Բ
		GUI_SetColor(GUI_BLACK);
		GUI_FillCircle(TP_X1, TP_Y1, 10);
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X1, TP_Y1, 5);
		GUI_SetColor(GUI_BLACK);
		
	}
	else if(_ucIndex == 1)
	{
		//�����һ��Բ
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X1, TP_Y1, 10);
		//��Բ
		GUI_SetColor(GUI_BLACK);
		GUI_FillCircle(TP_X2, TP_Y2, 10);
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X2, TP_Y2, 5);
		GUI_SetColor(GUI_BLACK);
		
	}
	else if(_ucIndex == 2)
	{
		//�����һ��Բ
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X2, TP_Y2, 10);
		//��Բ
		GUI_SetColor(GUI_BLACK);
		GUI_FillCircle(TP_X3, TP_Y3, 10);
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X3, TP_Y3, 5);
		GUI_SetColor(GUI_BLACK);
		
	}
	else if(_ucIndex == 3)
	{
		//�����һ��Բ
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X3, TP_Y3, 10);
		//��Բ
		GUI_SetColor(GUI_BLACK);
		GUI_FillCircle(TP_X4, TP_Y4, 10);
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X4, TP_Y4, 5);
		GUI_SetColor(GUI_BLACK);
		
	}
	else if(_ucIndex == 4)
	{
		//�����һ��Բ
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(TP_X4, TP_Y4, 10);
		//��Բ
		GUI_SetColor(GUI_BLACK);
		GUI_FillCircle(200, 120, 10);
		GUI_SetColor(GUI_WHITE);
		GUI_FillCircle(200, 120, 5);
		GUI_SetColor(GUI_BLACK);
		
	}
	_WaitForPressedState(1);
	Adc_x[_ucIndex] = TP_Read_XOY(0XD0); //��ȡ
	Adc_y[_ucIndex] = TP_Read_XOY(0X90);
	_WaitForPressedState(0);
	
}


//��㴥��У׼
void Touch_adjust(void)
{
	u8 flat = 1;
	uint8_t i;
	u32 tem1,tem2;
	u16 d1,d2;
	double fac;
	flat = _Explain();
	//Բ�������
	lcd_x[0] = TP_X1;
	lcd_y[0] = TP_Y1;
	lcd_x[1] = TP_X2;
	lcd_y[1] = TP_Y2;
	lcd_x[2] = TP_X3;
	lcd_y[2] = TP_Y3;
	lcd_x[3] = TP_X4;
	lcd_y[3] = TP_Y4;
	lcd_x[4] = TP_X5;
	lcd_y[4] = TP_Y5;
	////////////////////////////////////////////
	while(flat)
	{
		for(i = 0;i < CALIB_POINT_COUT; i++)
		{
			TOUCH_DispPoint(i);		/* ��ʾУ׼�� */
		}
		//��ֹ���ⴥ��
		//�Խ��߾�����
		tem1 = abs(Adc_x[0]-Adc_x[1]);  //x1-x2
		tem2 = abs(Adc_y[0]-Adc_y[1]);  //y1-y2
		tem1 *= tem1;
		tem2 *= tem2;
		d1=sqrt(tem1+tem2);//�õ�1,2�ľ���
		
		tem1 = abs(Adc_x[2]-Adc_x[3]);  //x3-x4
		tem2 = abs(Adc_y[2]-Adc_y[3]);  //y3-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d2=sqrt(tem1+tem2);//�õ�3,4�ľ���
		
		fac=(float)d1/d2;
		if(fac<0.95||fac>1.05)//���ϸ�
		{
			i=0; //���¿�ʼ
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			_DispStringCentered("Calibration date error,\n"
								"Please calibrated again."); /* Ask user to press the touch */
			_WaitForPressedState(1);
			_WaitForPressedState(0);
			continue; //����У׼
		}
		
		//�Ա߼��
		//��ֱ��
		tem1 = abs(Adc_x[0]-Adc_x[2]);  //x1-x3
		tem2 = abs(Adc_y[0]-Adc_y[2]);  //y1-y3
		tem1 *= tem1;
		tem2 *= tem2;
		d1=sqrt(tem1+tem2);//�õ�1,3�ľ���
		
		tem1 = abs(Adc_x[1]-Adc_x[3]);  //x2-x4
		tem2 = abs(Adc_y[1]-Adc_y[3]);  //y2-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d2=sqrt(tem1+tem2);//�õ�2,4�ľ���
		fac=(float)d1/d2;
		if(fac<0.95||fac>1.05)//���ϸ�
		{
			i=0; //���¿�ʼ
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			_DispStringCentered("Calibration date error,\n"
								"Please calibrated again."); /* Ask user to press the touch */
			_WaitForPressedState(1);
			_WaitForPressedState(0);
			continue; //����У׼
		}
		
		//ƽ�б�
		tem1 = abs(Adc_x[0]-Adc_x[3]);  //x1-x4
		tem2 = abs(Adc_y[0]-Adc_y[3]);  //y1-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d1=sqrt(tem1+tem2);//�õ�1,4�ľ���
		
		tem1 = abs(Adc_x[1]-Adc_x[2]);  //x2-x3
		tem2 = abs(Adc_y[1]-Adc_y[2]);  //y2-y3
		tem1 *= tem1;
		tem2 *= tem2;
		d2=sqrt(tem1+tem2);//�õ�3,4�ľ���
		fac=(float)d1/d2;
		if(fac<0.95||fac>1.05)//���ϸ�
		{
			i=0; //���¿�ʼ
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			_DispStringCentered("Calibration date error,\n"
								"Please calibrated again."); /* Ask user to press the touch */
			_WaitForPressedState(1);
			_WaitForPressedState(0);
			continue; //����У׼
		}
		
		flat = 0;
		
		//��ʱ����Ӱ����ݴ������Ĵ���
	}

}


//�����Զ�����У׼
void Init_touch_adj(void)
{   
	Touch_adjust();  //���
    GUI_TOUCH_EnableCalibration(1);//�����Զ�У׼
    GUI_TOUCH_CalcCoefficients(CALIB_POINT_COUT, lcd_x, lcd_y, Adc_x, Adc_y, 400, 240);
}

/////////////////////////////////////////////////////////////
/*********************************************************************
*
*       _StoreUnstable
*/
static void _StoreUnstable(int x, int y) {
  static int _xLast = -1;
  static int _yLast = -1;
  int xOut, yOut;

  if ((x != -1) && (y != -1) && (_xLast != -1) && (_yLast != -1)) {
    xOut = _xLast;    
    yOut = _yLast;    
  } else {
    xOut = -1;
    yOut = -1;    
  }
  _xLast = x;
  _yLast = y;
  GUI_TOUCH_StoreUnstable(xOut, yOut);
  
}

//����ɨ��
void ReadTouch(void)
{

////////////////////////��һ�ַ���,emwin��̳��ķ���//////////////////////////////////////////////
//    static GUI_PID_STATE State;
//    static int IsPressed;
//    int   x;
//    int   y;
//    if(Penirq == 0)
//    {
//          //
//          //���ð��µı�־
//          //
//          IsPressed =  1 ;
//          State.x = TP_Read_XOY(0XD0);  //��ȡx��A / Dֵ
//          State.y = TP_Read_XOY(0X90);  //��ȡy��A / Dֵ
//          State.Pressed =  1 ;        //��Pressed����Ϊ0
//          //
//          //���������ݸ�emWin�������Զ�У׼
//          //
//          GUI_TOUCH_StoreStateEx(&State);
//    }
//    else
//    {
//        if(IsPressed)
//        {
//            IsPressed = 0;
//            State.Pressed =  0;
//        }
//        //
//        //���������ݸ�emWin�������Զ�У׼
//        //
//        GUI_TOUCH_StoreStateEx(&State);
//    }


///////////////////////��2�ַ���������GUI_X_Touch_StoreState.c/////////////////////////////////////
//    static U16 xOld;
//    static U16 yOld;
//    static U8  PressedOld;
//    U16 x, y, xDiff, yDiff;
//    U8  Pressed;
//    Pressed = Penirq;
//    if (Pressed == 0)
//    {
//        x = TP_Read_XOY(0XD0);// TBD: Insert function which reads current x value
//        y = TP_Read_XOY(0X90);// TBD: Insert function which reads current y value
//        //
//        // The touch has already been pressed
//        //
//        if (PressedOld == 1)
//        {
//            //
//            // Calculate difference between new and old position
//            //
//            xDiff = (x > xOld) ? (x - xOld) : (xOld - x);
//            yDiff = (y > yOld) ? (y - yOld) : (yOld - y);
//            //
//            // Store state if new position differs significantly from old position
//            //
//            if (xDiff + yDiff > 2)
//            {
//                xOld = x;
//                yOld = y;
//                GUI_TOUCH_StoreState(x, y);
//            }
//        }
//        //
//        // The touch was previously released
//        // Store state regardless position
//        //
//		else
//		{
//			if ((x != 0) && (y != 0))
//			{
//				xOld = x;
//				yOld = y;
//				PressedOld = 1;
//				GUI_TOUCH_StoreState(x, y);
//			}
//		}
//    //
//    // Touch screen is not pressed
//    // Store state if it was released recently
//    //
//	}
//	else
//	{
//		if (PressedOld == 1)
//		{
//			PressedOld = 0;
//			GUI_TOUCH_StoreState(-1, -1);
//		}
//	}

///////////////////////��3�ַ���,����GUI_TOUCH_Exec///////////////////////////////////////
	static U8 ReadState;
	static int   x;
    static int   y;
	switch (ReadState)
	{
		case 0:
			if(Penirq == 0)  //��������
			{
				x = TP_Read_XOY(0XD0);  //��ȡ����x��adcֵ
			}
			else
			{
				x = -1;
			}

			ReadState++;
			break;
		default:
			if(Penirq == 0)	
			{
				y = TP_Read_XOY(0X90);  //��ȡ����y��adcֵ
			}
			else
			{
				y = -1;
			}
			if((x<100)||(x>4000)||(y<100)||(y>4000)) //��ȡ��ֵ����
			{
				_StoreUnstable(-1, -1);  //
			}
			else
			{
				_StoreUnstable(x, y);
			}
			
//			GUI_TOUCH_StoreUnstable(x, y);
			ReadState = 0;
			break;
	}
////////////////////////��4�ַ����ɲ��հ��������ӵĽ̳�///////////////////////////////////////
}
