#ifndef __eeprom
#define __eeprom

void EEPROM_Eares(u16 addres);
u8 EEPROM_Read(u16 addres);
void EEPROM_Write(u16 addres,u8 write_data);

#endif