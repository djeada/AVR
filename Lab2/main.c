/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t x = 0;

ISR(INT0_vect){
	_delay_ms(20);
	PORTC = ~x;
	x++;
	//dopóki wciśnięty przycisk
	while(!(PIND&(1<<2)));
}

int main(){

	//konfiguracja
	GICR |= (1 << INT0);
	MCUCR |= (1<<ISC01);
	DDRC = 0xFF;
	PORTD = 0xFF;
	sei();

	while(1){
		//0 zapala diode
		_delay_ms(10000);

	}

	return 0;
}
