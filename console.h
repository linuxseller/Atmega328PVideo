#include <stdint.h>

void console_init(long baudrate);       // Initialise USART
uint8_t console_ready();                // Check if receiver is ready
unsigned char console_read_one(void);   // Read one byte (8-bits)
void console_write(unsigned char data); // Sent one byte (8-bits)

#ifdef CONSOLE_IMPL
void console_init(long baudrate){
    UBRR0 = (F_CPU / (8L * baudrate)) - 1;
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
uint8_t console_ready(){
    return UCSR0A & (1<<RXC0);
}
uint8_t console_read(void){
    //while (!(UCSR0A&(1<<RXC0)));
    return UDR0;
}
void console_write(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
#endif // CONSOLE_IMPL
