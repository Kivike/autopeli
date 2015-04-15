#include "screen.h"
#include "boolean.h"
#include <stdlib.h>

//Don't spawn two doubles in row
int lastCarSpawnedWasDouble;

void generateCars(){
	int random = rand() % 10;
	
	//Creates a car depending on random
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

				//move everything on top row
				if(screenTop[i + 1] == PLAYER){
					gameIsOver = TRUE;
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

				//move everything on bottom row
				if(screenBottom[i + 1] == PLAYER){
					gameIsOver = TRUE;
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
