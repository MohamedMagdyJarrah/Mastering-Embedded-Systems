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
#include "../../MCAL/GPIO Driver/GPIO_interface.h"
#include <stdio.h>
#include "LCD_private.h"

/**************************************** Macro Configurations *******************************************/
/*Configuration of Data Port*/
#define LCD_DATA_PORT		GPIOA

/* Put the data pins as it appears for you from
 * (D7->D0) respectively if it is 8-bit mode
 * (D7->D4) respectively if it is 4-bit mode
 * Note: You should configure the macro to LCD_DATA_PINS
 */
#define LCD_DATA_8BIT_PINS	{GPIO_PIN_7,GPIO_PIN_6,GPIO_PIN_5,GPIO_PIN_4,GPIO_PIN_3,GPIO_PIN_2,GPIO_PIN_1,GPIO_PIN_0}
#define LCD_DATA_4BIT_PINS	{GPIO_PIN_7,GPIO_PIN_6,GPIO_PIN_5,GPIO_PIN_4}
/* Put your pins here */
#define LCD_DATA_PINS		LCD_DATA_8BIT_PINS

/*Configuration of Control Port and Pins*/
#define LCD_CTRL_PORT		GPIOA
#define LCD_RS_PIN			GPIO_PIN_8
#define LCD_RW_PIN			GPIO_PIN_9
#define LCD_E_PIN			GPIO_PIN_10

/*Configure the mode of the LCD with (FOUR_BIT_MODE) or (EIGHT_BIT_MODE)*/
#define LCD_Mode			EIGHT_BIT_MODE


/*=======================================================================================
 * 						APIs supported by "HAL LCD Driver"
 *=======================================================================================*/
void LCD_Init(void);
void LCD_SendCommand(uint8_t command);
void LCD_SendChar(uint8_t data);
void LCD_SendString(const char* data);
void LCD_GoToXY(uint8_t line,uint8_t column);
void LCD_SendNumber(sint64_t number);
void LCD_SendRealNumber(float64_t real_number);
void LCD_SinWaveDisplay(const char* Pattern);
void LCD_WriteSpecialCharacter(uint8_t* Pattern , uint8_t PatternNumber , uint8_t XPos, uint8_t YPos);
void LCD_ClearDisplay(void);

#endif	/* LCD_INTERFACE_H_ */

