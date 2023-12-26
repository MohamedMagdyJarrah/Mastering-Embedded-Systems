/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    MAX7221			******************/
/*****************************************************************/
/*****************************************************************/
#include "MAX7221_private.h"
#include "MAX7221_interface.h"


static void executeCommand(uint8 command,uint8 data)
{
	/* Initializing the packet by pulling chip select to low */
	MCAL_DIO_SetPinValue(DIO_PORTB, DIO_PIN4,DIO_PIN_LOW);

	/* Start command transmission */
	MCAL_SPI_Transcieve(command);
	/* Then transmitting data */
	MCAL_SPI_Transcieve(data);

	/* Terminate the chip select again to high */
	MCAL_DIO_SetPinValue(DIO_PORTB, DIO_PIN4,DIO_PIN_HIGH);
}


void HAL_MAX7221_Init(void)
{
	/* First decode all digits to display */
	executeCommand(Decode_Mode,0xFF);

	/* Set the Scan limit to scan all digits */
	executeCommand(Scan_Limit,0x07);

	/* Set the intensity of the display to be maximum */
	executeCommand(Intensity_Control,0x0F);

	/* Set the MAX7221 to be in the normal operation mode */
	executeCommand(Display_Control,0x01);
}

void HAL_MAX7221_DisplayDigit(uint8 digitPlace,uint8 digitValue)
{
	if(digitPlace >= 1 && digitPlace <= 8)
	{
		executeCommand(digitPlace,digitValue);
	}
	else
	{
		/* Do nothing */
	}
}
