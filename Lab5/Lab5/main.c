/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>

#include "USART.h"

char x;
char bufor[20];
int i = 0;

FILE usartOut = FDEV_SETUP_STREAM(USART_putchar, NULL, _FDEV_SETUP_WRITE);;


ISR(USART_RXC_vect){
	//USART_Transmit(UDR+1);

	bufor[i]=UDR;
	if(bufor[i]=='\r'){
			fprintf(&usartOut, "%s", bufor);
		if(!strncmp((const char*)bufor,"on",2)){
			PORTD&=~(1<<7);
		}
		if(!strncmp((const char*)bufor,"off",3)){
			PORTD|=(1<<7);
		}
		i=0;

	}
	else{
		i++;
	}
}

int main(){
	USART_Init(35);

	//glowny bit przerwan
	sei();

	//7 na D jest wyjściem
	DDRD = (1<<7);

	while(1){

	}

	return 0;
}
