#ifndef MEMORY_H
#define MEMORY_H

#define TRUE (1==1)
#define FALSE !TRUE

extern float journeyCounter;

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

#endif
