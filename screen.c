#include "lcd.h"
#include "memory.h"
#include "boolean.h"
#include "update.h"
#include <util/delay.h>

char screenTop[16];
char screenBottom[16];

const char CAR = 0x01;
const char FAST_CAR = 0x02;
const char RUBBLE = 0x03;
const char PLAYER = 0x00;
const char FLYING = 0x04;


void initializeScreen(){
	for(int i = 0; i<16; i++){
		screenTop[i] = ' ';
		screenBottom[i] = ' ';
	}

	//PLAYER
	lcd_write_ctrl(0x40);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11111);
	lcd_write_data(0b10111);
	lcd_write_data(0b10111);
	lcd_write_data(0b11111);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);

	//CAR
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11111);
	lcd_write_data(0b11101);
	lcd_write_data(0b11101);
	lcd_write_data(0b11111);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);

	//FAST_CAR
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11001);
	lcd_write_data(0b11111);
	lcd_write_data(0b11111);
	lcd_write_data(0b11001);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);

	//RUBBLE
	lcd_write_data(0b00000);
	lcd_write_data(0b10110);
	lcd_write_data(0b00011);
	lcd_write_data(0b00111);
	lcd_write_data(0b01111);
	lcd_write_data(0b00111);
	lcd_write_data(0b00010);
	lcd_write_data(0b00000);

	//JUMP
	lcd_write_data(0b01100);
	lcd_write_data(0b01100);
	lcd_write_data(0b11111);
	lcd_write_data(0b10111);
	lcd_write_data(0b10111);
	lcd_write_data(0b11111);
	lcd_write_data(0b01100);
	lcd_write_data(0b01100);
	lcd_write_ctrl(0x80);


	//PUT PLAYER ON SCREEN
	screenTop[15] = PLAYER;
}

void updateScreen(){
	int i;

	journeyCounter+=0.05;

	nthUpdate = nthUpdateInit / 100 * (100 - journeyCounter);

	landJumpingCar();

	screenTop[0] = (((int)'0')+((int)journeyCounter % 100 / 10));
	screenTop[1] = (((int)'0')+((int)journeyCounter % 10));

	for(i = 0; i < 40; i++){
		lcd_write_data(screenTop[i]);	
	}

	for(i = 0; i < 40; i++){
		lcd_write_data(screenBottom[i]);
	}
}

int selection = 0;
int menuUpdateCounter = 0;

void updateMenu(){
	menuUpdateCounter++;

	char top[] = " NEW GAME       ";
	char bottom[] = " HIGHSCORES     ";

	if(selection == 0){
		top[0] = '>';
		bottom[0] = ' ';
	}else{
		top[0] = ' ';
		bottom[0] = '>';
	}
	int i;
	for(i = 0; i < 40; i++){
		lcd_write_data(top[i]);	
	}

	for(i = 0; i < 40; i++){
		lcd_write_data(bottom[i]);
	}
}

