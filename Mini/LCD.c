/*
 * LCD.c
 *
 *  Created on: 22-05-2019
 *      Author: Adam Djellouli
 */

#include "LCD.h"

void lcdinit(void){
	//ustawiamy na port wyjsciowy
	LCD_DDR = 0xFF;
	lcd_write_instr(0x33);
	lcd_write_instr(0x32);
	lcd_write_instr(0x28);
	lcd_write_instr(0x08);
	lcd_write_instr(0x01);
	lcd_write_instr(0x06);
	lcd_write_instr(0x0F);
}


void lcd_write_instr(uint8_t data){
	//rs do zera
	LCD_PORT &= ~(1 << RS);
	//e w górę
	LCD_PORT |= (1 << E);

	LCD_PORT = (LCD_PORT&0x0F)|(data&0xF0);
	_delay_ms(1);

	//e do zera
	LCD_PORT &= ~(1 << E);

	_delay_ms(1);

	//e w górę
	LCD_PORT |= (1 << E);

	LCD_PORT= (LCD_PORT&0x0F) | (data << 4);
	_delay_ms(1);

	//e w górę
	LCD_PORT  &= ~(1 << E);
	_delay_ms(1);
}

void lcd_write_data(uint8_t data){
	//rs do 1
	LCD_PORT |= (1 << RS);
	//e w górę
	LCD_PORT |= (1 << E);

	LCD_PORT = (LCD_PORT&0x0F)|(data&0xF0);
	_delay_ms(1);

	//e do zera
	LCD_PORT &= ~(1 << E);

	_delay_ms(1);

	//e w górę
	LCD_PORT |= (1 << E);

	LCD_PORT= (LCD_PORT&0x0F) | (data << 4);
	_delay_ms(1);

	//e w górę
	LCD_PORT  &= ~(1 << E);
	_delay_ms(1);
}

void lcd_set_xy(uint8_t x, uint8_t y){
	 lcd_write_instr(0x80 + x + y*0x40);
}

void lcd_write_text_xy(uint8_t x, uint8_t y, char *text){
	lcd_set_xy(x,y);
	while(*text){
		lcd_write_data(*text);
		text++;
	}
}

void lcd_clear(void){
	 lcd_write_instr(1);
}

int lcd_putchar(char c, FILE *stream){
	lcd_write_data(c);
	return 0;
}
