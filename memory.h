#ifndef MEMORY_H
#define MEMORY_H

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

#endif
