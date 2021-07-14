#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int wait_time = 150;
int brightness = 0;

void initPWM() {
  DDRB |= (1 << PB3);
  TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
}

void setPWMOutput(int duty) { OCR0 = duty; }

int main(void) {
  initPWM();

  while (1) {
    for (brightness = 0; brightness < 255; brightness++) {
      setPWMOutput(brightness);
      _delay_ms(wait_time);
    }
    for (brightness = 255; brightness > 0; brightness--) {
      setPWMOutput(brightness);
      _delay_ms(wait_time);
    }
  }
  return 0;
}
