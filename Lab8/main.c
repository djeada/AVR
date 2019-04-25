/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: psm8
 */

#include "twi.h"
#include "LCD.h"
#include <avr/interrupt.h>
#include <avr/io.h>

FILE lcdOut = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);;

char* dni[7] = {"pn", "wt", "sr", "cz", "pt", "sb", "nd"};

uint8_t s, min, h, dWeek, dMonth, m, y;

ISR(INT0_vect){
	//wylacz kursor
	lcd_write_instr(0b00001100);

	getTime(&s, &min, &h, &dWeek, &dMonth, &m, &y);
	lcd_set_xy(0,0);

	fprintf(&lcdOut,"%02d:%02d:%02d", h, min, s);

	lcd_set_xy(14,0);
	fprintf(&lcdOut,"%s", dni[dWeek-1]);


	lcd_set_xy(0,1);
	fprintf(&lcdOut,"%02d/%02d/20%02d", dMonth, m, y);
}

int main(){
	lcdinit();
	twiInit();
	setTime(56,59,23,2,31,12,19);

	MCUCR |= (1 << ISC01);
	GICR |= (1<<INT0);
	sei();



	while(1){

	}

	return 0;
}
