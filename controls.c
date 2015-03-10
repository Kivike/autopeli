#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

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
        // Nappia 0 painetaan
    }

    if (PINA & (1 << PA2)) {
        // Nappia 2 ei paineta
    } else {
        // Nappia 2 painetaan
    }

    if (PINA & (1 << PA4)) {
        // Nappia 4 ei paineta
    } else {
        // Nappia 4 painetaan
    }
}
