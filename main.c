#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "player.h"
#include "screen.h"
#include "boolean.h"
#include "update.h"
#include "input.h"
#include "carController.h"
#include "highscores.h"

//Peetu Nuottaj‰rvi ja Roope Rajala

int gameIsOver;
int menuIsOpen;
int hiscoresOpened = FALSE;

int updateCounter = 0;
const int nthUpdateInit = 2000;
int nthUpdate = 0;

void init(void) {

   		/* estet‰‰n kaikki keskeytykset */
		cli();

        /* kaiutin pinnit ulostuloksi */
        DDRE  |=  (1 << PE4) | (1 << PE5);
        /* pinni PE4 nollataan */
        PORTE &= ~(1 << PE4);
        /* pinni PE5 asetetaan */
        PORTE |=  (1 << PE5);

        /* ajastin nollautuu, kun sen ja OCR1A rekisterin arvot ovat samat */
        TCCR1A &= ~( (1 << WGM11) | (1 << WGM10) );
        TCCR1B |=    (1 << WGM12);
        TCCR1B &=   ~(1 << WGM13);

        /* salli keskeytys, jos ajastimen ja OCR1A rekisterin arvot ovat samat */
        TIMSK |= (1 << OCIE1A);

        /* asetetaan OCR1A rekisterin arvoksi 0x3e (~250hz) */
        OCR1AH = 0x01;
        OCR1AL = 0x36;

        /* k‰ynnist‰ ajastin ja k‰yt‰ kellotaajuutena (16 000 000 / 1024) Hz */
        TCCR1B |= (1 << CS12) | (1 << CS10);

		/* n‰pp‰in pinnit sis‰‰ntuloksi */
		DDRA &= ~(1 << PA0);
		DDRA &= ~(1 << PA2);
		DDRA &= ~(1 << PA4);

		/* rele/led pinni ulostuloksi */
		DDRA |= (1 << PA6);

		/* lcd-n‰ytˆn alustaminen */
		lcd_init();
		lcd_write_ctrl(LCD_ON);
		lcd_write_ctrl(LCD_CLEAR);

		gameIsOver = TRUE;
		menuIsOpen = TRUE;
		nthUpdate = nthUpdateInit;

}

void everySecondUpdate(){
	//The repeating actions 2 times in loop
	moveCars(FAST_CAR);
	moveCars(CAR);	
	generateCars();	
	changeAcceleration();
}

void update(){
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

int main(void){

	/* alusta laitteen komponentit */
	init();
	initializeScreen();
	
    /* ikuinen silmukka */
    while (1) {
		_delay_ms(10);
		
		if(menuIsOpen){
			updateMenu();
			checkInputInMenu();
		}else{
			if(!gameIsOver){
				hiscoresOpened = FALSE;
	       		checkInput();
				update();
			}else{
				if(hiscoresOpened == FALSE){	
					highscoresAfterGameOver();
					hiscoresOpened = TRUE;
				}
				highscoreScreenUpdater();
				checkInputInGameOver();
			}
		}
	}

	return 0;
}

void resetGame(){
	initializeScreen();
	journeyCounter = 0;
	gameIsOver = FALSE;
	nthUpdate = nthUpdateInit;
}

ISR(TIMER1_COMPA_vect) {

	/* vaihdetaan kaiutin pinnien tilat XOR operaatiolla */
 	PORTE ^= (1 << PE4) | (1 << PE5);
}
