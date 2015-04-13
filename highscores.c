#include "lcd.h"

int hiscores[5];

void drawHighscorePage(){

}

void askForName(){

}

void highscoresAfterGameOver(){
	for(int i = 0; i < 5; i++){
		hiscores[i] = EEPROM_read(i);
	}

	for(int i = 4; i >= 0; i--){
		if(journeyCounter > hiscores[i]){
			int j = 4;
			while(j > i){
				hiscores[j] = hiscores[j - 1];
				j--;
			}
			hiscores[j] = journeyCounter;
		}
	}

	for(int i = 0; i < 5; i++){
		EEPROM_write(i, hiscores[i]);
	}
	
}
