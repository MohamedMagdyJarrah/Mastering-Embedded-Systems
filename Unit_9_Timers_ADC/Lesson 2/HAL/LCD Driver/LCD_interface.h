/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    LCD				******************/
/*****************************************************************/
/*****************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../MCAL/DIO Driver/DIO_interface.h"
#include <stdio.h>
#include <util/delay.h>
#include "LCD_private.h"

/**************************************** Macro Configurations *******************************************/
/*Configuration of Data Port*/
#define LCD_DATA_PORT		DIO_PORTA

/* Put the data pins as it appears for you from
 * (D7->D0) respectively if it is 8-bit mode
 * (D7->D4) respectively if it is 4-bit mode
 * Note: You should configure the macro to LCD_DATA_PINS
 */
#define LCD_DATA_8BIT_PINS	{DIO_PIN7,DIO_PIN6,DIO_PIN5,DIO_PIN4,DIO_PIN3,DIO_PIN2,DIO_PIN1,DIO_PIN0}
#define LCD_DATA_4BIT_PINS	{DIO_PIN6,DIO_PIN5,DIO_PIN4,DIO_PIN3}
/* Put your pins here */
#define LCD_DATA_PINS		LCD_DATA_4BIT_PINS

/*Configuration of Control Port and Pins*/
#define LCD_CTRL_PORT		DIO_PORTA
#define LCD_RS_PIN			DIO_PIN1
#define LCD_RW_PIN			DIO_PIN0
#define LCD_E_PIN			DIO_PIN2

/*Configure the mode of the LCD with (FOUR_BIT_MODE) or (EIGHT_BIT_MODE)*/
#define LCD_Mode			FOUR_BIT_MODE


/*=======================================================================================
 * 						APIs supported by "HAL LCD Driver"
 *=======================================================================================*/
void LCD_Init(void);
void LCD_SendCommand(uint8 command);
void LCD_SendChar(uint8 data);
void LCD_SendString(const char* data);
void LCD_GoToXY(uint8 line,uint8 column);
void LCD_SendNumber(sint64 number);
void LCD_SendRealNumber(float64 real_number);
void LCD_SinWaveDisplay(const char* Pattern);
void LCD_ClearDisplay(void);

#endif	/* LCD_INTERFACE_H_ */

