    Date format: dd-mm-yy

Chip - Atmega328P microprocessor


# Day 1 (07-12-23)

I've got an idea to implement video transcoder for microprocessor. As someone once said "Real programming starts when memory ends". This is basically the reason why I've chosen Atmega328 instead of all other variety of microprocessors like esp, stm, arm etc.

Because of flash and ram memory limits I will need to implement every single part of this project with my bare hands (and keyboard, I guess).

With quick thought given about what steps needed to be done I've came up with this shitty TODO list:

* Data transfer bus between PC and controller
* Video decoding and encoding algorithm
* Process status visualisation of some sort will be really cool

This coding adventure is going to be really hard, interesting, depressing and challenging and hard and challenging and hard... 

With this "plan" in mind I started developing.

## Step one: Serial connection

You might think that starting from video d/e algorithm will be better. Imho this approach is much better indeed, but I'm to lasy to start from something hard, so let's get into bus connection first.

According to [this]() datasheet (TODO: provide link) USART (Universal Synchronous Asynchronous Receiver Transceiver) is already provided on chip, and because I am using arduino nano development board I, fortunately, have USART-USB connection.

What do we have:
* 2 USART instaces
* 5 to 9 data bits per serial frame
* Double Speed Asynchronous Communication Mode

Lets iterate over all:

* Chip provides us with two USART interfaces, but we've got only one core to deal with, so only one instace of interface would be used.
* I think using 8 bits per frame has most efficient ratio data over time spent, but we'll see.
* I don't really know what DSACM is about, but it sounds really cool.

Okay, time to start programming.

### Programming
First thing that should be done is USART initialisation.
I'm going to write most of my libs using stb style btw.

```c
void console_init(long baudrate){
    // set baud rate
    UBRR0 = (F_CPU / (8L * baudrate)) - 1;
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    // set frame format (8 bits 1 stop bit)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
```
Сode above uses internal clock generator and 8bit frame. Primarily I will be using 9600 baud rate for testing (9600bytes per second using 8bit frame)

```c
void console_init(long baudrate);
uint8_t console_ready();            // returns true if data is ready to be received
uint8_t console_read();             // return read byte
void console_write(uint8_t data);   // tansmits byte
```

Lets write simple serial test program:
```c
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define CONSOLE_IMPL
#include "console.h"

uint8_t pin_id;
int main(void){
    console_init(9600); // console initialisation
    console_write('H');
    console_write('i'); // greeting
    DDRB = 0xff; // set PORTB as output
	while(1){
        if(console_ready()){ // check if anything in buffer
            pin_id = console_read()-'0'; // get pin id
            console_write(pin_id+'0'); // print pin id for debugging purposes
        }
        PORTB ^= (1<<pin_id); // flip pin_id in PORTB (if pin_id==5, LED_BUILTIN is flipped)
        _delay_ms(500); // sleep
    }
}
```
That is all for today.
