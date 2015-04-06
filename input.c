#include <avr/io.h>
#include <avr/interrupt.h>

void checkInput() {

    if (PINA & (1 << PA0)) {
        // Nappia 0 ei paineta
    } else {
       	moveRight(); // Nappia 0 painetaan
    }

    if (PINA & (1 << PA2)) {
        // Nappia 2 ei paineta
    } else {
        //jump();// Nappia 2 painetaan
    }

    if (PINA & (1 << PA4)) {
        // Nappia 4 ei paineta
    } else {
        moveLeft();// Nappia 4 painetaan
    }	
}
