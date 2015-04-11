	#include "lcd.h"

	const int FALSE = 0;
	const int TRUE = 1;

	char screenTop[16];
	char screenBottom[16];

	float journeyCounter = 0;
	int gameOverBool;
	
	const char CAR = 'C';
	const char FAST_CAR = 'K';
	const char PLAYER = 'X';
	const char FLYING = 'F';
	const int jumpLength = 4;

	//Don't spawn two doubles in row
	int lastCarSpawnedWasDouble;
	int timeInAir = 0;

	int updateCounter = 0;
	const int nthUpdateInit = 1000;
	int nthUpdate;

void initializeScreen(){
	for(int i = 0; i<16; i++){
		screenTop[i] = ' ';
		screenBottom[i] = ' ';
	}
	gameOverBool = FALSE;
	lastCarSpawnedWasDouble = FALSE;
	nthUpdate = nthUpdateInit;
}

update(){
	updateCounter++;
	if(updateCounter == nthUpdate / 2){
		moveCars(FAST_CAR);
		updateScreen();
	}
	if(updateCounter == nthUpdate){
		moveCars(CAR);
		moveCars(FAST_CAR);
		generateCars();
		updateScreen();
		updateCounter = 0;
	}
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

void landJumpingCar(){
	if(screenTop[15] == FLYING){
		timeInAir++;
		if(timeInAir >= jumpLength){
			screenTop[15] = PLAYER;
		}	
	}

	if(screenBottom[15] == FLYING){
		timeInAir++;
		if(timeInAir >= jumpLength){
			screenBottom[15] = PLAYER;
		}	
	}
}

void moveRight(){
	if(playerNotFlying()){
		screenTop[15] = PLAYER;
		screenBottom[15] = ' ';
	}

}

void moveLeft(){
	if(playerNotFlying()){
		screenTop[15] = ' ';
		screenBottom[15] = PLAYER;
	}
}

int playerNotFlying(){
	if(screenTop[15] == FLYING || screenBottom[15] == FLYING){
		return 0;
	}
	return 1;
}

void generateCars(){
	int random = rand() % 10;
	
	if(random == 0){
		screenTop[2] = CAR;
	}	
	if(random == 1){
		screenBottom[2] = CAR;
	}
	if(random == 2 && !lastCarSpawnedWasDouble){
		screenTop[2] = CAR;
		screenBottom[2] = CAR;
		lastCarSpawnedWasDouble = TRUE;
	}else{
		lastCarSpawnedWasDouble = FALSE;
	}
	if(random == 3){
		screenTop[2] = FAST_CAR;
	}
	if(random == 4){
		screenBottom[2] = FAST_CAR;
	}


}

void moveCars(char car){

	for(int i = 15; i > 0; i--){

		if(screenTop[i] == car){
			screenTop[i] = ' ';
			if(i != 15){

				//move everything
				if(screenTop[i + 1] == PLAYER){
					gameOver();
				}else if(screenTop[i + 1] == FLYING){
					screenTop[i + 1] = FLYING;
				}else if(screenTop[i + 1] == CAR){
					//explosion when 2 cars collide
					screenTop[i + 1] = ' ';
				}else{
					screenTop[i + 1] = car;
				}			
			}
		}

		if(screenBottom[i] == car){
			screenBottom[i] = ' ';
			if(i != 15){ 

				//move everything
				if(screenBottom[i + 1] == PLAYER){
					gameOver();
				}else if(screenBottom[i + 1] == FLYING){
					screenBottom[i + 1] = FLYING;
				}else if(screenBottom[i + 1] == CAR){
					//explosion when 2 cars collide
					screenBottom[i + 1] = ' ';
				}else{
					screenBottom[i + 1] = car;
				}	
			}
		}
	}
}

void jump(){
	if(screenTop[15] == PLAYER){
		screenTop[15] = FLYING;
	}
	
	if(screenBottom[15] == PLAYER){
		screenBottom[15] = FLYING;
	}

	timeInAir = 0;
}

void gameOver(){
	char gameOver[] = "GAME OVER";
	for(int i = 0; i < sizeof(gameOver); i++){
		screenTop[i] = gameOver[i];
	}
	gameOverBool = TRUE;
}

int gameIsOver(){
	return gameOverBool;
}

void resetGame(){
	initializeScreen();
	journeyCounter = 0;
	gameOverBool = FALSE;
	nthUpdate = 1000;
}
