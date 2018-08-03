//#include "stm32f10x.h"
//#include "delay.h"
//#include "ILI93xx.h"
//#include "malloc.h"
//#include "GUI.h"
//#include "timer.h"
//#include "GUIDemo.h"
//#include "test.h"
//#include "led.h"
//#include "key.h"
//#include "Interface.h"
//#include "example.h"
//#include "touch.h"
//#include "iic.h"
//#include "24c16.h"
///**************************************
//***********ע������********************
//STM32��Ϊ����оƬ
//1.��DeviceΪGDF303ʱ���øĶ�������ֱ����,��ΪGDF303
//û��FPU��Ԫ;
//2.��DeviceΪATF403ʱ,ATF403ӵ��FPU��Ԫ������ʱ�õ�
//EMWIN-CM3��û��֧��FPU��Ԫ,�������FPU������Ӳ������,
//�ر�FPU��Ԫ������ʹ�á�
//�رղ��裺Target -> Floating Poirt Hardware -> Not Used
//3.������Ƶ����Ҫ��FSMC���ٶȣ�����emwin������������

//4.����ֱ�Ӱ�Device ΪATF403�ĳ���ֱ�����ص�STM32�ϣ��������У�Ҫ��Device
//////////////////
//4.���ʹ��SRAM-224k��Ҫ����EOPB0 Ϊ 0xfe��ZW���128k�ָ�SRAM,NZW������128k��
//��ʱ��ZW�̶�Ϊ128k


//5.*ע�⣺�����GPоƬʹ�õ�stm32��flash�����㷨�����������ʹ�û�GD��flash�㷨
//*������DB13��DB15Ҫ��ת


//***************************************/

////��ǰҳ����
//WM_HWIN hWin_now;

///*
//*******************************************************************************************
//* �� �� ��: GPIO_TEST
//* ����˵��: ��������GUI��������
//* �� ��: ��
//* �� �� ֵ: ��
//*******************************************************************************************
//*/
//void GPIO_TEST(void)
//{
//    GUI_Init();
//    /* ���ò��Ժ��� */
//	GUI_SetBkColor(GUI_WHITE);
//	GUI_SetColor(GUI_BLACK);
//    GUI_Clear();
//	GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
//	GUI_FillCircle(120, 64, 40);
//	GUI_SetDrawMode(GUI_DRAWMODE_XOR);
//	GUI_FillCircle(140, 84, 40);
//    while (1)
//    {
//        GUI_Delay(10);
//    }

//}

///*
//*******************************************************************************************
//* �� �� ��: All_Init
//* ����˵��: ��������
//* �� ��: ��
//* �� �� ֵ: ��
//*******************************************************************************************
//*/
//void All_Init(void)
//{
//	delay_init();
//	delay_ms(3000); //�ȴ���Ƭ�������ȶ�
//	/*************************AT32F403***********************************/
//	//��֤��β�����ԴҪ�ȶ����������оƬ,���������ٶȽ���(������)��
//	//��SRAM��չΪ224k,ֻ������AT32ϵ��оƬ,Ҫ�������β�����������
//	//�������أ�MEM1_MAX_SIZEһ��Ҫ<(96*1024),�Ա�֤������ȷ,����ȷ����SRAMΪ224k
//	//�ڶ������أ�MEM1_MAX_SIZE��������>96k,Ȼ��ע�������
////	FLASH_Unlock();  //����FLASH
////	FLASH_EraseOptionBytes();
////	FLASH_ProgramOptionByteData(0x1FFFF810,0xFE);// 224 KB SRAM 96+128
////	FLASH_Lock();//����
//	/*****************************END*************************************/
//	
//	
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//    LED_GPIO_Init();        //����LED��ʼ��,ȫ��
//    KEY_GPIO_Init();        //������ʼ��
//    Encoder_GPIO_Init();    //��������ʼ��
//    Lcd_Initialize();       //LCD��ʼ��
//    TIM3_Int_Init(999, (SystemCoreClock/1000000-1)); //1KHZ ��ʱ��1ms
//	TP_Init();             //���������ų�ʼ��
//	my_mem_init(SRAMIN);    //��������ʹ���ⲿRAM,�õ��ⲿSRAM��ʹ��
//	IIC_Init();             //��������24c16
////  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE); //ʹ��CRCʱ�ӣ�����STemWin����ʹ��,�˴���emwin���Բ���
//	
//}

///*
//*******************************************************************************************
//* �� �� ��: main
//* ����˵��: ������
//* �� ��: ��
//* �� �� ֵ: int
//*******************************************************************************************
//*/
//int main(void)
//{
//    u8 key_value = 0;
//    u8 key_value1 = 0;
//    u8 key_value2 = 0;
//    u8 key_value3 = 0;
//	u8 mem_use = 0;  //�ڴ�ʹ����
//	u8 *p=0;         //�������ݵ�ָ��
//    u16 count = 0;
//	u32 key_count = 0;
//    GUI_COLOR color;
//	All_Init();  //���������ʼ��
////	GPIO_TEST();  //����
//	MainTask(); //������

//    while(1)
//    {
//        if(WM_IsWindow(hWin_now)) //�ж�hWin_now�Ƿ���Ч,Framewin���ڿͻ������
//        {

//            /***********************************��ť���************************************/
//            //�����⣬������whileѭ��,��Ҫע��������ѭ��
//            key_value1 = Encoder_Check_One();   //��ť1���
//            key_value2 = Encoder_Check_Two();   //��ť2���
//            key_value3 = Encoder_Check_Three(); //��ť3���
//            //�˳���һ��ֻ���һ����ť����
//            if((key_value1 != Encoder_static) || (key_value2 != Encoder_static)
//               || (key_value3 != Encoder_static)) //�ж���
//            {
//                if(key_value1)
//                {
//                    key_value = key_value1;
//                }
//                else if(key_value2)
//                {
//                    key_value = key_value2;
//                }
//                else if(key_value3)
//                {
//                    key_value = key_value3;
//                }

//                switch(key_value)
//                {
//                    case Encoder1_left:
//                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_LEFT); //������ť���͵���Ϣ
//                        //��ֱ��ִ�б��۽����ڵĻص�����
//                        //���ù��̣�GUI_SendKeyMsg->WM_SendMessage->�ص�����->����WM_NOTIFY_PARENT
//                        //��������

//                        break;

//                    case Encoder1_right:
//                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_RIGHT);
//                        break;

//                    case Encoder2_left:
//                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_OUT_LEFT); //�����ť
//                        break;

//                    case Encoder2_right:
//                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_OUT_RIGHT);
//                        break;

//                    case Encoder3_left:
//                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_LEFT); //control��ť
//                        break;
//                    case Encoder3_right:
//                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_RIGHT);
//                        break;

//                    default:
//                        break;
//                }//end of switch(key_value)
//				key_count = 0;
//            }//end of if
//			else  //û����ť����
//			{
//				key_count++;  
//				if(key_count >= 1000) //����ԼXXXms��û�ж���
//				{
//					key_count = 0;
//					WM_SendMessageNoPara(hWin_now, MSG_KNOB_NULL);  
//				}
//			}


//            /*********************************�������*********************************/
//            key_value = KEY_Scan(0);
//            if(key_value)
//            {
//                switch(key_value)
//                {
//                    //���밴ť
//                    case KEY_INPUT:
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
//                        //�Ȱѵ�ȫ��
//                        LED_All_Off;
//                        Input_led_On; //����
//                        break;

//                    //�˳���ť
//                    case KEY_ESC:
//                        //�Ȱѵ�ȫ��
//                        LED_All_Off;
//                        Esc_led_On; //����
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_ESC);
//                        break;

//                    //�����ť
//                    case KEY_OUTPUT:
//                        //�Ȱѵ�ȫ��
//                        LED_All_Off;
//                        Out_led_On; //����
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
//                        break;

//                    //ϵͳ��ť
//                    case KEY_SYSTEM:
//                        LED_All_Off;
//                        Sys_led_On; //����
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_SYSTEM);
//                        break;

//                    //��ť1
//                    case KEY_EN_1:
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
//                        break;

//                    //��ť2
//                    case KEY_EN_2:
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
//                        break;

//                    //��ť3
//                    case KEY_EN_3:
////                  GUI_SendKeyMsg(GUI_KEY_ENTER, 1);  //����ȷ����������Ϣ
//                        WM_SendMessageNoPara(hWin_now, MSG_KEY_CONTROL);
//                        break;
//                    default:
//                        break;
//                }//end of switch(key_value)

//            }//end of key_value
//        }
//        else   //��Ч��ˢRED��
//        {
//            GUI_SetBkColor(GUI_RED);
//            GUI_Clear();

//            GUI_SetColor(GUI_BLACK);
//            GUI_GotoXY(0, 0);
//            GUI_DispDecMin(GUI_ALLOC_GetNumFreeBytes());
//			
//			//��ʾ�ڴ�ʹ����
////			p = mymalloc(0,20480); //����20k
//			mem_use = my_mem_perused(SRAMIN);
//			GUI_GotoXY(0, 10);
//			GUI_DispDecMin(mem_use);
////			myfree(0,p);          //�ͷ��ڴ�
//        }

//        if(count == 1000)
//        {
//            count = 0;
//            LED = ~LED;  //LED��ת���������ϵͳ�Ƿ���������
//        }
//        GUI_Delay(1);
//        count++;

//    }

//}


