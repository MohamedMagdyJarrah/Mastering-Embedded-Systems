/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    GPIO			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef INC_STM32F103X6_GPIO_H_
#define INC_STM32F103X6_GPIO_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/STM32F103x6_MemMap.h"

/*===============================================================================================
  								APIs supported by "MCAL GPIO Driver"
 *===============================================================================================*/
 /*************************************DESCRIPTION****************************************/
 /*
  1- Choose your Port according to GPIOx where can be (A...E depending on the device)
  2- Choose your Port mode according to @ref GPIO_PORT_MODE_define
  3- Choose your Port mode according to @ref GPIO_PIN_MODE_define
  4- Choose your Pin value according to @ref GPIO_PINSTATE_define
  5- Choose your Port value according to @ref GPIO_PORTSTATE_define or Write the wanted value
  6- Choose your Pin number according to @ref GPIO_PIN_define
  */
void MCAL_GPIO_SetPinMode(GPIO_t* GPIOx,uint8_t PinNumber,uint8_t PinMode);
void MCAL_GPIO_SetPortMode(GPIO_t* GPIOx,uint32_t PortMode);

void MCAL_GPIO_WritePin(GPIO_t* GPIOx,uint8_t PinNumber, uint8_t PinValue);
void MCAL_GPIO_WritePort(GPIO_t* GPIOx,uint16_t PortValue);

void MCAL_GPIO_TogglePin(GPIO_t* GPIOx,uint8_t PinNumber);
void MCAL_GPIO_TogglePort(GPIO_t* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_t* GPIOx,uint8_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_t* GPIOx);

uint8_t MCAL_GPIO_LockPin(GPIO_t* GPIOx,uint8_t PinNumber);

#endif /* INC_STM32F103X6_GPIO_H_ */
