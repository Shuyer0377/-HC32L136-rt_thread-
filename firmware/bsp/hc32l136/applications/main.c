
#include "board.h"

#include <rtthread.h>
#include <rtdevice.h>
#include "oled.h"
#include "bmp.h"
#include "rtc_calendar.h"
#include "dht11.h"



int32_t main(void)
{

	
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
  OLED_Clear();
	RTC_Init_Config();
	DHT11_Init();
	
	
	OLED_ShowString(32,10,"Smart",24,1); //LOGO
	OLED_ShowString(20,35,"Bracelet",24,1); //LOGO
	OLED_Refresh();
	delay1ms(3000);
	OLED_Clear();
	while(1)
	{
//	OLED_Clear();
	  OLED_Refresh();
//		delay1ms(200);
		
		Display_Time();   //��������ʾ
		

		Display_DHT11();  //��ʪ����ʾ


	}
}












