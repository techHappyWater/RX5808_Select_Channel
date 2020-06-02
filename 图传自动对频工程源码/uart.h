#ifndef __uart
#define __uart

void UartInit(void);		//115200bps@12.000MHz
void Uart_Up_Byte(u8 dat);
void Uart_Up_Buf(u8 *p);
void Uart_Up_CH_Sig(u8 ch,u8 Sig);

#endif