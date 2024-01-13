#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "MCAL/SPI Driver/SPI_interface.h"
#include "MCAL/TWI Driver/TWI_interface.h"
#include "MCAL/Watchdog Driver/Watchdog_interface.h"
#include "MCAL/Timers Driver/Timers_interface.h"
#include "MCAL/ADC Driver/ADC_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#include "HAL/MAX7221 Driver/MAX7221_interface.h"
#include "HAL/LM35 Driver/LM35_interface.h"

#include <util/delay.h>
#define F_CPU			8000000UL

void ModulesInit(void)
{
	/* Configure the LCD Pins */
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN5,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN6,DIO_PIN_OUTPUT);


	/* Configure Potentiometer Pin */
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT_FLOATING);

	MCAL_ADC_Init();
	LCD_Init();
}


int main(void)
{
	uint16 Pot_Reading = 0;
	uint8 percent = 0;
	uint8 bars = 0 , i;

	ModulesInit();


	while(1)
	{
		LCD_GoToXY(0,0);
		LCD_SendString("Percent:");
		LCD_GoToXY(0,12);
		MCAL_ADC_StartConversionSynch(ADC0,&Pot_Reading);
		percent = (Pot_Reading/1023.0) * 100;
		LCD_SendNumber(percent);
		LCD_SendChar('%');
		bars = (percent/100.0) * 15;
		LCD_GoToXY(1,0);
		for(i=0 ; i<bars ; i++)
		{
			LCD_SendChar(0xff);
		}
		_delay_ms(500);
		LCD_ClearDisplay();
	}
	return 0;
}


