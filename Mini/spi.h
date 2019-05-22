/*
 * spi.h
 *
 *  Created on: 03-04-2019
 *      Author: psm8
 */

#ifndef SPI_H_
#define SPI_H_

#define MOSI PB5
#define SCK PB7
#define SS PB4

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>

void InitSPI (void);

uint8_t TransferSPI(uint8_t bajt);
#endif /* SPI_H_ */
