#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

ISR(TIMER1_OVF_vect) {
  PORTC ^= (1 << PC2);
  TCNT1 = 700000;
}

int main(void) {

  // set PC2 as output
  DDRC |= 1 << PC2;

  TCNT1 = 700000;
  TCCR1A = 0;

  // Timer mode with 1024 prescler
  TCCR1B = (1 << CS10) | (1 << CS12);
  ;

  // Enable timer1 overflow interrupt(TOIE1)
  TIMSK = (1 << TOIE1);

  // enables interrupts
  sei();

  while (1) {
  }

  return 0;
}
