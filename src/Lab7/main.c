/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */

#include "USART.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

// ICR1 = 27647
// OCR1A = 1244 - 2902

// TCR1A |= (1 << COM1A1);
// TCR1A |= (1 << WGM11);
// TCR1B |= (1 << WGM12);
// TCR1B |= (1 << WGM13);
// TCR1B |= (1 << CS11);

char x;
char bufor[20];
int i = 0;
int liczba = 1250;

FILE usartOut = FDEV_SETUP_STREAM(USART_putchar, NULL, _FDEV_SETUP_WRITE);
;

int wartoscY(int x) { return 14 * x + 1244; }

ISR(USART_RXC_vect) {
  // USART_Transmit(UDR+1);

  bufor[i] = UDR;
  if (bufor[i] == '\r') {
    fprintf(&usartOut, "%s", bufor);
    /*if(!strncmp((const char*)bufor,"on",2)){
            PORTD&=~(1<<7);
    }
    if(!strncmp((const char*)bufor,"off",3)){
            PORTD|=(1<<7);
    }*/
    liczba = wartoscY(atoi(bufor));

    i = 0;

  } else {
    i++;
  }
}

int main() {
  USART_Init(35);

  // glowny bit przerwan
  sei();

  // 7 i 5 na D jest wyjściem
  DDRB |= (1 << 3);
  DDRD |= (1 << 5);

  TCCR1A |= (1 << COM1A1);
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << WGM13);
  TCCR1B |= (1 << CS11);

  ICR1 = 27647;
  OCR1A = 1250;

  TCCR0 |= (1 << WGM00);
  TCCR0 |= (1 << WGM01);
  TCCR0 |= (1 << COM01);
  TCCR0 |= (1 << CS02);

  while (1) {
    // OCR1A = liczba;
    //_delay_ms(1000);

    for (int j = 0; j < 255; j++) {
      OCR0 = j;
      _delay_ms(2);
    }
    for (int k = 255; k > 0; k--) {
      OCR0 = k;
      _delay_ms(2);
    }
  }

  return 0;
}
