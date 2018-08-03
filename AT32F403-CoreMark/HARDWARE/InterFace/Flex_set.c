//皮肤设置

#include "DIALOG.h"


//按钮聚焦皮肤设置
void Button_flex(void)
{
	BUTTON_SKINFLEX_PROPS Props;
	
	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED); //聚焦的状态
	Props.aColorFrame[0] = GUI_GREEN; //圆角边框的外部颜色
	Props.aColorFrame[1] = GUI_BLACK; //圆角边框的内部颜色
	Props.aColorFrame[2] = GUI_RED;   //框架与内部区域的颜色
	Props.aColorLower[0] = GUI_RED;   //下层渐变的（上层）颜色
	Props.aColorLower[1] = GUI_RED;   //下层渐变的（下层）颜色
	Props.aColorUpper[0] = GUI_RED;   //上层渐变的（上层）颜色
	Props.aColorUpper[1] = GUI_RED;   //上层渐变的（下层）颜色
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);  //聚焦颜色
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);   //按下颜色
	
	BUTTON_SetSkinFlexProps(&Props_Default, BUTTON_SKINFLEX_PI_ENABLED);   //初始化颜色
	BUTTON_SetDefaultTextColor(GUI_BLACK, BUTTON_CI_UNPRESSED);    //按钮字体颜色
}

/*
*******************************************************************************************
* 函 数 名: Button_flex_2
* 功能说明: 配置按钮外观
* 形 参: 无
* 返 回 值: 无
*******************************************************************************************
*/
void Button_flex_2(void)
{
	BUTTON_SKINFLEX_PROPS Props;
//	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED); //聚焦的状态
//	Props.aColorFrame[0] = GUI_GREEN; //圆角边框的外部颜色
//	Props.aColorFrame[1] = GUI_BLACK; //圆角边框的内部颜色
//	Props.aColorFrame[2] = GUI_RED;   //框架与内部区域的颜色
//	Props.aColorLower[0] = GUI_RED;   //下层渐变的（上层）颜色
//	Props.aColorLower[1] = GUI_RED;   //下层渐变的（下层）颜色
//	Props.aColorUpper[0] = GUI_RED;   //上层渐变的（上层）颜色
//	Props.aColorUpper[1] = GUI_RED;   //上层渐变的（下层）颜色
//	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);  //聚焦颜色
//	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);   //按下颜色

	
	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED); //聚焦的状态
	Props.aColorFrame[0] = GUI_GREEN; //圆角边框的外部颜色
	Props.aColorFrame[1] = GUI_BLACK; //圆角边框的内部颜色
	Props.aColorFrame[2] = GUI_BLUE;   //框架与内部区域的颜色
	Props.aColorLower[0] = GUI_BLUE;   //下层渐变的（上层）颜色
	Props.aColorLower[1] = GUI_BLUE;   //下层渐变的（下层）颜色
	Props.aColorUpper[0] = GUI_BLUE;   //上层渐变的（上层）颜色
	Props.aColorUpper[1] = GUI_BLUE;   //上层渐变的（下层）颜色
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);   //初始颜色
	BUTTON_SetDefaultTextColor(GUI_WHITE, BUTTON_CI_UNPRESSED);    //按钮字体颜色
}


//Framewin皮肤设置
void Framewin_flex(void)
{
	  //设置按钮皮肤
  	FRAMEWIN_SKINFLEX_PROPS Props;
	FRAMEWIN_GetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE); //获得活动状态的皮肤
	Props.aColorFrame[0] = GUI_BLACK;
	Props.aColorFrame[1] = GUI_BLACK;
	Props.aColorFrame[2] = GUI_BLACK;
	Props.aColorTitle[0] = 0xC0CEDC;
	Props.aColorTitle[1] = GUI_BLACK;
	Props.BorderSizeL = 0;
	Props.BorderSizeR = 0;
	Props.BorderSizeB = 0;
	Props.Radius = 0;
	FRAMEWIN_SetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE);//设置活动状态的皮肤
}

//SLIDER皮肤设置
int _DrawSkin_SLIDER1(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
    static GUI_RECT rSlot; //轴的坐标
    static GUI_RECT rSlider = {0, 0, 0, 0};
	static char a=0;
//    int x, y;
	SLIDER_SetWidth(pDrawItemInfo->hWin, 22);
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
	
//        GUI_DrawGradientRoundedV(rSlot.x0, rSlot.y0 + 12, rSlot.x1, rSlot.y1 - 12, 3, 0x0000FF, 0x00FFFF);
		GUI_DrawGradientRoundedV(rSlot.x0+12, rSlot.y0, rSlot.x1-12, rSlot.y1, 3, 0x0000FF, 0x00FFFF);
//		GUI_DrawGradientRoundedV(rSlider.x1 - 8, rSlot.y0 + 12, rSlot.x1, rSlot.y1 - 12, 3, 0x00, GUI_GRAY);
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
//        GUI_SetAlpha(0x70);  //混合透明色,需要比较多的动态内存，如果内存不足则不会有现象
//        GUI_SetColor(GUI_YELLOW);
//        GUI_FillCircle((rSlider.x0 + rSlider.x1) / 2, (rSlider.y0 + rSlider.y1) / 2, 10);
//        GUI_SetAlpha(0);
        GUI_SetColor(GUI_GREEN);
        GUI_FillCircle((rSlider.x0 + rSlider.x1) / 2, (rSlider.y0 + rSlider.y1) / 2, 11);
        GUI_SetColor(GUI_BLUE);
        GUI_FillCircle((rSlider.x0 + rSlider.x1) / 2, (rSlider.y0 + rSlider.y1) / 2, 6);
	
        break;

    default:
        return SLIDER_DrawSkinFlex(pDrawItemInfo);
    }
	
    return 0;
}

//修改list框
void Listbox_flex(void)
{
	LISTBOX_SetDefaultBkColor(LISTBOX_CI_UNSEL,GUI_LIGHTBLUE); //未选项背景
//	LISTBOX_SetDefaultTextColor(LISTBOX_CI_UNSEL,GUI_WHITE);
}