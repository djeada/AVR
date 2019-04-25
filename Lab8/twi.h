/*
 * twi.h
 *
 *  Created on: 24-04-2019
 *      Author: Adam Djellouli
 */

#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

void twiInit(void);
void twistart(void);
void twistop(void);
void twiwrite(uint8_t bajt);
uint8_t twiread(uint8_t ack);
void setTime(uint8_t s, uint8_t min, uint8_t h, uint8_t dWeek, uint8_t dMonth, uint8_t m, uint8_t y);
void getTime(uint8_t *s, uint8_t *min, uint8_t *h, uint8_t *dWeek, uint8_t *dMonth, uint8_t *m, uint8_t *y);
uint8_t bcd2dec(uint8_t x);
uint8_t dec2bcd(uint8_t x);

#endif /* TWI_H_ */
