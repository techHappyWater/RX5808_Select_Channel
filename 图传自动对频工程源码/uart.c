#include "all.h"

void UartInit(void)		//115200bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0xE6;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
}

void Uart_Up_Byte(u8 dat)
{
  SBUF=dat;
  while(!TI);
	TI=0;
}

void Uart_Up_Buf(u8 *p)
{
  u8 i;
	for(i=0;p[i];i++)Uart_Up_Byte(p[i]);
}

void Uart_Up_CH_Sig(u8 ch,u8 Sig)
{
	Uart_Up_Byte('0'+(ch+1)/10);
	Uart_Up_Byte('0'+(ch+1)%10);
	Uart_Up_Buf("    ");
  Uart_Up_Byte('A'+(ch)/8);
	Uart_Up_Byte('0'+(ch)%8+1);
	Uart_Up_Buf("    ");
	Uart_Up_Byte('0'+Sig/100);
	Uart_Up_Byte('0'+Sig%100/10);
	Uart_Up_Byte('0'+Sig%10);
	Uart_Up_Buf("\r\n");
}