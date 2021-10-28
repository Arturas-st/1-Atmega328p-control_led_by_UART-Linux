#include <avr/io.h>
#include <util/delay.h>
#include "blink.h"

void ledBlink(){
    
    DDRB |= (1 << DDB3); // set pin as output
    //0B001000 - PORTB3 (digital pin 11)
    while(1){
        PORTB |= (1 << PORTB3); // turn led on
        _delay_ms(500);
        PORTB &= ~(1 << PORTB3); // turn led off
        _delay_ms(500);
    }
}



