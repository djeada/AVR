/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */

#include <avr/interrupt.h>
#include <avr/io.h>

//raz na 100ms wywolane przerwanie i sprawdzamy czy wcisnieto przycisk


int licznik = 0;
int i = 0;
int j,d,s,t;

int arr[10]={0b11000000, 0b11111001, 0b10100100,0b10110000, 0b10011011, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000 };

//obsluga przerwania sprawdzanie przycisku
/*ISR(TIMER1_COMPA_vect){
	//czy wcisnieto przycisk
	if(!(PIND&(1<<6))){
		//zmieniamy stan diody
		PORTC ^=(1<<0);
	}
}*/


void modulo(){
	t = licznik%10000/1000;
	s = licznik%1000/100;
	d = licznik%100/10;
	j = licznik%10;
}

//licznik sekund
ISR(TIMER1_COMPA_vect){
	licznik++;
}

ISR(TIMER0_COMP_vect){

		modulo();
		PORTC=~(1<<i);
		if(i==0){
			PORTD=arr[j];
		}
		if(i==1){
			PORTD=arr[d];
		}
		if(i==2){
			PORTD=arr[s];
		}
		if(i==3){
			PORTD=arr[t];
		}
		i++;

		if (i > 3){
			i=0;
		}
}

int main(){

	OCR1A=10;
	//rejestr kontrolny, ustawiamy tryb pracy by utrzymac clk I/O /1024 (From prescaler
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<CS12);
	TCCR1B |= (1<<CS10);

	//przycisk
	//PORTD |= (1<<6);
	//dioda
	//DDRC |= (1<<0);

	//przerwanie przy porownaniu, gdy licznik doliczy do wartosci OCR1A
	TIMSK |= (1<<OCIE1A);

	DDRD = 0xFF;
	DDRC = 0xFF;

	OCR0=53;
	TCCR0 |= (1<<WGM01);
	TCCR0 |= (1<<CS02);
	TCCR0 |= (1<<CS00);
	TIMSK |= (1<<OCIE0);

	//glowny bit przerwan, na koncu wlaczamy zasilanie
	sei();


	while(1){

	}

	return 0;
}
