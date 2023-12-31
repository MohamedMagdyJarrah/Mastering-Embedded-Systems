/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    USART			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/ATMEGA32_MemMap.h"
#include "../DIO Driver/DIO_interface.h"

/*=============================================================================================
 * 									Pre-Build Configuration
 *=============================================================================================*/
/*Timeout of sending data*/
#define USART_TIMEOUT					50000

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


/*=======================================================================================
 * 						APIs supported by "MCAL USART Driver"
 *=======================================================================================*/
void MCAL_USART_Init(void);

uint8 MCAL_USART_SendCharSynch(uint8 Data);
uint8 MCAL_USART_SendCharAsynch(uint8* Data,void(*NotificationFunc)(void));

uint8 MCAL_USART_RecievesCharSynch(void);
uint8 MCAL_USART_RecieveCharAsynch(uint8* RecievedData,void(*NotificationFunc)(void));

uint8 MCAL_USART_SendStringSynch(const char* String);
uint8 MCAL_USART_SendStringAsynch(char* String,void(*NotificationFunc)(void));

uint8 MCAL_USART_RecieveBufferSynch(uint8* Buffer,uint8 BufferSize);
uint8 MCAL_USART_RecieveBufferAsynch(uint8* Buffer,uint8 BufferSize,void(*NotificationFunc)(void));

#endif
