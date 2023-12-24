#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"

#define F_CPU			8000000UL
#include <util/delay.h>


int main(void)
{
	uint8 pressedKey = KPD_NOT_PRESSED_KEY;
	LCD_Init();
	KPD_Init();

	while(1)
	{
		pressedKey = KPD_GetPressedKey();

		if(pressedKey != KPD_NOT_PRESSED_KEY)
		{
			LCD_SendChar(pressedKey);
		}
		else
		{
			/* Do Nothing */
		}
	}

}


