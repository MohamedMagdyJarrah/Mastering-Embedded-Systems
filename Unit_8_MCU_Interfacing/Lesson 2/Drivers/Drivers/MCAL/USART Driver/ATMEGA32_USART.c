#include "ATMEGA32_USART.h"

/*========================================================================================================
 * @Fun			:	MCAL_USART_voidInit
 * @Brief		:	Initialize USART according to the specified parameter in PinConfig
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_USART_voidInit(void)
{
	uint8_t Local_u8UCSRC=0b10000000;
	/* Configuring the mode of the USART and The Baud rate if it is in Asynchronous mode */
	#if USART_MODE == USART_MODE_ASYNCHRONOUS
	CLR_BIT(Local_u8UCSRC,UCSRC_UMSEL);
	UBRRL = USART_BAUDRATE;
	#elif USART_MODE == USART_MODE_SYNCHRONOUS
	SET_BIT(Local_u8UCSRC,UCSRC_UMSEL);
	#endif
	
	/* Configuring the Data length */
	Local_u8UCSRC |= (USART_DATALENGTH<<1);
	
	/* Configuring the parity bits of the frame */
	Local_u8UCSRC |= (USART_PARITY<<4);
	
	/* Configuring the stop bits of the frame */
	Local_u8UCSRC |= (USART_STOPBITS<<3);
	
	UCSRC = Local_u8UCSRC;
	/* Enable Transmitter and Receiver */
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_SendCharSynch
 * @Brief		:	Sending the data with synchronous (Polling) mode
 * @param		:   The frame of data will be send
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_USART_SendCharSynch(uint8_t Copy_u8Data)
{
	while (!GET_BIT(UCSRA,UCSRA_UDRE));
	UDR = Copy_u8Data;
}

/*========================================================================================================
 * @Fun			:	USART_SendStringSynch
 * @Brief		:	Sending the data with synchronous (Polling) mode
 * @param		:   The string of data will be send
 * @RetVal		:	None
 *========================================================================================================*/
void USART_SendStringSynch(const char* Copy_charString)
{
	uint8_t i = 0;
	while (Copy_charString[i] != '\0')
	{
		MCAL_USART_SendCharSynch(Copy_charString[i]);
		i++;
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_RecieveCharSynch
 * @Brief		:	Receiving the data with synchronous (Polling) mode
 * @RetVal		:	None
 *========================================================================================================*/
uint8_t MCAL_USART_RecieveCharSynch(void)
{
	while (!GET_BIT(UCSRA,UCSRA_RXC));
	return UDR;
}

/*========================================================================================================
 * @Fun			:	USART_SendStringSynch
 * @Brief		:	Sending the data with synchronous (Polling) mode
 * @param		:   The buffer of data will be received
  * @param		:   The size of the buffer
 * @RetVal		:	None
 *========================================================================================================*/
void USART_RecieveBufferSynch(uint8_t* Copy_pu8Buffer,uint8_t Copy_u8BufferSize)
{
	uint8_t i=0;
	for(i=0 ; i< Copy_u8BufferSize ;i++)
	{
		Copy_pu8Buffer[i] = MCAL_USART_RecieveCharSynch();
	}
	Copy_pu8Buffer[i] = '\0';
}
