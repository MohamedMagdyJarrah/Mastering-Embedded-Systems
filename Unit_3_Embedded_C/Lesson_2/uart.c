#include "uart.h"

#define UART0DR		*((volatile unsigned int* const)((unsigned int*)0x101f1000))

void UART_Send_String(unsigned char* P_tx_string)
{
	/* Loop on the string until Null character */
	while(*P_tx_string != '\0')
	{
		/* load the character in the register (Transmit the char) */
		UART0DR = (unsigned int)*P_tx_string;
		/* Go to the next character */
		P_tx_string++;
	}
	
}