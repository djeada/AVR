/*
 * longdelay.c

 *
 *  Created on: 27-02-2019
 *      Author: Adam Djellouli
 */
#include "longdelay.h"

void longdelay(uint16_t time){

	for (int i=0 ; i < time; i++){
		_delay_ms(1);
	}
}

