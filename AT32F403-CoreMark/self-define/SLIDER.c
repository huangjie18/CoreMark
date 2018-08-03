#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_SLIDER_0 (GUI_ID_USER + 0x01)


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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] =
{
    { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 400, 240, 0, 0x0, 0 },
    { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 34, 113, 331, 34, 0, 0x0, 0 },
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



static int _DrawSkin_SLIDER(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
    static GUI_RECT rSlot; //轴的坐标
    static GUI_RECT rSlider = {0, 0, 0, 0};
    int x, y;

    switch (pDrawItemInfo->Cmd)
    {
    case WIDGET_ITEM_DRAW_TICKS: //如果下面不操作则不绘制刻度线
        //以下添加刻度线
        break;
    case WIDGET_ITEM_DRAW_SHAFT: //绘制轴
        rSlot.x0 = pDrawItemInfo->x0;
        rSlot.y0 = pDrawItemInfo->y0;
        rSlot.x1 = pDrawItemInfo->x1;
        rSlot.y1 = pDrawItemInfo->y1;




//        GUI_SetPenSize(5);
//        GUI_SetColor(GUI_GREEN);
//        GUI_DrawLine(rSlot.x0, (rSlot.y0+rSlot.y1)/2, rSlider.x0, (rSlot.y0+rSlot.y1)/2); //画绿线
//        GUI_SetColor(GUI_GRAY);
//        GUI_DrawLine(rSlider.x1, (rSlot.y0+rSlot.y1)/2, rSlot.x1, (rSlot.y0+rSlot.y1)/2); //画灰线
        GUI_DrawGradientRoundedV(rSlot.x0, rSlot.y0 + 12, rSlider.x0 + 8, rSlot.y1 - 12, 3, 0x0000FF, 0x00FFFF);
        GUI_DrawGradientRoundedV(rSlider.x1 - 8, rSlot.y0 + 12, rSlot.x1, rSlot.y1 - 12, 3, 0x00, GUI_GRAY);
//        if(rSlider.y0!=0)
//        {
//            GUI_SetColor(GUI_RED);
//            x = rSlider.x1;
////            GUI_FillCircle(x,(rSlot.y0+rSlot.y1)/2,15); //绘制圆点
//            GUI_FillRect(rSlider.x0,rSlot.y0,rSlider.x1,rSlot.y1);
//        }

        break;

    case WIDGET_ITEM_DRAW_THUMB: //滑块绘制
        rSlider.x0 = pDrawItemInfo->x0;
        rSlider.y0 = pDrawItemInfo->y0;
        rSlider.x1 = pDrawItemInfo->x1;
        rSlider.y1 = pDrawItemInfo->y1;
//        GUI_SetColor(GUI_RED);
//        GUI_DrawCircle((rSlider.x0+rSlider.x1)/2,(rSlider.y0+rSlider.y1)/2,10);
//        GUI_SetColor(GUI_WHITE);
//        GUI_FillCircle((rSlider.x0+rSlider.x1)/2,(rSlider.y0+rSlider.y1)/2,6);
        GUI_SetAlpha(0x70);  //混合透明色,需要比较多的动态内存，如果内存不足则不会有现象
        GUI_SetColor(GUI_YELLOW);
        GUI_FillCircle((rSlider.x0 + rSlider.x1) / 2, (rSlider.y0 + rSlider.y1) / 2, 10);
        GUI_SetAlpha(0);
        GUI_SetColor(GUI_YELLOW);
        GUI_DrawCircle((rSlider.x0 + rSlider.x1) / 2, (rSlider.y0 + rSlider.y1) / 2, 10);
        GUI_SetColor(GUI_WHITE);
        GUI_FillCircle((rSlider.x0 + rSlider.x1) / 2, (rSlider.y0 + rSlider.y1) / 2, 6);
        break;


    case WIDGET_ITEM_DRAW_FOCUS: //聚焦框
        break;
    default:
        return SLIDER_DrawSkinFlex(pDrawItemInfo);
    }
    return 0;
}
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN htlem;
    int NCode;
    int Id;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        htlem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
        SLIDER_SetWidth(htlem, 22);
        SLIDER_SetSkin(htlem, _DrawSkin_SLIDER);
        SLIDER_SetValue(htlem, 50);
        break;

    case WM_PAINT:
        GUI_SetBkColor(GUI_BLUE);
        GUI_Clear();
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_GotoXY(0, 0);
        GUI_DispDecMin(GUI_ALLOC_GetNumFreeBytes());
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (Id)
        {
        case ID_SLIDER_0: // Notifications sent by 'Slider'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_VALUE_CHANGED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
            // USER START (Optionally insert additional code for further Ids)
            // USER END
        }
        break;
    // USER START (Optionally insert additional message handling)
    // USER END
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

WM_HWIN example(void)
{
    WM_HWIN hWin;

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/