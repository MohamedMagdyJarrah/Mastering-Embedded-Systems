#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "LIB/STM32F103x6_MemMap.h"
#include "MCAL/GPIO Driver/GPIO_interface.h"
#include "MCAL/EXTI Driver/EXTI_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"

#define F_CPU				8000000UL

unsigned char ch;

void clock_init(void)
{
	RCC_GPIOA_EN();
	RCC_AFIO_EN();
}

void UART_NotifiFunc(void)
{
	MCAL_USART_DataReceive(USART1, &ch, Polling_Disable);
	MCAL_USART_DataTrasmit(USART1, ch, Polling_Enable);
}



int main(void)
{
	USART_Config_t usartCFG;

	/*
//	For Polling Mechanism
	usartCFG.Baudrate = USART_BAUDRATE_115200;
	usartCFG.HwFlowCtrl = USART_HW_FLW_CTRL_DISABLE;
	usartCFG.IRQ_EN = USART_IRQ_DISABLE;
	usartCFG.P_IRQ_CallBack = NULL;
	usartCFG.PacketLength = USART_DATA_LENGTH_8BITS;
	usartCFG.ParityBit = USART_PARITY_DISABLE;
	usartCFG.StopBits = USART_STOP_BITS_1BIT;
	usartCFG.USART_MODE = USART_MODE_TX_RX;
	 */

	// For Interrupt Mechanism
	usartCFG.Baudrate = USART_BAUDRATE_115200;
	usartCFG.HwFlowCtrl = USART_HW_FLW_CTRL_DISABLE;
	usartCFG.IRQ_EN = USART_IRQ_RECEIVED_DATA_READY;
	usartCFG.P_IRQ_CallBack = UART_NotifiFunc;
	usartCFG.PacketLength = USART_DATA_LENGTH_8BITS;
	usartCFG.ParityBit = USART_PARITY_DISABLE;
	usartCFG.StopBits = USART_STOP_BITS_1BIT;
	usartCFG.USART_MODE = USART_MODE_TX_RX;

	clock_init();
	MCAL_USART_Init(USART1, &usartCFG);
	MCAL_USART_SetGpioPins(USART1);

	while(1)
	{
		//		MCAL_USART_DataReceive(USART1, &ch, Polling_Enable);
		//		MCAL_USART_DataTrasmit(USART1, ch, Polling_Enable);
	}
}
