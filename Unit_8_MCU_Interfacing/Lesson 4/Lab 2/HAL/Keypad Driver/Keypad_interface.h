/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    KEYPAD			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../MCAL/DIO Driver/DIO_interface.h"

/**************************************** Macro Configurations *******************************************/
/* To configure the ports of the rows and the columns of the keypad use: DIO_PORTx Macro where x is the port you connect on it
 * Also, To configure the pins use: DIO_PINx where x is the number of the pin you chose
 * */

/* 				Port of the KEYPAD Rows and Columns			*/
#define KPD_ROW_PORT			DIO_PORTD
#define KPD_COLUMN_PORT			DIO_PORTD

/*              Pins of the Columns				 */
#define KPD_COLUMN0_PIN			DIO_PIN4
#define KPD_COLUMN1_PIN			DIO_PIN5
#define KPD_COLUMN2_PIN			DIO_PIN6
#define KPD_COLUMN3_PIN			DIO_PIN7

/*              Pins of the Rows				 */
#define KPD_ROW0_PIN			DIO_PIN0
#define KPD_ROW1_PIN			DIO_PIN1
#define KPD_ROW2_PIN			DIO_PIN2
#define KPD_ROW3_PIN			DIO_PIN3

/* Macro to specify the number of rows and columns
 * Note: The driver built on Keypad 4x4 so discard these two Macros they are not configurations
 *  */
#define COLUMN_NUM				4
#define ROW_NUM					4

/*	Choose the result of the key if there is no key pressed on the keypad */
#define KPD_NOT_PRESSED_KEY		0xff
/* Configure your keypad buttons */
#define KPD_ARRAY_VALUE			{{'7','8','9','/'},{'4','5','6','x'},{'1','2','3','-'},{0xff,'0','=','+'}}

/*=======================================================================================
 * 						APIs supported by "HAL Keypad Driver"
 *=======================================================================================*/
void KPD_Init(void);
uint8 KPD_GetPressedKey(void);

#endif	/* KPD_INTERFACE_H_ */
