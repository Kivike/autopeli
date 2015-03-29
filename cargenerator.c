#include "screen.h"

const char CAR = 'c';

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
				screenTop[i + 1] = CAR;
			}
		}

		if(screenBottom[i] == CAR){
			screenBottom[i] = ' ';
			if(i != 15){ 
				screenBottom[i + 1] = CAR;
			}
		}


	}


}
