#include <avr/io.h>
#include <avr/interrupt.h>
//#include "lcd.h"

/*
DDRA
Napit: PA0, PA2, PA4
LED: PA6

DDRE
Kaiutin: PE4 ja PE5
*/

void checkInput() {

    if (PINA & (1 << PA0)) {
        // Nappia 0 ei paineta
    } else {
       	moveRight(); // Nappia 0 painetaan
    }

	if (PINA & (1 << PA1)) {
       	// Nappia 1 ei paineta
    } else { 
		// Nappia 1 painetaan
		accelerateNextUpdate();
    }

    if (PINA & (1 << PA2)) {
        // Nappia 2 ei paineta
    } else {
        jump();// Nappia 2 painetaan
    }

	if (PINA & (1 << PA3)) {
        decelerateNextUpdate();
    }

    if (PINA & (1 << PA4)) {
        // Nappia 4 ei paineta
    } else {
        moveLeft();// Nappia 4 painetaan
    }
}

void checkInputInGameOver(){
    if (PINA & (1 << PA0)) {
        // Nappia 0 ei paineta
    } else {
       	characterUp(); // Nappia 0 painetaan
    }

	if (PINA & (1 << PA1)) {
       	// Nappia 1 ei paineta
    } else { 
		// Nappia 1 painetaan
		cursorLeft();
    }

    if (PINA & (1 << PA2)) {
        // Nappia 2 ei paineta
    } else {
        resetGame();// Nappia 2 painetaan
    }

    if (PINA & (1 << PA3)) {
        // Nappia 2 ei paineta
    } else {
       cursorRight(); // Nappia 2 painetaan
    }

	if (PINA & (1 << PA4)) {
        // Nappia 4 ei paineta
    } else {
        characterDown();// Nappia 4 painetaan
    }
}
