#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void main (void) {
    //ledBlink();

    uart_init();

    while(1){
        //uart_putchar('a');
        //char *string = "hallo där\n";
        //uart_putstr(string);
        uart_putstr("hej där");
        _delay_ms(500);
    }
}
