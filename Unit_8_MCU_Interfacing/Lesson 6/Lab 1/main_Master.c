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
	uint8 i =0;
	/* Initialize the TWI */
	MCAL_TWI_MasterInit(0);

	while(1)
	{
		_delay_ms(500);
		MCAL_TWI_SendStartCondition();
		MCAL_TWI_SendSlaveAddressWithWrite(0b1101000);
		MCAL_TWI_MasterWriteDataByte(i++);
		MCAL_TWI_SendStopCondition();
	}
	return 0;
}


