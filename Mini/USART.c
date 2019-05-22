/* * USART.c
 *
 *  Created on: 27-03-2019
 *      Author: psm8
 */

#include "USART.h"

void USART_Init( unsigned int baud ){

	/* prędkość transmisji */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;

	/* Format ramki: słowo=8bitów, 2 bity stopu */
	UCSRC =
	(1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

	/* Włączenie odbiornika i nadajnika */
	UCSRB = (1<<RXEN)|(1<<TXEN);

	/* Włączenie przerwania, gdy przyszła dana */
	UCSRB |= (1<<RXCIE);

}


void USART_Transmit( unsigned char data ) {
	/* Czekaj, aŜ zwolni się bufor nadajnika */
	while ( !( UCSRA & (1<<UDRE)) );

	/* Umieść daną w buforze i ją wyślij */
	UDR = data;
}

unsigned char USART_Receive( void ) {

	/* Czekaj, aŜ pojawi się dana do odbioru */

	while ( !(UCSRA & (1<<RXC)) ) ;

	/* Odbierz daną */
	return UDR;
}

int USART_putchar(char c, FILE *stream){
	USART_Transmit(c);
	return(0);
}


