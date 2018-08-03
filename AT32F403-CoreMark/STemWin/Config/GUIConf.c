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
File        : GUIConf.c
Purpose     : Display controller initialization
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
#include "malloc.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Define the available number of bytes available for the GUI
//
//#define GUI_NUMBYTES  0x200000

//自己修改的代码
#define USE_EXRAM  0//不使用外部SRAM
#define GUI_NUMBYTES  15*1024 //设置STemWin内存大小
#define GUI_BLOCKSIZE 0X80  //块大小
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   available memory for the GUI.
*/
//void GUI_X_Config(void) {
//  //
//  // 32 bit aligned memory area
//  //
//  static U32 aMemory[GUI_NUMBYTES / 4];
//  //
//  // Assign memory to emWin
//  //
//  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
//  //
//  // Set default font
//  //
//  GUI_SetDefaultFont(GUI_FONT_6X8);
//}
/*************************** 自己修改的程序 ****************************/
void GUI_X_Config(void)
{
	if(USE_EXRAM) //使用外部RAM
	{
		//从外部SRAM中分配GUI_NUMBYTES字节的内存
		U32 *aMemory = mymalloc(SRAMEX,GUI_NUMBYTES);
		//为存储管理系统分配一个存储块
		GUI_ALLOC_AssignMemory((void*)aMemory,GUI_NUMBYTES);
		//设置存储块的平均尺寸，该区越大，可用的存储块数量越少
		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
		//设置默认字体
		GUI_SetDefaultFont(GUI_FONT_6X8);
	}
	else
	{
		//从内部RAM中分配GUI_NUMBYTES字节的内存
//		U32 *aMemory = mymalloc(SRAMIN,GUI_NUMBYTES);
//		//为存储管理系统分配一个存储块
//		GUI_ALLOC_AssignMemory((void*)aMemory,GUI_NUMBYTES);
//		//设置存储块的平均尺寸，该区越大，可用的存储块数量越少
//		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
//		//设置默认字体
//		GUI_SetDefaultFont(GUI_FONT_6X8);
		
		
		static U32 aMemory[GUI_NUMBYTES / 4];
		/*  Assign memory to emWin */
		GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); 
	}
}
/*************************** End of file ****************************/
