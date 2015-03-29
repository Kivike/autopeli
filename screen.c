#include "lcd.h"
#include "screen.h"

	int journeyCounter = 0;

void updateScreen(){
	int i;

	journeyCounter++;

	screenTop[0] = (((int)'0')+(journeyCounter % 100 / 10));
	screenTop[1] = (((int)'0')+(journeyCounter % 10));

	for(i = 0; i < 40; i++){
		lcd_write_data(screenTop[i]);
	}

	for(i = 0; i < 40; i++){
		lcd_write_data(screenBottom[i]);
	}
}

void initializeScreen(){
	for(int i = 0; i<16; i++){
		screenTop[i] = ' ';
		screenBottom[i] = ' ';
	}
}

void moveRight(){
	screenTop[15] = 'X';
	screenBottom[15] = ' ';
}

void moveLeft(){
	screenTop[15] = ' ';
	screenBottom[15] = 'X';
}
