#include <avr/io.h>
#include <util/delay.h>

int main()
{

        DDRD |=1<<PC3;
        while(1)
        {
                PORTC &= ~(1<<PC3);
                _delay_ms(1000);
                PORTC |=(1<<PC3);
                _delay_ms(1000);
        }

	return 0;
}
