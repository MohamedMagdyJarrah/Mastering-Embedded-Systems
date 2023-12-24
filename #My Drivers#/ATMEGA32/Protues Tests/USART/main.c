#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"

#define F_CPU			8000000UL
#include <util/delay.h>

void transmitNotfi(void)
{
	LCD_GoToXY(1,15);
	LCD_SendChar('T');
}

void receiveNotfi(void)
{
	LCD_GoToXY(1,15);
	LCD_SendChar('R');
}

int main(void)
{
	uint8 receivedData = 0;
	uint8 buff[5];
	MCAL_USART_Init();
	LCD_Init();

	LCD_SendString("Welcome to USART");
	//	MCAL_USART_SendCharSynch('T');
	//	MCAL_USART_SendStringSynch("Welcome LCD");
	//	MCAL_USART_SendCharAsynch('T',&transmitNotfi);
	MCAL_USART_SendStringAsynch("Hello LCD",&transmitNotfi);

	while(1)
	{
		LCD_GoToXY(1,0);
		//		receivedData = MCAL_USART_RecievesCharSynch();
		//		MCAL_USART_RecieveBufferSynch(buff,5);
		//		LCD_SendString(buff);
		//		MCAL_USART_RecieveCharAsynch(&receivedData,&receiveNotfi);
		//		if(receivedData != 0)
		//		{
		//			LCD_SendChar(receivedData);
		//		}
		MCAL_USART_RecieveBufferAsynch(buff,5,&receiveNotfi);
		LCD_SendString(buff);

	}

}


