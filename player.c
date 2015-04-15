#include "screen.h"
#include "boolean.h"
#include "player.h"
#include "update.h"

int accelerateNextUpdateBoolean = FALSE;
int decelerateNextUpdateBoolean = FALSE;
float journeyCounter = 0;
int acceleration = 0;

int timeInAir = 0;

const int jumpLength = 4;

void accelerate(){
	acceleration+=200;

	//so accelerating doesn't skip events.
	updateCounter-=200;
}


void landJumpingCar(){
	//Gravity for jumping car
	timeInAir--;
	if(screenTop[15] == FLYING){
		if(timeInAir <= 0){
			screenTop[15] = PLAYER;
		}	
	}else if(screenBottom[15] == FLYING){
		if(timeInAir <= 0){
			screenBottom[15] = PLAYER;
		}
	}else if(timeInAir < 10){
		timeInAir = -2;
	}
}

int playerNotFlying(){
	if(screenTop[15] == FLYING || screenBottom[15] == FLYING){
		return FALSE;
	}
	return TRUE;
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

void jump(){
	//Prevent player from spamming jump
	if(timeInAir <= -2){
		if(screenTop[15] == PLAYER){
			screenTop[15] = FLYING;
		}
	
		if(screenBottom[15] == PLAYER){
			screenBottom[15] = FLYING;
		}

		timeInAir = jumpLength;
	}
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


