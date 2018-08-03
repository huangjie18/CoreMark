/*********************************************************************
*          Portions COPYRIGHT 2014 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.26 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "ILI93xx.h"
#include "example.h"
#include "touch.h"
//�봥�����йض��壬����ʵ�������д  ADֵ������Ӧ���ص�ģ���Ҫ�Լ���д��ֵͬ������ͬ��λ�ô�λ
#define TOUCH_AD_TOP		3820  	//���´������Ķ�����д�� X ��ģ������ֵ��
#define TOUCH_AD_BOTTOM		150 	//���´������ĵײ���д�� X ��ģ������ֵ��
#define TOUCH_AD_LEFT 		3760    //���´���������࣬д�� Y ��ģ������ֵ��
#define TOUCH_AD_RIGHT		380	    //���´��������Ҳ࣬д�� Y ��ģ������ֵ��


#define Drive_LCD  1   //1ʹ������ԭ�����̣�0ʹ��Ұ������������
/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#if Drive_LCD
	#define XSIZE_PHYS  400 // To be adapted to x-screen size
	#define YSIZE_PHYS  240 // To be adapted to y-screen size
#else
	#define XSIZE_PHYS  240 // To be adapted to x-screen size
	#define YSIZE_PHYS  400 
#endif
/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

  

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
static void LcdWriteReg(U16 Data) {
  // ... TBD by user
	*(__IO u16 *) (Bank1_LCD_C) = Data;
}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdWriteData(U16 Data) {
  // ... TBD by user
	*(__IO u16 *) (Bank1_LCD_D) = Data;
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
	  *(__IO u16 *) (Bank1_LCD_D) = *pData++;
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
	  *pData++ = *(__IO u16 *) (Bank1_LCD_D);
  }
}

static U16 LcdReadData(void)
{
	U16 pData;
	pData = *(__IO u16 *) (Bank1_LCD_D);
	return pData;
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
#if Drive_LCD
//����ԭ���������ã���������STemwin��û�е�LCD���������õ�GUIDRV_Template.c
void LCD_X_Config(void) {
	int TouchOrientation;
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  //��GUIDRV_Template.c�������Լ�������LCD����
  pDevice=GUI_DEVICE_CreateAndLink(&GUIDRV_Template_API, GUICC_M565, 0, 0);//����ԭ����������
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  /////////////////////////////////////////////////////////////
  //X��Y�ķ����Ƿ񽻻�
//	 TouchOrientation = (GUI_MIRROR_X * LCD_GetMirrorX()) |
//	(GUI_MIRROR_Y * LCD_GetMirrorY()) |
//	(GUI_SWAP_XY * LCD_GetSwapXY()) ;
//	GUI_TOUCH_SetOrientation(TouchOrientation);

  //ʹ��stemwin�Դ��Ĵ�����У׼
  #if (USE_TOUCH_MODE == 1)
  GUI_TOUCH_Calibrate(GUI_COORD_X, 0, 399, TOUCH_AD_TOP , TOUCH_AD_BOTTOM);
  GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, 239, TOUCH_AD_LEFT, TOUCH_AD_RIGHT);
  #else
  #endif
  
//  GUI_TOUCH_EnableCalibration(1);//����
//  GUI_TOUCH_CalcCoefficients(3,lcd_x,lcd_y,Adc_x,Adc_y,400,240);

	
}
#else
//Ұ���������ã�����STemwin��֧�ֵ�LCD����,û���õ�GUIDRV_Template.c
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR,GUICC_M565, 0, 0);//Ұ����������
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
  Config.FirstCOM = 0;                                          //modify by fire
  Config.FirstSEG = 0;                                          //modify by fire  
  Config.Orientation = GUI_SWAP_XY | GUI_MIRROR_X;					    //modify by fire  ����		
//  Config.NumDummyReads = 2;                                     //modify by fire ʹ����ILI9341��������������Ƿ�ע����

  GUIDRV_FlexColor_Config(pDevice, &Config);
  
  

//  // Set controller and operation mode
//  //
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B16);
  
  GUIDRV_FlexColor_SetReadFunc66709_B16(pDevice,GUIDRV_FLEXCOLOR_READ_FUNC_III);
}
#endif
/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
	  	Lcd_Initialize();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

