#include "uart.h"

/* Buffer will send using UART */
unsigned char buffer[100] = "Learn-in-depth:< Mohamed Magdy >";

void main(void)
{
	/* Transmitting buffer using VersatilePB Board */
	UART_Send_String(buffer);
}
