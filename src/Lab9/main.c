/*
 * LCD.c
 *
 *  Created on: 06-03-2019
 *      Author: Adam Djellouli
 */

#include <avr/interrupt.h>
#include <stdlib.h>

#include "1wire.h"
#include "LCD.h"

FILE lcdOut = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
;

uint16_t T = 0;
uint8_t x1, x2;

int main() {
  // float pi = 3.14;
  lcdinit();

  // wylacz kursor
  lcd_write_instr(0b00001100);
  // lcd_write_instr(0b00000111);
  // lcd_write_instr(0b00011100);

  while (1) {
    if (!OW_reset()) {
      OW_sendByte(0xCC);
      OW_sendByte(0x44);
      _delay_ms(1000);
      if (!OW_reset()) {
        OW_sendByte(0xCC);
        OW_sendByte(0xBE);
        x1 = OW_recvByte();
        x2 = OW_recvByte();
        T = x2;
        T = (T << 8) | x1;
      }
    }

    lcd_set_xy(1, 0);
    fprintf(&lcdOut, "%0.2lf ", T * 0.0625);
    lcd_write_data(0b11011111);
    fprintf(&lcdOut, "C");
  }

  return 0;
}
