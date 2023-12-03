#ifndef INC_STM32F103X6_GPIO_H_
#define INC_STM32F103X6_GPIO_H_

/*********************************************** Includes **********************************************/
#include "STM32F103x6.h"

/*******************************************  Type definitions *****************************************/
typedef struct
{
	/*Specifies the GPIO pins to be configured
	 * This parameter can be a value of @ref GPIO_PIN_define */
	uint8_t GPIO_PinNumber;

	/*Specifies the GPIO pins to be configured
	 * This parameter can be a value of @ref GPIO_MODE_define */
	uint32_t GPIO_Mode;

}GPIO_PinConfig_t;

/************************************ Macros Configuration References *********************************/
// @ref GPIO_PIN_define
#define GPIO_PIN_0						((uint8_t)0)		/* Pin 0 is selected */
#define GPIO_PIN_1						((uint8_t)1)		/* Pin 1 is selected */
#define GPIO_PIN_2						((uint8_t)2)		/* Pin 2 is selected */
#define GPIO_PIN_3						((uint8_t)3)		/* Pin 3 is selected */
#define GPIO_PIN_4						((uint8_t)4)		/* Pin 4 is selected */
#define GPIO_PIN_5						((uint8_t)5)		/* Pin 5 is selected */
#define GPIO_PIN_6						((uint8_t)6)		/* Pin 6 is selected */
#define GPIO_PIN_7						((uint8_t)7)		/* Pin 7 is selected */
#define GPIO_PIN_8						((uint8_t)8)		/* Pin 8 is selected */
#define GPIO_PIN_9						((uint8_t)9)		/* Pin 9 is selected */
#define GPIO_PIN_10						((uint8_t)10)		/* Pin 10 is selected */
#define GPIO_PIN_11						((uint8_t)11)		/* Pin 11 is selected */
#define GPIO_PIN_12						((uint8_t)12)		/* Pin 12 is selected */
#define GPIO_PIN_13						((uint8_t)13)		/* Pin 13 is selected */
#define GPIO_PIN_14						((uint8_t)14)		/* Pin 14 is selected */
#define GPIO_PIN_15						((uint8_t)15)		/* Pin 15 is selected */
#define GPIO_PIN_ALL					((uint16_t)0xFF)	/* All Pins are selected */

// @ref GPIO_MODE_define
// 0: Analog mode
// 1: Floating input (reset state)
// 2: Input with pull-up
// 3: Input with pull-down
// 4: General purpose output push-pull
// 5: General purpose output Open-drain
// 6: Alternate function output Push-pull
// 7: Alternate function output Open-drain
// 8: Alternate function input
#define GPIO_MODE_ANALOG							0b0000		/* Analog mode */
#define GPIO_MODE_INPUT_FLOATING					0b0100		/* Floating input (reset state) */
#define GPIO_MODE_INPUT_PULL_UP						0b1000		/* Input with pull-up */
#define GPIO_MODE_INPUT_PULL_DOWN					0b1000		/* Input with pull-down */
#define GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ			0b0001		/* General purpose output Push-pull with speed 10 MHZ */
#define GPIO_MODE_OUTPUT_OPEN_DRAIN_10_MHZ			0b0101		/* General purpose output Open-drain with speed 10 MHZ */
#define GPIO_MODE_ALTERNATE_PUSH_PULL_10_MHZ		0b1001		/* Alternate function output Push-pull with speed 10 MHZ */
#define GPIO_MODE_ALTERNATE_OPEN_DRAIN_10_MHZ		0b1101		/* Alternate function output Open-drain with speed 10 MHZ */
#define GPIO_MODE_OUTPUT_PUSH_PULL_2_MHZ			0b0010		/* General purpose output Push-pull with speed 2 MHZ */
#define GPIO_MODE_OUTPUT_OPEN_DRAIN_2_MHZ			0b0110		/* General purpose output Open-drain with speed 2 MHZ */
#define GPIO_MODE_ALTERNATE_PUSH_PULL_2_MHZ			0b1010		/* Alternate function output Push-pull with speed 2 MHZ */
#define GPIO_MODE_ALTERNATE_OPEN_DRAIN_2_MHZ		0b1110		/* Alternate function output Open-drain with speed 2 MHZ */
#define GPIO_MODE_OUTPUT_PUSH_PULL_50_MHZ			0b0011		/* General purpose output Push-pull with speed 50 MHZ */
#define GPIO_MODE_OUTPUT_OPEN_DRAIN_50_MHZ			0b0111		/* General purpose output Open-drain with speed 50 MHZ */
#define GPIO_MODE_ALTERNATE_PUSH_PULL_50_MHZ		0b1011		/* Alternate function output Push-pull with speed 50 MHZ */
#define GPIO_MODE_ALTERNATE_OPEN_DRAIN_50_MHZ		0b1111		/* Alternate function output Open-drain with speed 50 MHZ */
#define GPIO_MODE_ALTERNATE_INPUT					0b0100		/* Alternate function input */
// for Whole Port
#define GPIO_MODE_PORT_INPUT_FLOATING				0x44444444	/* All port configured as Floating input (reset state) */
#define GPIO_MODE_PORT_INPUT_PULL_UP				0x88888888	/* All port configured as Input with pull-up */
#define GPIO_MODE_PORT_INPUT_PULL_DOWN				0x88888888	/* All port configured as Input with pull-down */
#define GPIO_MODE_PORT_OUTPUT_PUSH_PULL_10_MHZ		0x11111111	/* All port configured as output Push-pull with speed 10 MHZ */
#define GPIO_MODE_PORT_OUTPUT_OPEN_DRAIN_10_MHZ		0x55555555	/* All port configured as output Open-drain with speed 10 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_PUSH_PULL_10_MHZ	0x99999999	/* All port configured as Alternate output Push-pull with speed 10 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_OPEN_DRAIN_10_MHZ	0xDDDDDDDD	/* All port configured as Alternate output Open-drain with speed 10 MHZ */
#define GPIO_MODE_PORT_OUTPUT_PUSH_PULL_2_MHZ		0x22222222	/* All port configured as output Push-pull with speed 2 MHZ */
#define GPIO_MODE_PORT_OUTPUT_OPEN_DRAIN_2_MHZ		0x66666666	/* All port configured as output Open-drain with speed 2 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_PUSH_PULL_2_MHZ	0xAAAAAAAA	/* All port configured as Alternate output Push-pull with speed 2 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_OPEN_DRAIN_2_MHZ	0xEEEEEEEE	/* All port configured as Alternate output Open-drain with speed 2 MHZ */
#define GPIO_MODE_PORT_OUTPUT_PUSH_PULL_50_MHZ		0x33333333	/* All port configured as output Push-pull with speed 50 MHZ */
#define GPIO_MODE_PORT_OUTPUT_OPEN_DRAIN_50_MHZ		0x77777777	/* All port configured as output Open-drain with speed 50 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_PUSH_PULL_50_MHZ	0xBBBBBBBB	/* All port configured as Alternate output Push-pull with speed 50 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_OPEN_DRAIN_50_MHZ	0xFFFFFFFF	/* All port configured as Alternate output Open-drain with speed 50 MHZ */
#define GPIO_MODE_PORT_ALTERNATE_INPUT				0x44444444	/* All port configured as Alternate input */

//@ref GPIO_PINSTATE_define
#define GPIO_PINSTATE_HIGH							1
#define GPIO_PINSTATE_LOW							0

//@ref GPIO_LOCKSTATE_define
#define GPIO_LOCKSTATE_ERROR						1
#define GPIO_LOCKSTATE_NOERROR						0


/*===============================================================================================
 * 								APIs supported by "MCAL GPIO Driver"
 *===============================================================================================*/
void MCAL_GPIO_Init(GPIO_t* GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_Init_Prebuild(GPIO_t* GPIOx);
void MCAL_GPIO_DeInit(GPIO_t* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_t* GPIOx,uint8_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_t* GPIOx);

void MCAL_GPIO_WritePin(GPIO_t* GPIOx,uint8_t PinNumber, uint8_t PinValue);
void MCAL_GPIO_WritePort(GPIO_t* GPIOx,uint16_t PortValue);

void MCAL_GPIO_TogglePin(GPIO_t* GPIOx,uint8_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_t* GPIOx,uint8_t PinNumber);

#endif /* INC_STM32F103X6_GPIO_H_ */
