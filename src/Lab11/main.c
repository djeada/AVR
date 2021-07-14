/*
 * main.c
 *
 *  Created on: 20-02-2019
 *      Author: psm8
 */

#include "1wire.h"
#include "LCD.h"
#include "petitfs-atmega16/diskio.h"
#include "petitfs-atmega16/pff.h"
#include <avr/interrupt.h>
#include <stdlib.h>

FILE lcdOut = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
;

uint16_t T = 0;
uint8_t x1, x2;

int main() {
  lcdinit();
  lcd_write_instr(0b00001100);

  FATFS fs;
  WORD br, bw;
  char buff[16];
  FRESULT res = pf_mount(&fs);

  if (res) {
    fprintf(&lcdOut, "Blad montowania ");
  } else {
    res = pf_open("/data/dane.txt");

    if (res) {
      fprintf(&lcdOut, "Blad otwierania ");
    }

    else {
      res = pf_read(buff, 16, &br);

      if (res) {
        fprintf(&lcdOut, "Blad czytania ");
      } else {
        pf_lseek(0);
        for (int i = 0; i < 10; i++) {
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
          int n = sprintf(buff, "%d\t%0.2lf\n", i, T * 0.0625);
          pf_write(buff, n, &bw);

          lcd_set_xy(1, 0);
          fprintf(&lcdOut, "%0.2lf ", T * 0.0625);
          lcd_write_data(0b11011111);
          fprintf(&lcdOut, "C");
          _delay_ms(1000);
        }
        res = pf_write(0, 0, &bw);
        pf_mount(0);
        lcd_clear();
        fprintf(&lcdOut, "Gotowe");
      }
    }
  }

  return 0;
}
