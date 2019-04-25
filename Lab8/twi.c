/*
 * twi.c
 *
 *  Created on: 24-04-2019
 *      Author: Adam Djellouli
 */

#include "twi.h"


void twiInit(void){
	TWBR = 47;
	twistart();
	twiwrite(0xD0);
	twiwrite(7);
	twiwrite(0b00010000);
	twistop();
}


// procedura transmisji sygnału START
void twistart(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
// procedura transmisji sygnału STOP
void twistop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while ((TWCR & (1<<TWSTO)));
}

// procedura transmisji bajtu danych
void twiwrite(uint8_t bajt) {
	TWDR = bajt;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
//procedura odczytu bajtu danych
uint8_t twiread(uint8_t ack){
	TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t bcd2dec(uint8_t x){
	return ((x>> 4)*10) + (x&0x0F);
}

uint8_t dec2bcd(uint8_t x){
	return ((x/10) << 4) | (x%10);
}

void setTime(uint8_t s, uint8_t min, uint8_t h, uint8_t dWeek, uint8_t dMonth, uint8_t m, uint8_t y){
	twistart();
	twiwrite(0xD0);
	twiwrite(0);
	twiwrite(dec2bcd(s));
	twiwrite(dec2bcd(min));
	twiwrite(dec2bcd(h));
	twiwrite(dec2bcd(dWeek));
	twiwrite(dec2bcd(dMonth));
	twiwrite(dec2bcd(m));
	twiwrite(dec2bcd(y));
	twistop();
}

void getTime(uint8_t *s, uint8_t *min, uint8_t *h, uint8_t *dWeek, uint8_t *dMonth, uint8_t *m, uint8_t *y){
	twistart();
	twiwrite(0xD0);
	twiwrite(0);
	twistart();
	twiwrite(0xD1);

	*s = bcd2dec(twiread(1));
	*min = bcd2dec(twiread(1));
	*h = bcd2dec(twiread(1));
	*dWeek = bcd2dec(twiread(1));
	*dMonth = bcd2dec(twiread(1));
	*m = bcd2dec(twiread(1));
	*y = bcd2dec(twiread(0));

	twistop();
}

