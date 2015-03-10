#include "lcd.h"

	char screenTop[] = "0123456789ABCDEF";
	char screenBottom[] = "GHIJKLMNOPQRSTUV";

void updateScreen(){

	int i;

	for(i = 0; i < 40; i++){
		lcd_write_data(screenTop[i]);
	}

	for(i = 0; i < 40; i++){
		lcd_write_data(screenBottom[i]);
	}
}
