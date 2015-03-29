#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

playMusic(){
		
		while(1){
			OCR1AH = 0x00;
	        OCR1AL = 0x3e;
		
			PORTE ^= (1 << PE4) | (1 << PE5);
			_delay_ms(200);

			OCR1AH = 0x00;
	        OCR1AL = 0x8e;
			PORTE ^= (1 << PE4) | (1 << PE5);
			_delay_ms(200);
}		}
