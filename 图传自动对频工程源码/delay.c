#include "all.h"
/*
Project:RX5808图传自动对频
Made By:秃秃的科技宅
首发于 ：bilibili

我们的口号是：开源万岁！！！

Note：此代码完全开源，如有大佬拿去完善，请一定把完善过的代码开源！！！

2020.05.16
*/
void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(u16 time)
{
  while(time--)Delay1ms();
}