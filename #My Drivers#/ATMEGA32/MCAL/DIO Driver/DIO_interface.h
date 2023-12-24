/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    DIO				******************/
/*****************************************************************/
/*****************************************************************/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/ATMEGA32_MemMap.h"


/*=======================================================================================
 * 						APIs supported by "MCAL DIO Driver"
 *=======================================================================================*/
/*************************************DESCRIPTION****************************************/
/*
 1- To Enter your Port direction you should enter DIO_PORT_INPUT_FLOATING or DIO_PORT_INPUT_PULL_UP or DIO_PORT_OUTPUT
 2- To Enter your Pin direction you should enter DIO_PIN_INPUT_FLOATING or DIO_PIN_INPUT_PULL_UP or DIO_PIN_OUTPUT
 3- To Enter your Port name you should enter DIO_PORTx (A,B,C,D)
 4- To Enter your Pin name you should enter DIO_PINx (0,1,2,3,4,5,6,7)
 5- To Enter your Port value you should enter DIO_PORT_HIGH or DIO_PORT_LOW
 6- To Enter your Pin value you should enter DIO_PIN_HIGH or DIO_PIN_LOW
 7- To get value of pin you should pass address of variable with port and pin to store the value in it
 */

uint8 MCAL_DIO_SetPinDirection(uint8 Copy_Port, uint8 Copy_Pin, uint8 Copy_Direction);

uint8 MCAL_DIO_SetPortDirection(uint8 Copy_Port, uint8 Copy_Direction);

uint8 MCAL_DIO_SetPinValue(uint8 Copy_Port, uint8 Copy_Pin, uint8 Copy_Value);

uint8 MCAL_DIO_SetPortValue(uint8 Copy_Port, uint8 Copy_Value);

uint8 MCAL_DIO_TogglePinValue(uint8 Copy_Port, uint8 Copy_Pin);

uint8 MCAL_DIO_TogglePortValue(uint8 Copy_Port);

uint8 MCAL_DIO_GetPinValue(uint8 Copy_Port, uint8 Copy_Pin, uint8* Copy_PinValue);

#endif
