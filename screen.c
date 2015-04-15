#include "lcd.h"
#include "memory.h"
#include <util/delay.h>

char screenTop[16];
char screenBottom[16];

float journeyCounter = 0;
int gameOverBool;


const char CAR = 0x01;
const char FAST_CAR = 0x02;
const char RUBBLE = 0x03;
const char PLAYER = 0x00;
const char FLYING = 0x04;

const int jumpLength = 4;

//Don't spawn two doubles in row
int lastCarSpawnedWasDouble;

int timeInAir = 0;

int updateCounter = 0;
const int nthUpdateInit = 2000;
int nthUpdate;
int acceleration = 0;

int accelerateNextUpdateBoolean;
int decelerateNextUpdateBoolean;

void initializeScreen(){
	for(int i = 0; i<16; i++){
		screenTop[i] = ' ';
		screenBottom[i] = ' ';
	}

	
	gameOverBool = FALSE;
	lastCarSpawnedWasDouble = FALSE;
	nthUpdate = nthUpdateInit;
	accelerateNextUpdateBoolean = FALSE;
	decelerateNextUpdateBoolean = FALSE;

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


}

update(){
	updateCounter++;

	int updateStep = nthUpdate - acceleration;
	
	//so you cant accelerate past 0 steps and go over the 
	if(updateStep < 10) updateStep = 10;

	if(updateCounter == updateStep / 4){
		moveCars(FAST_CAR);
		updateScreen();
	}
	if(updateCounter == updateStep / 2){
		everySecondUpdate();
		updateScreen();
		//makes sure you don't step over with accelerating
	}
	if(updateCounter >= updateStep){
		everySecondUpdate();
		moveCars(RUBBLE);
		updateCounter = 0;
		updateScreen();	
	}
}

void everySecondUpdate(){
	moveCars(FAST_CAR);
	moveCars(CAR);	
	generateCars();	
	changeAcceleration();
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
		return FALSE;
	}
	return TRUE;
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
				}else if(screenTop[i + 1] == CAR || screenTop[i + 1] == RUBBLE){
					//explosion when 2 cars or car and rubble collide
					screenTop[i + 1] = RUBBLE;
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
				}else if(screenBottom[i + 1] == CAR || screenBottom[i + 1] == RUBBLE){
					//explosion when 2 cars or car and rubble collide
					screenBottom[i + 1] = RUBBLE;
				}else{
					screenBottom[i + 1] = car;
				}	
			}
		}
	}
}

void accelerate(){
	acceleration+=200;

	//so accelerating doesn't skip events.
	updateCounter-=200;
}

void decelerate(){
	if(acceleration >= 200){
		acceleration-=200;
		//so accelerating doesn't skip events.
		updateCounter+=200;
	}else{
		//so accelerating doesn't skip events.
		updateCounter+=acceleration;
		acceleration=0;
	}
}

void accelerateNextUpdate(){
	accelerateNextUpdateBoolean = TRUE;
}

void decelerateNextUpdate(){
	decelerateNextUpdateBoolean = TRUE;
}

void changeAcceleration(){
	if(accelerateNextUpdateBoolean == TRUE){
		accelerateNextUpdateBoolean = FALSE;
		accelerate();
	}

	if(decelerateNextUpdateBoolean == TRUE){
		decelerateNextUpdateBoolean = FALSE;
		decelerate();
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

	gameOverBool = TRUE;
}

int gameIsOver(){
	return gameOverBool;
}

void resetGame(){
	initializeScreen();
	journeyCounter = 0;
	gameOverBool = FALSE;
	nthUpdate = nthUpdateInit;
}
