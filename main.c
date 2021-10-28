#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 
#include <stdbool.h>
#include "serial.h"
#include "blink.h"

int main (void) {
    
    uart_init();
    DDRB |= (1 << DDB1);
    while(1){
        //ledBlink();
        //uart_putchar('a');
        //uart_putstr("Arturas Stanis\n");
        //uart_getchar();
        //uart_echo();
        
        ledOnOffUart();
    }
    return 0;
}
