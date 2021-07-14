/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */

#include <avr/io.h>
#include <util/delay.h>

int main() {

  DDRA = 0b11111111;

  while (1) {

    PORTA ^= 0xFF;
    _delay_ms(500);
  }

  return 0;
}
