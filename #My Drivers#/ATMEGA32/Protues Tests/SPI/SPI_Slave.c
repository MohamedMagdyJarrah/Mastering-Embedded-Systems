#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "MCAL/SPI Driver/SPI_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"


#define F_CPU			8000000UL
#include <util/delay.h>

int main(void)
{
	uint8 data = 0;
	MCAL_DIO_SetPortDirection(DIO_PORTA,DIO_PORT_OUTPUT);
	MCAL_SPI_SlaveInit();

	while(1)
	{
		for( data=255 ; data>=0 ; data-- )
		{
			MCAL_DIO_SetPortValue(DIO_PORTA, MCAL_SPI_Transcieve(data));
		}
	}

	return 0;
}


