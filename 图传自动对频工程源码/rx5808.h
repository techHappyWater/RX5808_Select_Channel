#ifndef __rx5808
#define __rx5808
/*
Project:RX5808图传自动对频
Made By:秃秃的科技宅
首发于 ：bilibili

我们的口号是：开源万岁

Note：此代码完全开源，如有大佬拿去完善，请一定把完善过的代码开源！！！

2020.05.16
*/

sbit SCK =P1^5;
sbit LE  =P1^6;
sbit MOSI=P1^7;

extern u16 code Freq_Buff[48];
extern u8 channel;
void RX5808_Set_Freq(u16 F_rf);   //RX5808设置一个频率
void Channel_Scan();              //自动搜频

#endif