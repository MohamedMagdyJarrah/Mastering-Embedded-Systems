/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    USART			******************/
/*****************************************************************/
/*****************************************************************/
#include "USART_interface.h"

/**************************************** Global Variables *****************************************/
USART_Config_t* Global_USART_Configuration[3];

/**************************************** Private Functions *****************************************/
uint8_t USART_INDEX(USART_t* USARTx)
{
	if(USARTx == USART1)
	{
		return 0;
	}
	else if(USARTx == USART2)
	{
		return 1;
	}
	else if(USARTx == USART3)
	{
		return 2;
	}
	return 0;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_Init
 * @Brief		:	Initialize USART Peripheral with user configuration
 * @Param[in]  	:	USARTx: Pointer to the chosen USART in the MCU
 * @Param[in]  	:	USART_Config: pointer to the configurations set by the user
 * @RetVal		:	None
 * @Note		:	This API only work for polling and asynchronous mode now
 *========================================================================================================*/
void MCAL_USART_Init(USART_t* USARTx,USART_Config_t* USART_Config)
{
	uint32_t PCLK , BRR;
	Global_USART_Configuration[USART_INDEX(USARTx)] = USART_Config;

	/* Enable USART Peripheral */
	SET_BIT(USARTx->CR1,13);

	/* Enable the clock for the chosen USART */
	if(USARTx == USART1)
	{
		RCC_USART1_EN();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_EN();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_EN();
	}

	/* Set USART mode */
	USARTx->CR1 |= USART_Config->USART_MODE;

	/* Set the length of data */
	USARTx->CR1 |= USART_Config->PacketLength;

	/* Set Parity bit */
	USARTx->CR1 |= USART_Config->ParityBit;

	/* Choose number of Stop bits */
	USARTx->CR2 |= USART_Config->StopBits;

	/* Configure the hardware flow control */
	USARTx->CR3 |= USART_Config->HwFlowCtrl;


	/* Configuring the baudrate of the USART */
	if(USARTx == USART1)
	{
		PCLK = MCAL_RCC_GetPCLK2();
	}
	else if(USARTx == USART2)
	{
		PCLK = MCAL_RCC_GetPCLK1();
	}
	else if(USARTx == USART3)
	{
		PCLK = MCAL_RCC_GetPCLK1();
	}

	BRR = USART_BRR_REGISTER(PCLK,USART_Config->Baudrate);
	USARTx->BRR = BRR;

	/* Configure the IRQ of the USART */
	if(USART_Config->IRQ_EN != USART_IRQ_DISABLE)
	{
		/* Configure the chosen IRQ */
		USARTx->CR1 |= USART_Config->IRQ_EN;
		/* Enable NVIC interrupt */
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_ENABLE;
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_ENABLE;
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_ENABLE;
		}
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_DeInit
 * @Brief		:	De-Initialize USART Peripheral using RCC
 * @Param[in]  	:	USARTx: Pointer to the chosen USART in the MCU
 * @RetVal		:	None
 * @Note		:	None
 *========================================================================================================*/
void MCAL_USART_DeInit(USART_t* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_DISABLE;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE;
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_DataTrasmit
 * @Brief		:	Transmit the data by the chosen USART
 * @Param[in]  	:	USARTx: Pointer to the chosen USART in the MCU
 * @Param[in]  	:	Data: the data transmitted by the user
 * @Param[in]  	:	TransmissionMechanism: data type refer to the polling mechanism is used or not
 * @RetVal		:	None
 * @Note		:	None
 *========================================================================================================*/
void MCAL_USART_DataTrasmit(USART_t* USARTx, uint16_t Data, PollingMechanism_t TransmissionMechanism)
{
	/* Check first the transmit buffer is empty or not */
	if(TransmissionMechanism == Polling_Enable)
	{
		while(GET_BIT(USARTx->SR,7) == 0);
	}

	/* Check the length of data will transmit (if the parity is enabled the MSB will be replaced by hardware) */
	if(Global_USART_Configuration[USART_INDEX(USARTx)]->PacketLength == USART_DATA_LENGTH_8BITS)
	{
		USARTx->DR = (Data & 0xFF);
	}
	else if(Global_USART_Configuration[USART_INDEX(USARTx)]->PacketLength == USART_DATA_LENGTH_9BITS)
	{
		USARTx->DR = (Data & 0x1FF);
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_DataReceive
 * @Brief		:	Receive the data by the chosen USART
 * @Param[in]  	:	USARTx: Pointer to the chosen USART in the MCU
 * @Param[in]  	:	Data: the data received by the user
 * @Param[in]  	:	TransmissionMechanism: data type refer to the polling mechanism is used or not
 * @RetVal		:	None
 * @Note		:	None
 *========================================================================================================*/
void MCAL_USART_DataReceive(USART_t* USARTx, uint16_t* Data, PollingMechanism_t TransmissionMechanism)
{
	/* Check first the received buffer is ready or not */
	if(TransmissionMechanism == Polling_Enable)
	{
		while(GET_BIT(USARTx->SR,5) == 0);
	}

	if(Global_USART_Configuration[USART_INDEX(USARTx)]->ParityBit == USART_PARITY_DISABLE)
	{
		if(Global_USART_Configuration[USART_INDEX(USARTx)]->PacketLength == USART_DATA_LENGTH_8BITS)
		{
			*Data = (USARTx->DR & 0xFF);
		}
		else if(Global_USART_Configuration[USART_INDEX(USARTx)]->PacketLength == USART_DATA_LENGTH_9BITS)
		{
			*Data = (USARTx->DR & 0x1FF);
		}
	}
	else
	{
		if(Global_USART_Configuration[USART_INDEX(USARTx)]->PacketLength == USART_DATA_LENGTH_8BITS)
		{
			*Data = (USARTx->DR & 0x7F);
		}
		else if(Global_USART_Configuration[USART_INDEX(USARTx)]->PacketLength == USART_DATA_LENGTH_9BITS)
		{
			*Data = (USARTx->DR & 0xFF);
		}
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_SetGpioPins
 * @Brief		:	Set the GPIO of the chosen USART
 * @Param[in]  	:	USARTx: Pointer to the chosen USART in the MCU
 * @RetVal		:	None
 * @Note		:	Should enable the clock of AFIO and GPIO of the corresponding bits after MCAL_USART_Init()
 *========================================================================================================*/
void MCAL_USART_SetGpioPins(USART_t* USARTx)
{
	if(USARTx == USART1)
	{
		// PA9 TX
		// PA10 RX
		// PA11 CTS
		// PA12 RTS
		MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_9,	 GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ); // TX
		MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_10, GPIO_PIN_MODE_ALTERNATE_INPUT);			// RX

		/* Configure CTS */
		if(Global_USART_Configuration[0]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS || Global_USART_Configuration[0]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS_RTS)
		{
			MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_11, GPIO_PIN_MODE_INPUT_FLOATING);
		}

		/* Configure RTS */
		if(Global_USART_Configuration[0]->HwFlowCtrl == USART_HW_FLW_CTRL_RTS || Global_USART_Configuration[0]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS_RTS)
		{
			MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_12, GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ);
		}
	}
	else if(USARTx == USART2)
	{
		// PA2 TX
		// PA3 RX
		// PA0 CTS
		// PA1 RTS
		MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_2,	 GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ); // TX
		MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_3, GPIO_PIN_MODE_ALTERNATE_INPUT);				// RX

		/* Configure CTS */
		if(Global_USART_Configuration[1]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS || Global_USART_Configuration[1]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS_RTS)
		{
			MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_0, GPIO_PIN_MODE_INPUT_FLOATING);
		}

		/* Configure RTS */
		if(Global_USART_Configuration[1]->HwFlowCtrl == USART_HW_FLW_CTRL_RTS || Global_USART_Configuration[1]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS_RTS)
		{
			MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_1, GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ);
		}
	}
	else if(USARTx == USART3)
	{
		// PB10 TX
		// PB11 RX
		// PB13 CTS
		// PA14 RTS
		MCAL_GPIO_SetPinMode(GPIOB, GPIO_PIN_10, GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ); // TX
		MCAL_GPIO_SetPinMode(GPIOB, GPIO_PIN_11, GPIO_PIN_MODE_ALTERNATE_INPUT);			// RX

		/* Configure CTS */
		if(Global_USART_Configuration[2]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS || Global_USART_Configuration[2]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS_RTS)
		{
			MCAL_GPIO_SetPinMode(GPIOB, GPIO_PIN_13, GPIO_PIN_MODE_INPUT_FLOATING);
		}

		/* Configure RTS */
		if(Global_USART_Configuration[2]->HwFlowCtrl == USART_HW_FLW_CTRL_RTS || Global_USART_Configuration[2]->HwFlowCtrl == USART_HW_FLW_CTRL_CTS_RTS)
		{
			MCAL_GPIO_SetPinMode(GPIOA, GPIO_PIN_14, GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ);
		}
	}
}

/******************************************************************************
 * 								ISR Functions
 * ****************************************************************************/
void USART1_IRQHandler(void)
{
	Global_USART_Configuration[0]->P_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	Global_USART_Configuration[1]->P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Global_USART_Configuration[2]->P_IRQ_CallBack();
}
