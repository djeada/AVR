/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: Adam Djellouli
 */

#include "LCD.h"
#include <avr/interrupt.h>

FILE lcdOut = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
;

int main() {
  int i = 1;
  // float f = 3.14;
  lcdinit();
  // fprintf(&lcdOut, "Hello world %.2f :)", f);

  // stdout = &lcdOut;
  // printf("Hello world! \n");
  // lcd_write_text_xy(1,0, "test");

  // lcd_write_instr(0x40);
  // lcd_write_data(0b00001111);
  // lcd_write_data(0b00011011);
  // lcd_write_data(0b00011011);
  // lcd_write_data(0b00011011);
  // lcd_write_data(0b00011111);
  // lcd_write_data(0b00011011);
  // lcd_write_data(0b00011011);
  // lcd_write_data(0b00011011);
  // lcd_set_xy(0,0);
  // lcd_write_data(0);
  // wylacz kursor
  lcd_write_instr(0b00001100);
  lcd_write_instr(0b00000111);
  lcd_write_instr(0b00011100);

  while (1) {
    lcd_set_xy(16, 0);
    fprintf(&lcdOut, "Stacja metra %d                          ", i++);
  }

  return 0;
}
