/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_1 (GUI_ID_USER + 0x02)
#define ID_SPINBOX_0 (GUI_ID_USER + 0x03)
#define ID_TEXT_2 (GUI_ID_USER + 0x04)
#define ID_TEXT_3 (GUI_ID_USER + 0x05)
#define ID_TEXT_4 (GUI_ID_USER + 0x06)
#define ID_TEXT_5 (GUI_ID_USER + 0x07)
#define ID_TEXT_6 (GUI_ID_USER + 0x08)
#define ID_TEXT_7 (GUI_ID_USER + 0x09)
#define ID_SPINBOX_1 (GUI_ID_USER + 0x0A)
#define ID_SPINBOX_2 (GUI_ID_USER + 0x0B)
#define ID_SPINBOX_3 (GUI_ID_USER + 0x0C)
#define ID_DROPDOWN_0 (GUI_ID_USER + 0x0D)
#define ID_DROPDOWN_1 (GUI_ID_USER + 0x0E)
#define ID_CHECKBOX_0 (GUI_ID_USER + 0x0F)
#define ID_CHECKBOX_1 (GUI_ID_USER + 0x10)
#define ID_CHECKBOX_2 (GUI_ID_USER + 0x11)
#define ID_CHECKBOX_3 (GUI_ID_USER + 0x12)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 285, 240, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 0, 0, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 150, 0, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 0, 21, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 150, 21, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 0, 81, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_5, 150, 81, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_6, 0, 141, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_7, 150, 141, 120, 20, 0, 0x64, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 5, 45, 110, 34, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_1, 150, 45, 110, 34, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_2, 5, 105, 110, 34, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_3, 150, 105, 110, 34, 0, 0x0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 5, 165, 130, 18, 0, 0x0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_1, 150, 165, 130, 18, 0, 0x0, 0 },
	{ CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_0, 5, 190, 130, 20, 0, 0x0, 0 },
	{ CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_1, 150, 190, 130, 20, 0, 0x0, 0 },
	{ CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_2, 5, 215, 130, 20, 0, 0x0, 0 },
	{ CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_3, 150, 215, 130, 20, 0, 0x0, 0 },
	// USER START (Optionally insert additional widgets)
	// USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {

	WM_HWIN hItem, hItem1;
	int     NCode;
	int     Id;


	switch (pMsg->MsgId) {

	case WM_INIT_DIALOG:
		//第一项text控件初始化
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "LOW  PASS"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		//第二项text控件初始化
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "HIGH  PASS"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "Frequency/Hz"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "Frequency/Hz"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "Gain/dB"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "Gain/dB"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "Filter Type"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER); //居中显示
		TEXT_SetText(hItem, "Filter Type"); //显示字符串
		TEXT_SetFont(hItem, GUI_FONT_20_1);



		//FRE选值框控件初始化
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
		SPINBOX_SetEdge(hItem, SPINBOX_EDGE_CENTER); //按钮在左右两边
		SPINBOX_SetFont(hItem, GUI_FONT_16B_1); //设置字体
		SPINBOX_SetRange(hItem,0,20000);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
		SPINBOX_SetEdge(hItem, SPINBOX_EDGE_CENTER); //按钮在左右两边
		SPINBOX_SetFont(hItem, GUI_FONT_16B_1); //设置字体
		SPINBOX_SetRange(hItem, 0, 20000);

		//Gain选值框控件初始化
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_2);
		SPINBOX_SetEdge(hItem, SPINBOX_EDGE_CENTER); //按钮在左右两边
		SPINBOX_SetFont(hItem, GUI_FONT_20_1); //设置字体
		SPINBOX_SetRange(hItem, -10, 10);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_3);
		SPINBOX_SetEdge(hItem, SPINBOX_EDGE_CENTER); //按钮在左右两边
		SPINBOX_SetFont(hItem, GUI_FONT_20_1); //设置字体
		SPINBOX_SetRange(hItem, -10, 10);

		//下拉框初始化
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
		DROPDOWN_AddString(hItem, "Linkwitz-Riley 24");
		DROPDOWN_AddString(hItem, "Butterworth 24");
		DROPDOWN_AddString(hItem, "Bessel 24");
		DROPDOWN_SetFont(hItem, GUI_FONT_16_1);
		DROPDOWN_SetListHeight(hItem, 50); //设置显示高度

		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_1);
		DROPDOWN_AddString(hItem, "Linkwitz-Riley 24");
		DROPDOWN_AddString(hItem, "Butterworth 24");
		DROPDOWN_AddString(hItem, "Bessel 24");
		DROPDOWN_SetFont(hItem, GUI_FONT_16_1);
		DROPDOWN_SetListHeight(hItem, 50); //设置显示高度

		//复选框初始化
		hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
		CHECKBOX_SetText(hItem, "Invert");
		CHECKBOX_SetFont(hItem, GUI_FONT_16B_1);
		CHECKBOX_SetState(hItem, 0); //设置复选框当前状态

		hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
		CHECKBOX_SetText(hItem, "Invert");
		CHECKBOX_SetFont(hItem, GUI_FONT_16B_1);
		CHECKBOX_SetState(hItem, 0); //设置复选框当前状态

		hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
		CHECKBOX_SetText(hItem, "Low-High");
		CHECKBOX_SetFont(hItem, GUI_FONT_16B_1);
		CHECKBOX_SetState(hItem, 0); //设置复选框当前状态

		hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
		CHECKBOX_SetText(hItem, "Mid-High");
		CHECKBOX_SetFont(hItem, GUI_FONT_16B_1);
		CHECKBOX_SetState(hItem, 0); //设置复选框当前状态


		break;
	/*绘制2D*/
	case WM_PAINT:
		//全局背景
		GUI_SetBkColor(GUI_LIGHTBLUE);
		GUI_Clear();


		//填充色块
		GUI_SetColor(GUI_RED);
		GUI_FillRect(0, 0, 285, 20);
		//F/HZ色块
		GUI_SetColor(GUI_GREEN);
		GUI_FillRect(0, 21, 285, 41);

		//TYPE色块
		GUI_SetColor(GUI_GREEN);
		GUI_FillRect(0, 81, 285, 101);

		//GAIN色块
		GUI_SetColor(GUI_GREEN);
		GUI_FillRect(0, 141, 285, 161);


		//画线
		GUI_SetColor(GUI_BLACK);
		GUI_DrawVLine(140, 0, 240);
		GUI_DrawHLine(20, 0, 285);
		GUI_DrawHLine(41, 0, 285);
		GUI_DrawHLine(81, 0, 285);
		GUI_DrawHLine(101, 0, 285);
		GUI_DrawHLine(141, 0, 285);
		GUI_DrawHLine(161, 0, 285);
		GUI_DrawHLine(188, 0, 285);
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN Out_Secondchild(void);
WM_HWIN Out_Secondchild(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
