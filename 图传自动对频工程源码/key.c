#include "all.h"

void KEY_Scan()        //扫描按键
{
  static bit key_mode=0;      				//0：扫描按键     1：自动搜频
	static u8 count=0;   				//按键按下时间计数
	static bit Key_Add_old=1;   //记录上次按键状态
	static bit Key_Sub_old=1;   //记录上次按键状态
	
	if((Key_Add==0)||(Key_Sub==0))
	{
	  count++;
		if(count==200)
		{
		  count=0;
			key_mode=1;
		}
	}
	else count=0;
	
	if(key_mode==0)
	{
		LED_K=1;
		
		if((Key_Add==1)&&(Key_Add_old==0))
		{
			if(channel<47)channel+=1;
			else channel=0;
			RX5808_Set_Freq(Freq_Buff[channel]);
			EEPROM_Eares(0);
			EEPROM_Write(0,channel);
		}
		
		if((Key_Sub==1)&&(Key_Sub_old==0))
		{
			if(channel>0)channel-=1;
			else channel=47;
			RX5808_Set_Freq(Freq_Buff[channel]);
			EEPROM_Eares(0);
			EEPROM_Write(0,channel);
		}
	}
	
	if(key_mode==1)
	{
		LED_K=0;
	  if((Key_Add==1)&&(Key_Sub==1))
		{
		  Channel_Scan();
			key_mode=0;
		}
	}
	
	Key_Add_old=Key_Add;
	Key_Sub_old=Key_Sub;
}