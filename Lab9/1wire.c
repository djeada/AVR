#include "1wire.h"
/*
 * LCD.c
 *
 *  Created on: 06-03-2019
 *      Author: Adam Djellouli
 */

uint8_t OW_reset(void){
	int result;
	OW_low; // Drives DQ low
	_delay_us(480);
	OW_high; // Releases the bus
	_delay_us(70);
	result = OW_check; // Sample for presence pulse from slave
	_delay_us(410);
	return result; // Return sample presence pulse result
}

void    OW_send(uint8_t bit){
	if (bit)
	{
	// Write '1' bit
		OW_low; // Drives DQ low
	_delay_us(6);
	OW_high; // Releases the bus
	_delay_us(64);
	}
	else
	{
	// Write '0' bit
		OW_low; // Drives DQ low
	_delay_us(60);
	OW_high; // Releases the bus
	_delay_us(10);
	}
}

uint8_t OW_recv(void){
	int result;
	OW_low; // Drives DQ low
	_delay_us(6);
	OW_high; // Releases the bus
	_delay_us(9);
	result = OW_check; // Sample the bit value from the slave
	_delay_us(55);
	return result;
}

void  OW_sendByte(uint8_t data){
	int loop;

	// Loop to write each bit in the byte, LS-bit first
	for (loop = 0; loop < 8; loop++){
		OW_send(data & 0x01);
		// shift the data byte for the next bit
		data >>= 1;
	}
}

uint8_t OW_recvByte(void){
	int loop, result=0;
	for (loop = 0; loop < 8; loop++)
	{
	// shift the result to get it ready for the next bit
	result >>= 1;
	// if result is one, then set MS bit
	if (OW_recv())
	result |= 0x80;
	}
	return result;
}
