#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define CONSOLE_IMPL
#include "console.h"

uint8_t input;
int main(void){
    console_init(9600);
    console_write('H');
    console_write('i');
    DDRB |= (1<<input);
	while(1){
        if(console_ready()){
            input = console_read()-'0';
            console_write(input+'0');
        }
        PORTB ^= (1<<input);
        _delay_ms(500);
    }
}
