#include "lcd.h"

char CAR;
char PLAYER;
char FLYING;
int journeyCounter = 0;
char screenTop[16];
char screenBottom[16];
int gameIsOver = 0;


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

	if(screenTop[15] == FLYING){
		screenTop[15] = PLAYER;
	}

	if(screenBottom[15] == FLYING){
		screenBottom[15] = PLAYER;	
	}
}

void initializeScreen(){
	for(int i = 0; i<16; i++){
		screenTop[i] = ' ';
		screenBottom[i] = ' ';
	}

	CAR = 'C';
	PLAYER = 'X';
	FLYING = 'F';	
}

void moveRight(){
	screenTop[15] = PLAYER;
	screenBottom[15] = ' ';
}

void moveLeft(){
	screenTop[15] = ' ';
	screenBottom[15] = PLAYER;
}

void jump(){
	if(screenTop[15] == PLAYER){
		screenTop[15] == FLYING;
	}
	
	if(screenBottom[15] == PLAYER){
		screenBottom[15] == FLYING;
	}
}

void generateCars(){
	int random = rand() % 10;
	
	if(random == 0){
		screenTop[2] = CAR;
	}	
	if(random == 1){
		screenBottom[2] = CAR;
	}
	

}

void moveCars(){

	for(int i = 15; i > 0; i--){
		if(screenTop[i] == CAR){
			screenTop[i] = ' ';
			if(i != 15){ 
				if(screenTop[i + 1] == PLAYER){
					gameOver();
				}else{
					screenTop[i + 1] = CAR;
 				}
			}
		}

		if(screenBottom[i] == CAR){
			screenBottom[i] = ' ';
			if(i != 15){
				if(screenBottom[i + 1] == PLAYER){
					gameOver();
				}else{
					screenBottom[i + 1] = CAR;
 				}
			}
		}
	}
}

void gameOver(){
	char gameOver[] = "Game Over";
	for(int i = 0; i < sizeof(gameOver); i++){
		screenTop[i] = gameOver[i];
	}
	gameIsOver = 1;
}

int GameIsOver(){
	return gameIsOver;
}
