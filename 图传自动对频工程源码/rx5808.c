#include "all.h"
/*
Project:RX5808图传自动对频
Made By:秃秃的科技宅
首发于 ：bilibili

我们的口号是：开源万岁

Note：此代码完全开源，如有大佬拿去完善，请一定把完善过的代码开源！！！

2020.05.16
*/


/*
数据帧格式：
			4位		寄存器地址
      1位		允许读写控制
			20位	数据
			
20位数据格式：
			7位		A
			13位	N
			
A和N的计算公式：
			F_rf-479=F_lo=2*(N*32+A)*(F_osc/R)
			其中：F_osc=8Mhz	R=8

先发低位！！！！！！！！！！！！！！！！！！

硬件改动：需去掉一个电阻，否则将无法使用

可以去百度查看RX5808具体介绍，百度文库网址：
https://wenku.baidu.com/view/40e85b9e6037ee06eff9aef8941ea76e59fa4a6e.html
*/

#define Synthesizer_Register_B 				0x01  //频率设置寄存器
#define Power_Down_Control_Register   0x0a  //电源控制寄存器
#define State_Register                0x0f  //状态控制寄存器

u16 code Freq_Buff[48]=
{
	5865,5845,5825,5805,5785,5765,5745,5725,		//A	CH1-8
	5733,5752,5771,5790,5809,5828,5847,5866,		//B	CH1-8
	5705,5685,5665,5645,5885,5905,5925,5945,		//C	CH1-8
	5740,5760,5780,5800,5820,5840,5860,5880,		//D	CH1-8
	5658,5695,5732,5769,5806,5843,5880,5917,		//E	CH1-8
	5362,5399,5436,5473,5510,5547,5584,5621,		//F	CH1-8
};

u8 channel=0;

//spi发送一位数据
void SPI_Send_Bit(bit Value)
{
  SCK =0;
	_nop_();
	MOSI=Value;
	_nop_();
	SCK =1;
	_nop_();
}

//spi发送长度为len位数据
//根据时序图，要求先发送数据低位
void SPI_Send_Bits(u32 Value,u8 len)
{
  u8 i;
	for(i=0;i<len;i++)
	{
	  SPI_Send_Bit((bit)(Value&0x01));
		Value>>=1;
	}
}

void Send_Register_Data(u8 addr,u32 Dat)   //向地址为addr寄存器发送数据
{
  LE=0;                   //相当于CS，低电平选中芯片，允许传输数据
	SPI_Send_Bits(addr,4);  //先发送寄存器4位地址
	SPI_Send_Bit(1);        //允许写入
	SPI_Send_Bits(Dat,20);  //发送20位控制数据
	
	//一帧数据传输完成
	LE=1;
	SCK=0;
	MOSI=0;
}

void RX5808_Set_Freq(u16 F_rf)   //RX5808设置一个频率
{
  u32 dat;
	u16 F_lo=(F_rf-479)/2;
	u16 SYN_RF_N;
	u16 SYN_RF_A;
	
	SYN_RF_N=F_lo/32;    //计算此频率下N值
	SYN_RF_A=F_lo%32;    //计算此频率下A值
	
	dat=SYN_RF_N;
	dat<<=7;
	dat|=SYN_RF_A;       //得到20位控制数据
	
	//设置频率控制寄存器
	Send_Register_Data(Synthesizer_Register_B,dat);
}

void Channel_Scan()  //自动搜频
{
	u8 i;
	u8 sig;
	u8 sig_max=0;
	
	ADC_Translate();
	
	for(i=0;i<48;i++)
	{
	  RX5808_Set_Freq(Freq_Buff[i]);
		delay_ms(15);
		sig=ADC_Translate();
//		Uart_Up_CH_Sig(i,sig);
		
		if(sig>sig_max)sig_max=sig,channel=i;
	}
	
//	Uart_Up_Buf("\r\n");
//	Uart_Up_Buf("The final channel is :  ");
//	Uart_Up_CH_Sig(channel,sig_max);
	
	EEPROM_Eares(0);
	EEPROM_Write(0,channel);      //频率数值存入eeprom
	RX5808_Set_Freq(Freq_Buff[channel]);    //设置频率
}
