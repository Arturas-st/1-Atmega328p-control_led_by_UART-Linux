#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

#define BAUD 38400
#define FOSC 16000000
#define UBBR (FOSC/(16*BAUD) - 1)

//uint16_t ubbr = FOSC/(16*BAUD) - 1;

void uart_init(void){
    //Set baud rate
    UBRR0H = (UBBR >> 8);
    UBRR0L = UBBR;
    //Enable transmitter
    UCSR0B |= (1 << TXEN0);
    //Enable receiver
    UCSR0B |= (1 << RXEN0);
    //Set frame format: 8data, 1stop bit (8N1)
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}


void uart_putchar(char chr){
    // Wait for empty transmit buffer
    while(!(UCSR0A & (1 << UDRE0))){ };
    //Put data into buffer, sends the data
    UDR0 = chr;

    if(chr == '\n'){
        uart_putchar('\r');
    }

}

void uart_putstr(const char *str){
    /*for(int i = 0; str[i] != '\0'; i++){
        uart_putchar(str[i]);
    }*/
    char chr = *str; // get character
    uart_putchar(chr); //send character
    while (chr != '\0'){
        str++;             // increment the pointer
        chr = *str;        // get next character
        uart_putchar(chr); // send next character
    }
}

char uart_getchar(void){
    // Wait for data to be received
    while(!(UCSR0A & (1 << RXC0))){ };
    // Get and return received data from buffer
    return UDR0;

}

void uart_echo(void){
    // Prints out what we enter in our terminal
    uart_putchar(uart_getchar());
    

    //char chr = uart_getchar();
    //uart_putchar(chr);
        
       
}
