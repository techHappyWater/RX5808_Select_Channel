#include "all.h"

/*************EEPROM读写*************/
//**************************************************************** 
//  扇区擦除 
//---------------------------------------------------------------- 
void EEPROM_Eares(u16 addres) 
{      
	IAP_ADDRL=addres;     //低位地址 
	IAP_ADDRH=addres>>8;  //高位地址 
	IAP_CONTR=0x01;  
	IAP_CONTR=IAP_CONTR|0x82; //设时间与充ISP操作
	IAP_CMD=0x03;         //扇区命命令 
	IAP_TRIG=0x5a;        //触发 
	IAP_TRIG=0xa5;        //触发启动。 
	_nop_();_nop_();_nop_();_nop_();
	IAP_ADDRL=0xff; 
	IAP_ADDRH=0xff; 
	IAP_CONTR=0x00; 
	IAP_CMD=0x00; 
	IAP_TRIG=0x00;  
} 
//**************************************************************** 
//  读数据 
//---------------------------------------------------------------- 
u8 EEPROM_Read(u16 addres) 
{ 
	IAP_ADDRL=addres;     //低位地址 
	IAP_ADDRH=addres>>8;  //高位地址 
	IAP_CONTR=0x01;  
	IAP_CONTR=IAP_CONTR|0x82; //设时间与充ISP操作
	IAP_CMD=0x01;         //写命令 
	IAP_TRIG=0x5a;        //触发 
	IAP_TRIG=0xa5;        //触发启动。 
	_nop_();_nop_();_nop_();_nop_(); 
	IAP_ADDRL=0xff; 
	IAP_ADDRH=0xff; 
	IAP_CONTR=0x00; 
	IAP_CMD=0x00; 
	IAP_TRIG=0x00; 

	return(IAP_DATA);         
} 
//**************************************************************** 
//  写数据 
//---------------------------------------------------------------- 
void EEPROM_Write(u16 addres,u8 write_data) 
{ 
	IAP_DATA=write_data;  //要写入的数据。 
	IAP_ADDRL=addres;     //低位地址 
	IAP_ADDRH=addres>>8;  //高位地址 
	IAP_CONTR=0x01;  
	IAP_CONTR=IAP_CONTR|0x82; //设时间与充ISP操作。 
	IAP_CMD=0x02;         //写命令 
	IAP_TRIG=0x5a;        //触发 
	IAP_TRIG=0xa5;        //触发启动。 
	_nop_();_nop_();_nop_();_nop_();
	IAP_ADDRL=0xff; 
	IAP_ADDRH=0xff; 
	IAP_CONTR=0x00; 
	IAP_CMD=0x00; 
	IAP_TRIG=0x00;   
} 
