#include "all.h"
/*
Project:RX5808图传自动对频
Made By:秃秃的科技宅
首发于 ：bilibili

我们的口号是：开源万岁！！！

Note：此代码完全开源，如有大佬拿去完善，请一定把完善过的代码开源！！！

2020.05.16
*/

void main()
{
	UartInit();		//115200bps@12.000MHz
	P3M0&=0x7c;   //P3.0、P3.1、P3.7设为准双向口
	P3M1&=0x7c;
	P3M0|=0x40;   //P3.6设为推挽输出
	P3M1&=~0x40;
	P1M0&=0x1f;   //P1.7、P1.6、P1.5设为准双向口
	P1M1&=0x1f;
	
	LED_A=1;
	delay_ms(100);
	//Channel_Scan();
	
	channel=EEPROM_Read(0);
	RX5808_Set_Freq(Freq_Buff[channel]);
	
  while(1)
	{
	  delay_ms(10);
		KEY_Scan();        //扫描按键
	}
}
