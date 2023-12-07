#include <util/delay.h>
#include <avr/io.h>

int main(void){
	DDRB |= (1<<PB5);
	while(1){
        PORTB ^= (1<<PB5);
        _delay_ms(250);
    }
}
