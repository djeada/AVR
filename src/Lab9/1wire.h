/*
 * LCD.c
 *
 *  Created on: 06-03-2019
 *      Author: Adam Djellouli
 */

#ifndef WIRE_H_
#define WIRE_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define OW_PIN PB3
#define OW_DIR DDRB
#define OW_OUT PORTB
#define OW_IN PINB
#define OW_low OW_DIR |= 1 << OW_PIN
#define OW_high OW_DIR &= ~(1 << OW_PIN)
#define OW_check (OW_IN & (1 << OW_PIN))

uint8_t OW_reset(void);
void OW_send(uint8_t bit);
uint8_t OW_recv(void);
void OW_sendByte(uint8_t data);
uint8_t OW_recvByte(void);

#endif /* 1WIRE_H_ */
