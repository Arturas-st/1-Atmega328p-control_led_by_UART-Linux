#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h> 
#include <stdio.h>
#include <string.h>
#include "serial.h"

#define BAUD 38400
#define FOSC 16000000
#define UBBR (FOSC/(16*BAUD) - 1)
//#define UBBR FOSC/16/BAUD-1
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
    UCSR0C &= ~(1 << USBS0);
}

void uart_putchar(char chr){
    // Wait for empty transmit buffer
    while(!(UCSR0A & (1 << UDRE0))){ };
    //loop_until_bit_is_set(UCSR0A, UDRE0);
    //Put data into buffer, sends the data
    UDR0 = chr;

    /*if(chr == '\n'){
        uart_putchar('\r');
    }*/

    if(chr == '\r'){
        uart_putchar('\n');
    }

}

void uart_putstr(const char *str){
    for(int i = 0; str[i] != '\0'; i++){
        uart_putchar(str[i]);
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
    char chr = uart_getchar();
    _delay_ms(500);
    uart_putchar(chr); 

    //uart_putchar(uart_getchar());
}

void ledOnOffUart(void){
    char input[7];
    int counter = 0;
    char chr;

    while((chr = uart_getchar()) != '\r'){ //Loops over the incoming characters as long as it is not carriage return character is entered when pressing enter
        uart_putchar(chr);
        input[counter] = chr;
        counter++;
    }
    uart_putchar('\r'); //sends \r to start from the beginning of the line

    //Adds \r and \n to the string
    input[counter] = '\r'; 
    input[counter + 1] = '\n';
    input[counter + 2] = '\0'; //zero-terminates to be able to use strcmp ().

    //lights lamp if the string is equal to "ON\r\n"
    if(strncmp(input, "on\r\n", 4) == 0){ //write "off" in our rgb led case to turn on lamp
        PORTB |= (1 << PORTB1);   
           
    }
    //turns off light if the string is equal to "OFF\r\n"
    else if(strncmp(input, "off\r\n", 5) == 0){
        PORTB &= ~(1 << PORTB1); //write "on" in our rgb led case to turn off lamp
    
    }
}


