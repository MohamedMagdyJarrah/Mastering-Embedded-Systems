#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "MCAL/SPI Driver/SPI_interface.h"
#include "MCAL/TWI Driver/TWI_interface.h"
#include "MCAL/Watchdog Driver/Watchdog_interface.h"
#include "MCAL/Timers Driver/Timers_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#include "HAL/MAX7221 Driver/MAX7221_interface.h"

//#include <util/delay.h>
//#define F_CPU		8000000UL

void timerTest(void)
{
	MCAL_DIO_TogglePinValue(DIO_PORTB, DIO_PIN3);
}

int main(void)
{
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN3 , DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(DIO_PORTC, DIO_PIN3 , DIO_PIN_OUTPUT);
	MCAL_TIMER0_Init();
	MCAL_TIMER0_SetCompareMatchCallBack(&timerTest);

	while(1)
	{
		MCAL_TIMER0_GenerateSquareWave(0.001);
	}
	return 0;
}


