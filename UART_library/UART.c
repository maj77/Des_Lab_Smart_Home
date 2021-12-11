/**
 * @file UART.c
 * @author JZimnol
 * @brief source file for UART.h, contains basic functions for AVR UART
 */

 #include <avr/io.h>
 #include <string.h>
 #include <avr/pgmspace.h>
 #include "UART.h"

/**
 * @brief initialize UART
 * @param baud   -> UBRR0 value
 * @param mode   -> mode (TX, RX)
 * @param length -> frame length (5-8 bits)
 * @param par    -> number of parity bits
 * @param stop   -> number of stop bits	
 */
void UART_Init(BaudRate baud, Mode mode, DataLength length, 
               ParityBits par, StopBits stop) {

    uint8_t temp2Xflag = 0;

    /** configure UBRR0 value */
    if( baud > 38400 ) {
        temp2Xflag = 1;
        baud = F_CPU/8/baud-1;
    }
    else
        baud = F_CPU/16/baud-1;

    /** set baud rate */
    UBRR0H = (unsigned char)(baud>>8);
    UBRR0L = (unsigned char)(baud);

    /** set double transmission if needed */
    UCSR0A |= (temp2Xflag<<1);

    /** set all other options */
    UCSR0B = (mode<<3);
    UCSR0C = (length<<1) | (par<<4) | (stop<<3);
}
/**
 *	@brief enable RX interrupts
 */
void UART_EnableRxINT() {
    UCSR0B |= (1<<RXCIE0);
}
/**
 *	@brief enable TX interrupts
 */
void UART_EnableTxINT() {
    UCSR0B |= (1<<TXCIE0);
}
/**
 *	@brief enable Udre interrupts
 */
void UART_EnableUdreINT() {
    UCSR0B |= (1<<UDRIE0);
}
/** 
 * @brief send 1 byte using UART
 * @param data -> 1 byte of data 
 */
void UART_SendByte(uint8_t data) {
     while( !(UCSR0A & (1<<UDRE0)) )
        ;
     UDR0 = data;   
}
/** 
 * @brief send new line character 
 *        ('\r' --> CR - Cariage Return) 
 *        ('\n' --> LF - Line Feed) 
 *        using UART     
 */
void UART_SendNewLine() {
    UART_SendByte('\r');
    UART_SendByte('\n');    
}
/**
 * @brief send string through UART
 * @param *msg -> char* message
 */
void UART_SendString(const char *msg) {
    register char c;
    while( c = pgm_read_byte(msg++) )
        UART_SendByte(c);
}
/**
 * NOTE: Register variables tell the compiler to store the variable in 
 * CPU register instead of memory. Frequently used variables are kept in 
 * registers and they have faster accessibility.
 */
