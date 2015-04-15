#include "lcd.h"
#include "memory.h"

int hiscores[6];

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
char names[20];

void highscoreScreenUpdater(){
	highscoreScreenUpdateCounter++;

	if(highscoreScreenUpdateCounter == 50){
		if(nextUpdateCharUp){
			actionCharacterUp();
			updateMemory();
		}else if(nextUpdateCharDown){
			actionCharacterDown();
			updateMemory();
		}else if(nextUpdateCursorLeft){
			actionCursorLeft();
			updateMemory();
		}else if(nextUpdateCursorRight){
			actionCursorRight();
			updateMemory();
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

void updateMemory(){
	//Write updated highscore list to EEPROM
	for(int i = 0; i <= 12; i+=4){
		EEPROM_write(i, hiscores[i / 4 + 1]);
		EEPROM_write(i + 1, names[i + 1]);
		EEPROM_write(i + 2, names[i + 2]);
		EEPROM_write(i + 3, names[i + 3]);
	}
}

void drawHighscorePage(){
	//you might not understand what this is
	//but it is glorius. the best bug fix in EU i'd say
	//so embrace it
	name[0] = 'A';

	if(currentNameLocation == 0){
		names[1] = name[1];
		names[2] = name[2];
		names[3] = name[3];
	}else if(currentNameLocation == 1){
		names[5] = name[1];
		names[6] = name[2];
		names[7] = name[3];
	}else if(currentNameLocation == 2){
		names[9] = name[1];
		names[10] = name[2];
		names[11] = name[3];
	}else if(currentNameLocation == 3){
		names[13] = name[1];
		names[14] = name[2];
		names[15] = name[3];
	}
	sprintf(hiscoresScreenTop, "%c%c%c %2d %c%c%c %2d   ", names[1], names[2], names[3], hiscores[1], names[5], names[6], names[7], hiscores[2]);
	sprintf(hiscoresScreenBottom,"%c%c%c %2d %c%c%c %2d   ",names[9], names[10], names[11], hiscores[3], names[13], names[14], names[15], hiscores[4]);
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
	if(name[cursorLocation] == 0x40){
		name[cursorLocation] = 0x5A;
	}
}

void actionCharacterUp(){
	nextUpdateCharUp = FALSE;
	name[cursorLocation] = name[cursorLocation] + 1;
	if(name[cursorLocation] == 0x5B){
		name[cursorLocation] = 0x41;
	}
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
	for(int i = 0; i <= 12; i+=4){
		hiscores[i / 4 + 1] = (char)EEPROM_read(i);
		names[i + 1] = (char)EEPROM_read(i + 1);
		names[i + 2] = (char)EEPROM_read(i + 2);
		names[i + 3] = (char)EEPROM_read(i + 3);
		//EEPROM values are initialized to 0xFF or 0x00 so make them valid
		if(hiscores[i / 4 + 1] == 0xFF){
			hiscores[i / 4 + 1] = 0x00;
		}
		for(int j = 1; j < 4; j++){
			if(names[i + j] == 0xFF || names[i + j] == 0x00){
				names[i + j] = 'A';
			}
		}
	}

	int score = ((int)journeyCounter % 100 / 10) + ((int)journeyCounter % 10);

	//check how many times score passes hiscores
	int i = 1;
	while(score < hiscores[i]){
		i++;
	}

	//push up the rest
	for(int j = 4; j > i; j--){
		hiscores[j] = hiscores[j - 1];
		names[j * 4 + 1] = names[(j - 1) * 4 + 1];
		names[j * 4 + 2] = names[(j - 1) * 4 + 2];
		names[j * 4 + 3] = names[(j - 1) * 4 + 3];
	}

	//input score
	hiscores[i] = score;

	//initialize name
	for(int k = 0; k < 4; k++){
		name[k] = 'A';
	}

	//write to memory
	updateMemory();

	currentNameLocation = i - 1;

	drawHighscorePage();
	
}
