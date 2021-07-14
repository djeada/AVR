/*
 * USART.h
 *
 *  Created on: 22-05-2019
 *      Author: Adam Djellouli
 */

#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include <stdio.h>

void USART_Init(unsigned int baud);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);
int USART_putchar(char c, FILE *stream);

#endif /* USART_H_ */
