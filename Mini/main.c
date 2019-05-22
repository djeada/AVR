/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: psm8
 */

#include "spi.h"
#include "LCD.h"
#include "USART.h"
#include <stdlib.h>

FILE lcdOut = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);;
double tempMin, tempMax, temperatura = 0;
char bufor[50];
int i = 0;


/*
ISR(USART_RXC_vect){
	//USART_Transmit(UDR+1);

	bufor[i]=UDR;
	if(bufor[i]=='\r'){
			fprintf(&lcdOut, "%s", bufor);
		if(!strncmp((const char*)bufor,"on",2)){
			fprintf(&lcdOut, "Temperatura: %.1f, Max: %.1f, Min: %.1f ", temperatura, tempMax, tempMin);
		}
		i=0;
	}
	else{
		i++;
	}
}
*/

int main(){

	//incjalizacja zmiennych
	tempMin = 28;
	tempMax = 30;

	USART_Init(35);

	//glowny bit przerwan
	sei();

	//port C wejściowy
	DDRC &= ~(1 << 1);
	DDRC &= ~(1 << 2);
	DDRC &=	~(1 << 3);
	DDRC &=	~(1 << 4);

	//port C rezystory
	PORTC &= ~(1 << 1);
	PORTC &= ~(1 << 2);
	PORTC &= ~(1 << 3);
	PORTC &= ~(1 << 4);

	//wyjście na miejscu 0
	DDRC |= (1 << 0);

	lcdinit();
	//wylacz kursor
	lcd_write_instr(0b00001100);
	InitSPI();
	lcd_clear();
	uint8_t a, b;
	uint16_t c = 0;
	lcd_clear();
	PORTC &= ~(1 << 0);

	while(1){

		//ustawiamy CS na poziom 0
		PORTB|=(1<<4);
		PORTB&=~(1<<4);
		//wysyłamy bit 1
		TransferSPI(1);
		//wysłamy ob10100000 i odbieramy bajt
		a=TransferSPI(0b10100000);
		//wysłamy i odbieramy dowolny
		b=TransferSPI(0);
		//ustawiamy CS na 1
		PORTB|=(1<<4);
		//konwertujemy C chytrze
		c=((a&0x0F)<<8)|b;
		temperatura=(double)c*5./4096*100;

		//wyswietlenie temperatury
		lcd_set_xy(0,0);
		fprintf(&lcdOut, "Temp = %.1f", temperatura);
		lcd_write_data(0b11011111);
		fprintf(&lcdOut, "C");

		lcd_set_xy(0,1);
		fprintf(&lcdOut, "%.1f", tempMin);
		lcd_write_data(0b11011111);
		fprintf(&lcdOut, "C");

		lcd_set_xy(8,1);
		fprintf(&lcdOut, " %.1f", tempMax);
		lcd_write_data(0b11011111);
		fprintf(&lcdOut, "C");

		_delay_ms(100);

		//warunek Tmin < Tmax
		if(tempMin < tempMax){
			//zwiekszamy lub zmniejszamy progi w zaleznosci od przycisku
			if(!(PINC & (1 << 1))){
				tempMin -= 1;
				if(tempMin <= -55){
					tempMin = 55;
				}
			}
			if(!(PINC & (1 << 2))){
				tempMin += 1;
				if(tempMin > 150){
					tempMin =150;
				}
			}
			if(!(PINC & (1 << 3))){
				tempMax -= 1;
				if(tempMax <= -55){
					tempMax = 55;
				}
			}
			if(!(PINC & (1 << 4))){
				tempMax += 1;
				if(tempMax > 150){
					tempMax =150;
				}
			}
		}
		//wlaczenie pieca
		if(temperatura < tempMin){
			//zapal diode
			PORTC &= ~(1 << 0);
		}
		if (temperatura > tempMax) {
			//zgas diode
			PORTC |= (1 << 0);

		}
	}

	return 0;
}
