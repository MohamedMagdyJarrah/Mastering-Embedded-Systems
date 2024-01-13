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


	/* Configure LM35 Pin */
	MCAL_DIO_SetPinDirection(DIO_PORTA,DIO_PIN7,DIO_PIN_INPUT_FLOATING);

	MCAL_ADC_Init();
	LCD_Init();
}


int main(void)
{
	LM35_t TempSensor = LM35_ADC7_RESOLUTION_10_BIT;
	uint16 TemperatureReading = 0;

	ModulesInit();


	while(1)
	{
		LCD_GoToXY(0,0);
		LCD_SendString("Temperature:");
		LCD_GoToXY(1,2);
		TemperatureReading = HAL_LM35_GetTemperature(&TempSensor);
		LCD_SendNumber(TemperatureReading);
		_delay_ms(500);
	}
	return 0;
}


