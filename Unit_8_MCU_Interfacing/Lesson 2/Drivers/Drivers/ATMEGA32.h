#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/*********************************************** Includes **********************************************/
#include "LIB/Utils.h"
#include <stdint.h>

/************************************** Peripherals Addresses *************************************/
/********************************************************
					GPIO Registers
*********************************************************/
#define PORTA					*((volatile uint8_t*)0x3B)
#define DDRA					*((volatile uint8_t*)0x3A)
#define PINA					*((volatile uint8_t*)0x39)
#define PORTB					*((volatile uint8_t*)0x38)
#define DDRB					*((volatile uint8_t*)0x37)
#define PINB					*((volatile uint8_t*)0x36)
#define PORTC					*((volatile uint8_t*)0x35)
#define DDRC					*((volatile uint8_t*)0x34)
#define PINC					*((volatile uint8_t*)0x33)
#define PORTD					*((volatile uint8_t*)0x32)
#define DDRD					*((volatile uint8_t*)0x31)
#define PIND					*((volatile uint8_t*)0x30)


/********************************************************
					USART Registers
*********************************************************/
#define UDR				*((volatile uint8_t*)0x2C)

#define UCSRA			*((volatile uint8_t*)0x2B)
#define UCSRA_RXC		7
#define UCSRA_TXC		6
#define UCSRA_UDRE		5

#define UCSRB			*((volatile uint8_t*)0x2A)
#define UCSRB_RXCIE		7
#define UCSRB_TXCIE		6
#define UCSRB_UDRIE		5
#define UCSRB_RXEN 		4
#define UCSRB_TXEN 		3
#define UCSRB_UCSZ2		2

#define UCSRC			*((volatile uint8_t*)0x40)
#define UCSRC_URSEL		7
#define UCSRC_UMSEL		6
#define UCSRC_UPM1		5
#define UCSRC_UPM0		4
#define UCSRC_UCSZ1		2
#define UCSRC_UCSZ0		1

#define UBRRL			*((volatile uint8_t*)0x29)
#define UBRRH			*((volatile uint8_t*)0x40)	//The same register of UCSRC
/************************************** MACROS Used *************************************/
//@ref  USART_MODE_define
#define	USART_MODE_SYNCHRONOUS			0
#define	USART_MODE_ASYNCHRONOUS			1
//@ref  USART_BAUDRATE_define
#define	USART_BAUDRATE_2400				207
#define	USART_BAUDRATE_4800				103
#define	USART_BAUDRATE_9600				51
#define	USART_BAUDRATE_14400			34
#define	USART_BAUDRATE_19200			25
#define	USART_BAUDRATE_28800			16
#define	USART_BAUDRATE_38400			12
#define	USART_BAUDRATE_57600			8
#define	USART_BAUDRATE_76800			6
#define	USART_BAUDRATE_115200			3
#define	USART_BAUDRATE_230400			1
#define	USART_BAUDRATE_250000			1
//@ref USART_DATALENGTH_define
#define	USART_DATALENGTH_5BITS			0b000
#define	USART_DATALENGTH_6BITS			0b001
#define	USART_DATALENGTH_7BITS			0b010
#define	USART_DATALENGTH_8BITS			0b011
#define	USART_DATALENGTH_9BITS			0b111
// @ref USART_PARITY_define
#define USART_PARITY_DISABLED			0b00
#define USART_PARITY_EVEN				0b10
#define USART_PARITY_ODD				0b11
// @ref USART_STOPBITS_define
#define USART_STOPBITS_ONEBIT			0
#define USART_STOPBITS_TWOBITS			1

#endif /* ATMEGA32_H_ */