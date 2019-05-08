/*
 * LCD.c
 *
 *  Created on: 06-03-2019
 *      Author: Adam Djellouli
 */




#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define LCD_PORT PORTA
#define LCD_DDR DDRA
#define RS 2
#define E 3

//inicjalizacja wyswietlacza
void lcdinit(void);

//funkcja wysyłająca
void lcd_write_instr(uint8_t data);

//funkcja realizująca instrukcję
void lcd_clear(void);

//funckaj wysyłająca
void lcd_write_data(uint8_t data);

//funkcja ustawiająca
void lcd_set_xy(uint8_t x, uint8_t y);

//funkcja wyświetlająca tekst znajdujący sie w w pamięci
void lcd_write_text_xy(uint8_t x, uint8_t y, char *text);

int lcd_putchar(char c, FILE *stream);

#endif /* LCD_H_ */
