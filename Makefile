all: build

build:
	avr-gcc -Os -mmcu=atmega328p main.c -o a.elf -DF_CPU=16000000
	avr-size --format=avr --mcu=atmega328p a.elf

flash: build
	avrdude -D -c /etc/avrdude.conf -p atmega328p -c stk500v1 -P  /dev/ttyUSB0 -b 57600 -U flash:w:a.elf:e
