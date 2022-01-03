/**
 * @file main.c
 * @brief file representing simple slave device
 */

/** define clock frequency */
#ifndef F_CPU
    #define F_CPU 8000000U
#endif

/** include header files */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "UART.h"

/** private defines */
#define LED_YELLOW 1
#define LED_RED    3
#define LED_GREEN  5
#define LED_BLUE   7
#define LED_WHITE  0

/************************************|***********************************\
                                    MAIN
\************************************|***********************************/
int main(void) {
    UART_Init(BAUD_9600, RX_TX, BIT_8, NO_PARITY, STOP_1);
    UART_EnableRxINT();
    memset( (char*)UART_RxBuf, 0, sizeof(UART_RxBuf) );

    DDRB = (1<<LED_YELLOW) | (1<<LED_RED) | (1<<LED_GREEN) | (1<<LED_BLUE) 
         | (1<<LED_WHITE);
    PORTB = 0;

    sei();

    while (1);
}

/************************************|***********************************\
                             COMMAND EXECUTION
\************************************|***********************************/
void ExecuteCommand() {
    if( sendCommandFlag ) {
		/** s<number_of_slave>_<command> */
        if( strcmp((char*)UART_RxBuf, "s1_LED_YELLOW_ON") == 0 )
            PORTB |= (1<<LED_YELLOW);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_YELLOW_OFF") == 0 ) 
            PORTB &= !(1<<LED_YELLOW);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_RED_ON") == 0 ) 
            PORTB |= (1<<LED_RED);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_RED_OFF") == 0 ) 
            PORTB &= !(1<<LED_RED);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_GREEN_ON") == 0 ) 
            PORTB |= (1<<LED_GREEN);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_GREEN_OFF") == 0 ) 
            PORTB &= !(1<<LED_GREEN);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_BLUE_ON") == 0 ) 
            PORTB |= (1<<LED_BLUE);
        else if( strcmp((char*)UART_RxBuf, "s1_LED_BLUE_OFF") == 0 ) 
            PORTB &= !(1<<LED_BLUE);
        else 
            PORTB ^= (1<<LED_WHITE);
        
        /** clear buffer */
        memset( (char*)UART_RxBuf, 0, sizeof(UART_RxBuf) );
        sendCommandFlag = 0;
    }
    if( bufferFullFlag ) {
        memset( (char*)UART_RxBuf, 0, sizeof(UART_RxBuf) );
        bufferFullFlag = 0;
    }    
}

/************************************|***********************************\
                                    ISR
\************************************|***********************************/
ISR( USART_RX_vect ) {
    char data_byte = UDR0;

    if( data_byte != '\r' ) {
        if( strlen((char*)UART_RxBuf) < BUFF_SIZE ) 
            /** save to buffer if buffer status != full */
            UART_RxBuf[strlen((char*)UART_RxBuf)] = data_byte;
    }
    else {
        if( strlen((char*)UART_RxBuf) >= BUFF_SIZE )
            bufferFullFlag = 1;
        else
            sendCommandFlag = 1;

        ExecuteCommand();
    }
}

