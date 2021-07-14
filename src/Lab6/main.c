/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */

#include "LCD.h"
#include "spi.h"

FILE lcdOut = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
;

int main() {
  lcdinit();
  InitSPI();
  lcd_clear();
  uint8_t a, b;
  uint16_t c = 0;
  double wynik;
  lcd_clear();
  while (1) {

    // ustawiamy CS na poziom 0
    PORTB |= (1 << 4);
    PORTB &= ~(1 << 4);
    // wysyłamy bit 1
    TransferSPI(1);
    // wysłamy ob10100000 i odbieramy bajt
    a = TransferSPI(0b10100000);
    // wysłamy i odbieramy dowolny
    b = TransferSPI(0);
    // ustawiamy CS na 1
    PORTB |= (1 << 4);
    // konwertujemy C chytrze
    c = ((a & 0x0F) << 8) | b;
    wynik = (double)c * 5. / 4096;
    lcd_set_xy(0, 0);
    fprintf(&lcdOut, "Vin = %.2fV", wynik);
  }

  return 0;
}
