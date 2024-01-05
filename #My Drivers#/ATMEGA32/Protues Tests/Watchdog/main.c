#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "MCAL/SPI Driver/SPI_interface.h"
#include "MCAL/TWI Driver/TWI_interface.h"
#include "MCAL/Watchdog Driver/Watchdog_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#include "HAL/MAX7221 Driver/MAX7221_interface.h"

#include <util/delay.h>
#define F_CPU		8000000UL

int main(void)
{
	/* Set the direction for the led */
	MCAL_DIO_SetPinDirection(DIO_PORTC,DIO_PIN0,DIO_PIN_OUTPUT);
	_delay_ms(500);


	while(1)
	{
		MCAL_WATCHDOG_Enable();
		MCAL_DIO_SetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_HIGH);
		_delay_ms(2000);
		MCAL_WATCHDOG_Disable();
	}
	return 0;
}


