#include "screen.h"

accelerateNextUpdateBoolean = FALSE;
decelerateNextUpdateBoolean = FALSE;

const int jumpLength = 4;

void accelerate(){
	acceleration+=200;

	//so accelerating doesn't skip events.
	updateCounter-=200;
}


void landJumpingCar(){
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

void jump(){
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


