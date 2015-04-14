#include "lcd.h"
#include "memory.h"

int hiscores[5];

int currentNameLocation = 0;
int cursorLocation = 1;
int highscoreScreenUpdateCounter = 0;

int nextUpdateCharUp = 0;
int nextUpdateCharDown = 0;
int nextUpdateCursorLeft = 0;
int nextUpdateCursorRight = 0;

char hiscoresScreenTop[16];
char hiscoresScreenBottom[16];

char name[4];
char names[12];

void highscoreScreenUpdater(){
	highscoreScreenUpdateCounter++;

	if(highscoreScreenUpdateCounter == 50){
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
	//you might not understand what this is
	//but it is glorius. the best bug fix in EU i'd say
	//so embrace it
	name[0] = 'A';

	if(currentNameLocation = 0){
		names[0] = name[1];
		names[1] = name[2];
		names[2] = name[3];
	}
	if(currentNameLocation = 1){
		names[3] = name[1];
		names[4] = name[2];
		names[5] = name[3];
	}
	if(currentNameLocation = 2){
		names[6] = name[1];
		names[7] = name[2];
		names[8] = name[3];
	}
	if(currentNameLocation = 3){
		names[9] = name[1];
		names[10] = name[2];
		names[11] = name[3];
	}

	sprintf(hiscoresScreenTop, "%c%c%c %2d %c%c%c %2d   ", names[0], names[1], names[2], hiscores[0], names[3], names[4], names[5], hiscores[1]);
	sprintf(hiscoresScreenBottom,"%c%c%c %2d %c%c%c %2d   ",names[6], names[7], names[8], hiscores[2], names[9], names[10], names[11], hiscores[3]);
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
	if(cursorLocation != 1){
		cursorLocation--;
	}
}

void actionCursorRight(){
	nextUpdateCursorRight = FALSE;
	if(cursorLocation != 3){
		cursorLocation++;
	}
}



void highscoresAfterGameOver(){

	//read from memory
	for(int i = 0; i < 12; i+=4){
		hiscores[i / 4] = EEPROM_read(i);
		names[i + 1] = EEPROM_read(i + 1);
		names[i + 2] = EEPROM_read(i + 2);
		names[i + 3] = EEPROM_read(i + 3);
		//EEPROM values are initialized to 0xFF so turn them into score 0
		if(hiscores[i / 4] == 0xFF){
			hiscores[i] = 0x00;
		}
	}
	hiscores[5] = 0;
	names[9] = 'A';
	names[10] = 'A';
	names[11] = 'A';

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
	for(int i = 0; i < 4; i++){
		name[i] = 'A';
	}
	
	if(j + 1 == 0){
		currentNameLocation = 0;
	}
	if(j + 1 == 0){
		currentNameLocation = 1;
	}
	if(j + 1 == 0){
		currentNameLocation = 2;
	}
	if(j + 1 == 0){
		currentNameLocation = 3;
	}

	drawHighscorePage();
}
