#ifndef ATMEGA32_USART_H_
#define ATMEGA32_USART_H_


/*********************************************** Includes **********************************************/
#include "../../ATMEGA32.h"
#include <stdint.h>


/************************************ Macros Configuration References *********************************/
// @ref USART_MODE_define
// 1- USART_MODE_SYNCHRONOUS
// 2- USART_MODE_ASYNCHRONOUS
#define USART_MODE			USART_MODE_ASYNCHRONOUS

// @ref USART_MODE_define
// 1- USART_BAUDRATE_2400
// 2- USART_BAUDRATE_4800
// 3- USART_BAUDRATE_9600
// 4- USART_BAUDRATE_14400
// 5- USART_BAUDRATE_19200
// 6- USART_BAUDRATE_28800
// 7- USART_BAUDRATE_38400
// 8- USART_BAUDRATE_57600
// 9- USART_BAUDRATE_76800
// 10- USART_BAUDRATE_115200
// 11- USART_BAUDRATE_230400
// 12- USART_BAUDRATE_250000
#define USART_BAUDRATE		USART_BAUDRATE_9600

//@ref USART_DATALENGTH_define
// 1- USART_DATALENGTH_5BITS
// 2- USART_DATALENGTH_6BITS
// 3- USART_DATALENGTH_7BITS
// 4- USART_DATALENGTH_8BITS
// 5- USART_DATALENGTH_9BITS
#define USART_DATALENGTH	USART_DATALENGTH_8BITS


// @ref USART_PARITY_define
// 1- USART_PARITY_DISABLED
// 2- USART_PARITY_EVEN
// 3- USART_PARITY_ODD
#define USART_PARITY		USART_PARITY_DISABLED

// @ref USART_PARITY_define
// 1- USART_STOPBITS_ONEBIT
// 2- USART_STOPBITS_TWOBITS
#define USART_STOPBITS		USART_STOPBITS_ONEBIT


/*===============================================================================================
 * 								APIs supported by "MCAL USART Driver"
 *===============================================================================================*/
void MCAL_USART_voidInit(void);

void MCAL_USART_SendCharSynch(uint8_t Copy_u8Data);
void USART_SendStringSynch(const char* Copy_charString);

uint8_t MCAL_USART_RecieveCharSynch(void);
void USART_RecieveBufferSynch(uint8_t* Copy_pu8Buffer,uint8_t Copy_u8BufferSize);

#endif
