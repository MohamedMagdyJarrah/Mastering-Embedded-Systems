#ifndef ATMEGA32_GPIO_H_
#define ATMEGA32_GPIO_H_

/*********************************************** Includes **********************************************/
#include "../../ATMEGA32.h"
#include <stdint.h>

typedef struct
{
	/*Specifies the GPIO pins to be configured
	 * This parameter can be a value of @ref GPIO_PIN_define */
	uint8_t GPIO_PinNumber;
	
	/*Specifies the GPIO pins to be configured
	 * This parameter can be a value of @ref GPIO_MODE_define */
	uint8_t GPIO_Mode;
	
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

// @ref GPIO_MODE_define
#define GPIO_MODE_OUTPUT				0
#define GPIO_MODE_INPUT_FLOATING		1
#define GPIO_MODE_INPUT_PULL_UP			2

// @ref GPIO_PINSTATE_define
#define GPIO_PINSTATE_HIGH				1
#define GPIO_PINSTATE_LOW				0

// @ref GPIOx
#define	GPIOA							0
#define	GPIOB							1
#define	GPIOC							2
#define	GPIOD							3

/*===============================================================================================
 * 								APIs supported by "MCAL GPIO Driver"
 *===============================================================================================*/
void MCAL_GPIO_Init(uint8_t GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_PortInit(uint8_t GPIOx,uint8_t GPIO_MODE);
void MCAL_GPIO_DeInit(uint8_t GPIOx);

uint8_t MCAL_GPIO_ReadPin(uint8_t GPIOx,uint8_t PinNumber);
uint8_t MCAL_GPIO_ReadPort(uint8_t GPIOx);

void MCAL_GPIO_WritePin(uint8_t GPIOx,uint8_t PinNumber, uint8_t PinValue);
void MCAL_GPIO_WritePort(uint8_t GPIOx,uint16_t PortValue);

void MCAL_GPIO_TogglePin(uint8_t GPIOx,uint8_t PinNumber);

#endif /* ATMEGA32_GPIO_H_ */