#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "MCAL/SPI Driver/SPI_interface.h"
#include "MCAL/TWI Driver/TWI_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#include "HAL/MAX7221 Driver/MAX7221_interface.h"

#include <util/delay.h>

int main(void)
{
	uint8 dataReceived;
	/* Configure 7-segment pins as output */
	MCAL_DIO_SetPortDirection(DIO_PORTA,DIO_PORT_OUTPUT);

	/* Initialize the TWI */
	MCAL_TWI_SlaveInit(0b1101000);

	while(1)
	{
		MCAL_TWI_ReceiveSlaveAddressWithWrite();
		MCAL_TWI_SlaveReceiveByte(&dataReceived);
		MCAL_DIO_SetPortValue(DIO_PORTA,dataReceived);
	}
	return 0;
}


