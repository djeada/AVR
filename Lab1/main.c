/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */


#include <avr/io.h>
#include <util/delay.h>
#include "longdelay.h"

int main(){


	//port C wyjściowy
	DDRC = 0b11111111;
	//PORTC = 0b10011011;

	//port D wejściowy
	DDRD = 0;

	//rezystory
	PORTD = 0xFF;

	/*while(1){

		if(!(PIND & (1 << 0))){
			PORTC = 0b10011011;
		}
		else {
			PORTC = ~0b10011011;

		}
	}*/
	int time = 255;
	int i = 1;


	while(1){

		if(!(PIND & (1 << 0))){
			if (i % 2 != 0){
				i++;
				while(1){
					PORTC = 0b10000000;
					longdelay(time);
					PORTC = 0b01000000;
					longdelay(time);
					PORTC = 0b00100000;
					longdelay(time);
					PORTC = 0b00010000;
					longdelay(time);
					if(!(PIND & (1 << 0))){
						break;
					}
				}
			}
			else{
				while(1){
					i++;
					PORTC = 0b00010000;
					longdelay(time);
					PORTC = 0b00100000;
					longdelay(time);
					PORTC = 0b01000000;
					longdelay(time);
					PORTC = 0b10000000;
					longdelay(time);
					if(!(PIND & (1 << 0))){
						break;
					}
				}
			}
		}
		else if(!(PIND & (1 << 1))){
			if (time > 500){
				time = 550;
			}
			else {
				time +=30;
			}
			longdelay(10);
		}
		else if(!(PIND & (1 << 2))){
			if (time < 30){
				time = 5;
			}
			else {
				time -=30;
			}
			longdelay(10);
		}
		else{
			longdelay(255);
		}
	}
	return 0;
}
