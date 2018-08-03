//Ƥ������

#include "DIALOG.h"


//��ť�۽�Ƥ������
void Button_flex(void)
{
	BUTTON_SKINFLEX_PROPS Props;
	
	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED); //�۽���״̬
	Props.aColorFrame[0] = GUI_GREEN; //Բ�Ǳ߿���ⲿ��ɫ
	Props.aColorFrame[1] = GUI_BLACK; //Բ�Ǳ߿���ڲ���ɫ
	Props.aColorFrame[2] = GUI_RED;   //������ڲ��������ɫ
	Props.aColorLower[0] = GUI_RED;   //�²㽥��ģ��ϲ㣩��ɫ
	Props.aColorLower[1] = GUI_RED;   //�²㽥��ģ��²㣩��ɫ
	Props.aColorUpper[0] = GUI_RED;   //�ϲ㽥��ģ��ϲ㣩��ɫ
	Props.aColorUpper[1] = GUI_RED;   //�ϲ㽥��ģ��²㣩��ɫ
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);  //�۽���ɫ
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);   //������ɫ
	
	BUTTON_SetSkinFlexProps(&Props_Default, BUTTON_SKINFLEX_PI_ENABLED);   //��ʼ����ɫ
	BUTTON_SetDefaultTextColor(GUI_BLACK, BUTTON_CI_UNPRESSED);    //��ť������ɫ
}

/*
*******************************************************************************************
* �� �� ��: Button_flex_2
* ����˵��: ���ð�ť���
* �� ��: ��
* �� �� ֵ: ��
*******************************************************************************************
*/
void Button_flex_2(void)
{
	BUTTON_SKINFLEX_PROPS Props;
//	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED); //�۽���״̬
//	Props.aColorFrame[0] = GUI_GREEN; //Բ�Ǳ߿���ⲿ��ɫ
//	Props.aColorFrame[1] = GUI_BLACK; //Բ�Ǳ߿���ڲ���ɫ
//	Props.aColorFrame[2] = GUI_RED;   //������ڲ��������ɫ
//	Props.aColorLower[0] = GUI_RED;   //�²㽥��ģ��ϲ㣩��ɫ
//	Props.aColorLower[1] = GUI_RED;   //�²㽥��ģ��²㣩��ɫ
//	Props.aColorUpper[0] = GUI_RED;   //�ϲ㽥��ģ��ϲ㣩��ɫ
//	Props.aColorUpper[1] = GUI_RED;   //�ϲ㽥��ģ��²㣩��ɫ
//	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);  //�۽���ɫ
//	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);   //������ɫ

	
	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED); //�۽���״̬
	Props.aColorFrame[0] = GUI_GREEN; //Բ�Ǳ߿���ⲿ��ɫ
	Props.aColorFrame[1] = GUI_BLACK; //Բ�Ǳ߿���ڲ���ɫ
	Props.aColorFrame[2] = GUI_BLUE;   //������ڲ��������ɫ
	Props.aColorLower[0] = GUI_BLUE;   //�²㽥��ģ��ϲ㣩��ɫ
	Props.aColorLower[1] = GUI_BLUE;   //�²㽥��ģ��²㣩��ɫ
	Props.aColorUpper[0] = GUI_BLUE;   //�ϲ㽥��ģ��ϲ㣩��ɫ
	Props.aColorUpper[1] = GUI_BLUE;   //�ϲ㽥��ģ��²㣩��ɫ
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);   //��ʼ��ɫ
	BUTTON_SetDefaultTextColor(GUI_WHITE, BUTTON_CI_UNPRESSED);    //��ť������ɫ
}


//FramewinƤ������
void Framewin_flex(void)
{
	  //���ð�ťƤ��
  	FRAMEWIN_SKINFLEX_PROPS Props;
	FRAMEWIN_GetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE); //��û״̬��Ƥ��
	Props.aColorFrame[0] = GUI_BLACK;
	Props.aColorFrame[1] = GUI_BLACK;
	Props.aColorFrame[2] = GUI_BLACK;
	Props.aColorTitle[0] = 0xC0CEDC;
	Props.aColorTitle[1] = GUI_BLACK;
	Props.BorderSizeL = 0;
	Props.BorderSizeR = 0;
	Props.BorderSizeB = 0;
	Props.Radius = 0;
	FRAMEWIN_SetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE);//���û״̬��Ƥ��
}

//SLIDERƤ������
int _DrawSkin_SLIDER1(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
    static GUI_RECT rSlot; //�������
    static GUI_RECT rSlider = {0, 0, 0, 0};
	static char a=0;
//    int x, y;
	SLIDER_SetWidth(pDrawItemInfo->hWin, 22);
    switch (pDrawItemInfo->Cmd)
    {
    case WIDGET_ITEM_DRAW_TICKS: //������治�����򲻻��ƿ̶���
        //������ӿ̶���
        break;
    case WIDGET_ITEM_DRAW_SHAFT: //������
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
////            GUI_FillCircle(x,(rSlot.y0+rSlot.y1)/2,15); //����Բ��
//            GUI_FillRect(rSlider.x0,rSlot.y0,rSlider.x1,rSlot.y1);
//        }
        break;

    case WIDGET_ITEM_DRAW_THUMB: //�������
        rSlider.x0 = pDrawItemInfo->x0;
        rSlider.y0 = pDrawItemInfo->y0;
        rSlider.x1 = pDrawItemInfo->x1;
        rSlider.y1 = pDrawItemInfo->y1;
		

//        GUI_SetColor(GUI_RED);
//        GUI_DrawCircle((rSlider.x0+rSlider.x1)/2,(rSlider.y0+rSlider.y1)/2,10);
//        GUI_SetColor(GUI_WHITE);
//        GUI_FillCircle((rSlider.x0+rSlider.x1)/2,(rSlider.y0+rSlider.y1)/2,6);
//        GUI_SetAlpha(0x70);  //���͸��ɫ,��Ҫ�Ƚ϶�Ķ�̬�ڴ棬����ڴ治���򲻻�������
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

//�޸�list��
void Listbox_flex(void)
{
	LISTBOX_SetDefaultBkColor(LISTBOX_CI_UNSEL,GUI_LIGHTBLUE); //δѡ���
//	LISTBOX_SetDefaultTextColor(LISTBOX_CI_UNSEL,GUI_WHITE);
}