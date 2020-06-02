#include "all.h"
/*
Project:RX5808图传自动对频
Made By:秃秃的科技宅
首发于 ：bilibili

我们的口号是：开源万岁

Note：此代码完全开源，如有大佬拿去完善，请一定把完善过的代码开源！！！

2020.05.16
*/

u8 ADC_Translate()
{
  P1ASF=0x10;
	ADC_CONTR=0xec;
	while(!(ADC_CONTR&0x10));    //等待转换完成
	
	return ADC_RES;
}
