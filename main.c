#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "serial.h"
#include "blink.h"

int main (void) {
    //ledBlink();
    uart_init();
    while(1){
        //uart_putchar('a');
        //char *string = "hallo där\n";
        //uart_putstr(string);
        //uart_putstr("hej där\n");
        uart_echo();
        //_delay_ms(500);
    }
}
