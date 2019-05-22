/*
 * spi.c
 *
 *  Created on: 03-04-2019
 *      Author: psm8
 */


#include "spi.h"

void InitSPI (void) {
	//ustawienie kierunku wyjściowego dla linii MOSI, SCK i SS
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);
	//aktywacja SPI, tryb Master, prędkość zegara Fosc/64
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

uint8_t TransferSPI(uint8_t bajt){
	SPDR = bajt;
	//czekamy na ustawienie flagi SPIF po zakończeniu transmisji
	while( !(SPSR&(1<<SPIF)) );
	return SPDR;
}
