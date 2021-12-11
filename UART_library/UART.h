/**
 * @file UART.c
 * @author JZimnol
 * @brief UART header file, contains basic definitions and declarations
 */

#ifndef UART_H_
#define UART_H_

/************************************|***********************************\
                                DEFINITIONS
\************************************|***********************************/

/** F_CPU used for generating baud rate */
#ifndef F_CPU
    #warning "F_CPU undefined, has been set to 8 MHz"
    #define F_CPU 8000000U
#endif

/** size of a buffer, can be changed for diffrent purposes */
#define BUFF_SIZE 20

/************************************|***********************************\
                              ENUMS AND STRUCTS 
\************************************|***********************************/

/**
 * @brief enum used for setting UART Baud Rate
 */
typedef enum {
    BAUD_2400  = (uint16_t)2400,
    BAUD_4800  = (uint16_t)4800,
    BAUD_9600  = (uint16_t)9600,
    BAUD_14k4  = (uint16_t)14400,
    BAUD_19k2  = (uint16_t)19200,
    BAUD_28k8  = (uint16_t)28800,
    BAUD_38k4  = (uint16_t)38400,
    BAUD_57k6  = (uint16_t)57600,
    BAUD_76k8  = (uint32_t)76800,
    BAUD_115k2 = (uint32_t)115200,
    BAUD_230k4 = (uint32_t)230400
} BaudRate;

/**
 * @brief enum used for setting UART Mode (RX, TX, RX and TX)
 */
typedef enum {
    TX    = (uint8_t)1,
    RX    = (uint8_t)2,
    RX_TX = (uint8_t)3
} Mode;

/**
 * @brief enum used for setting UART frame length
 */
typedef enum {
    BIT_5 = (uint8_t)0,
    BIT_6 = (uint8_t)1,
    BIT_7 = (uint8_t)2,
    BIT_8 = (uint8_t)3 
} DataLength;

/**
 * @brief enum used for setting number of parity bits in UART frame
 */
typedef enum {
    NO_PARITY   = (uint8_t)0,
    EVEN_PARITY = (uint8_t)2,
    ODD_PARITY  = (uint8_t)3
} ParityBits;

/**
 * @brief enum used for setting number of stop bits in UART frame
 */
typedef enum {
    STOP_1 = (uint8_t)0,
    STOP_2 = (uint8_t)1
} StopBits;

/************************************|***********************************\
                                 VARIABLES 
\************************************|***********************************/
/** RX buffer used to collect data from PC */
volatile char UART_RxBuf[BUFF_SIZE];

/** this flag is set to 1 when PC command is bigger than BUFF_SIZE */
volatile uint8_t bufferFullFlag;

/** this flag is set when PC sends full command; will be deprecated in
    function and interrupt driven program */
volatile uint8_t sendCommandFlag;

/************************************|***********************************\
                                 FUNCTIONS
\************************************|***********************************/

/** UART initialization */
void UART_Init(BaudRate baud, Mode mode, DataLength length, 
               ParityBits par, StopBits stop);

/** enable RX interrupts */
void UART_EnableRxINT();
/** enable TX interrupts */
void UART_EnableTxINT();
/** enable Udre unterrupts */
void UART_EnableUdreINT();

/** send 1 byte using UART */
void UART_SendByte(uint8_t data);
/** send new line character */
void UART_SendNewLine();
/** send string through UART */
void UART_SendString(const char *msg);

#endif /* UART_H_ */