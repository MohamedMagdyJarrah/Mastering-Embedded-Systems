/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    USART			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef INC_STM32F103X6_USART_H_
#define INC_STM32F103X6_USART_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/STM32F103x6_MemMap.h"
#include "../RCC Driver/RCC_interface.h"
#include "../GPIO Driver/GPIO_interface.h"

/*******************************************  Type definitions *****************************************/
typedef struct
{
	/* Specifies the USART is configured as Transmitter or Receiver */
	/* This parameter must be based on @ref USART_MODE_define */
	uint8_t USART_MODE;

	/* Specifies the USART Baudrate */
	/* This parameter must be based on @ref USART_BAUDRATE_define */
	uint32_t Baudrate;

	/* Specifies the data length transmitted or received by USART */
	/* This parameter must be based on @ref USART_DATA_LENGTH_define */
	uint8_t PacketLength;

	/* Specifies the USART Parity bit */
	/* This parameter must be based on @ref USART_PARITY_define */
	uint8_t ParityBit;

	/* Specifies the USART Stop bits */
	/* This parameter must be based on @ref USART_STOP_BITS_define */
	uint8_t StopBits;

	/* Specifies the USART is configured with hardware flow control bits or not */
	/* This parameter must be based on @ref USART_HW_FLW_CTRL_define */
	uint8_t HwFlowCtrl;

	/* Specifies the USART IRQ Handler used */
	/* This parameter must be based on @ref USART_IRQ_define */
	uint8_t IRQ_EN;

	/* Specifies the USART call back function called once IRQ is happen */
	void	(*P_IRQ_CallBack)(void);

}USART_Config_t;

/* Enum to define the polling mechanism used */
typedef enum
{
	Polling_Enable,
	Polling_Disable
}PollingMechanism_t;


//	@ref USART_MODE_define
#define USART_MODE_TX						(uint32_t)(1<<3)
#define USART_MODE_RX						(uint32_t)(1<<2)
#define USART_MODE_TX_RX					(uint32_t)((1<<3) | (1<<2))

//	@ref USART_BAUDRATE_define
#define USART_BAUDRATE_2400					2400
#define USART_BAUDRATE_9600					9600
#define USART_BAUDRATE_19200				19200
#define USART_BAUDRATE_57600				57600
#define USART_BAUDRATE_115200				115200
#define USART_BAUDRATE_230400				230400
#define USART_BAUDRATE_460800				460800
#define USART_BAUDRATE_921600				921600
#define USART_BAUDRATE_2250000				2250000
#define USART_BAUDRATE_4500000				4500000

//	@ref USART_DATA_LENGTH_define
#define USART_DATA_LENGTH_8BITS				(uint32_t)(0<<12)
#define USART_DATA_LENGTH_9BITS				(uint32_t)(1<<12)

// @ref USART_PARITY_define
#define USART_PARITY_DISABLE				(uint32_t)(0<<10)
#define USART_PARITY_EVEN					(uint32_t)(1<<10)
#define USART_PARITY_ODD					(uint32_t)((1<<10) | (1<<9))

//	@ref USART_STOP_BITS_define
#define USART_STOP_BITS_1BIT				(uint32_t)(0<<12)
#define USART_STOP_BITS_0_5BIT				(uint32_t)(1<<12)
#define USART_STOP_BITS_2BIT				(uint32_t)(2<<12)
#define USART_STOP_BITS_1_5BIT				(uint32_t)(3<<12)

//	@ref USART_HW_FLW_CTRL_define
#define USART_HW_FLW_CTRL_DISABLE			(uint32_t)((0b00)<<8)
#define USART_HW_FLW_CTRL_RTS				(uint32_t)(1<<8)
#define USART_HW_FLW_CTRL_CTS				(uint32_t)(1<<9)
#define USART_HW_FLW_CTRL_CTS_RTS			(uint32_t)((0b11)<<8)

// @ref USART_IRQ_define
#define USART_IRQ_DISABLE					(uint32_t)(0)
#define USART_IRQ_TRANSMIT_DATA_EMPTY		(uint32_t)(1<<7)
#define USART_IRQ_TRANSMISSION_COMPLETE		(uint32_t)(1<<6)
#define USART_IRQ_RECEIVED_DATA_READY		(uint32_t)(1<<5)

/*===============================================================================================
  								APIs supported by "MCAL USART Driver"
 *===============================================================================================*/
/* Initialization and De-initialization of the USART */
void MCAL_USART_Init(USART_t* USARTx,USART_Config_t* USART_Config);
void MCAL_USART_DeInit(USART_t* USARTx);

/* APIs to send and receive message */
void MCAL_USART_DataTrasmit(USART_t* USARTx, uint16_t Data, PollingMechanism_t TransmissionMechanism);
void MCAL_USART_DataReceive(USART_t* USARTx, uint16_t* Data, PollingMechanism_t TransmissionMechanism);

/* Set GPIO for USART Pins */
void MCAL_USART_SetGpioPins(USART_t* USARTx);

#endif /* INC_STM32F103X6_USART_H_ */
