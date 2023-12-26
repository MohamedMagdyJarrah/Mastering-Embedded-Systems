#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "MCAL/SPI Driver/SPI_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#include "HAL/MAX7221 Driver/MAX7221_interface.h"


#define F_CPU			8000000UL
#include <util/delay.h>

int main(void)
{
	uint8 index = 0 , counter = 0;
	MCAL_SPI_MasterInit();
	HAL_MAX7221_Init();

	while(1)
	{
		for(index=0 ; index<9  ; index++)
		{
			HAL_MAX7221_DisplayDigit(index,counter++);
			_delay_ms(1000);
		}
		for(index=0 ; index<9  ; index++)
		{
			HAL_MAX7221_DisplayDigit(index,0);
			_delay_ms(1000);
		}
		counter =0;
	}
	return 0;
}


