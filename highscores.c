#include "lcd.h"
#include "memory.h"

int hiscores[5];

int currentNameLocation = 0;
int cursorLocation = 0;
int highscoreScreenUpdateCounter = 0;

int nextUpdateCharUp = 0;
int nextUpdateCharDown = 0;
int nextUpdateCursorLeft = 0;
int nextUpdateCursorRight = 0;

char hiscoresScreenTop[16];
char hiscoresScreenBottom[16];

char name[3];

void highscoreScreenUpdater(){
	highscoreScreenUpdateCounter++;

	if(highscoreScreenUpdateCounter == 10){
		if(nextUpdateCharUp){
			actionCharacterUp();
		}
		if(nextUpdateCharDown){
			actionCharacterDown();
		}
		if(nextUpdateCursorLeft){
			actionCursorLeft();
		}
		if(nextUpdateCursorRight){
			actionCursorRight();
		}

		drawHighscorePage();
		highscoreScreenUpdateCounter = 0;
	}

	for(int i = 0; i < 40; i++){
		lcd_write_data(hiscoresScreenTop[i]);	
	}	

	for(int i = 0; i < 40; i++){
		lcd_write_data(hiscoresScreenBottom[i]);
	}
}

void drawHighscorePage(){
	sprintf(hiscoresScreenTop, "%sBBBCCCDDDEEEF", name);
	strcpy(hiscoresScreenBottom,"QRSTUVWXYZ123456");	
}

void characterDown(){
	nextUpdateCharDown = TRUE;
}

void characterUp(){
	nextUpdateCharUp = TRUE;
}

void cursorLeft(){
	nextUpdateCursorLeft = TRUE;
}

void cursorRight(){
	nextUpdateCursorRight = TRUE;
}

void actionCharacterDown(){
	nextUpdateCharDown = FALSE;
	name[cursorLocation] = name[cursorLocation] - 1;
}

void actionCharacterUp(){
	nextUpdateCharUp = FALSE;
	name[cursorLocation] = name[cursorLocation] + 1;
}

void actionCursorLeft(){
	nextUpdateCursorLeft = FALSE;
	if(cursorLocation != 0){
		cursorLocation--;
	}
}

void actionCursorRight(){
	nextUpdateCursorRight = FALSE;
	if(cursorLocation != 2){
		cursorLocation++;
	}
}



void highscoresAfterGameOver(){

	//read from memory
	for(int i = 0; i < 5; i++){
		hiscores[i] = EEPROM_read(i);
		//EEPROM values are initialized to 0xFF so turn them into score 0
		if(hiscores[i] == 0xFF){
			hiscores[i] = 0x00;
		}
	}

	int score = (int)journeyCounter;

	//check how many times score passes hiscores
	int i = 3;
	while(score > hiscores[i]){
		i--;
	}

	//push up the rest
	int j = 3;
	while(j > i){
		hiscores[j + 1] = hiscores[j];
		j--;
	}

	//input score
	hiscores[j + 1] = score;

	//write to memory
	for(int i = 0; i < 5; i++){
		EEPROM_write(i, hiscores[i]);
	}

	//initialize name
	for(int i = 0; i < 3; i++){
		name[i] = 'A';
	}

	drawHighscorePage();
}
