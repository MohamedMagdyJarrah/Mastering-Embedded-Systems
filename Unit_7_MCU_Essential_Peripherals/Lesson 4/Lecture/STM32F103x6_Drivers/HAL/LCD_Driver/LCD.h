#ifndef LCD_H_
#define LCD_H_

/* Include the necessary libraries */
#include "Utils.h"
#include "Platform_Types.h"
#include <stdio.h>
#include "STM32F103x6.h"
#include "MCAL/GPIO Driver/STM32F103x6_GPIO.h"


/* Configure LCD Pins */
#define LCD_DATA_PORT				GPIOA
#define LCD_CONFIGE_PORT			GPIOA
#define LCD_RS_PIN					GPIO_PIN_8
#define LCD_RW_PIN					GPIO_PIN_9
#define LCD_E_PIN					GPIO_PIN_10
/* Write the pins of Data pins (D0..D7) */
#define LCD_DATA_PINS_8_BIT_MODE	{GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7}


/* Configure LCD Mode */
#define LCD_MODE			EIGHT_BIT_MODE
#define FOUR_BIT_MODE		0
#define EIGHT_BIT_MODE		1

/* LCD Commands */
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

/*===============================================================================================
 * 								APIs supported by "HAL LCD Driver"
 *===============================================================================================*/
void LCD_INIT(void);
void LCD_SEND_COMMAND(uint8_t command);
void LCD_SEND_CHAR(uint8_t data);
void LCD_SEND_STRING(const char* data);
void LCD_GO_TO_XY(uint8_t x,uint8_t y);
void LCD_SEND_NUMBER(uint32_t number);
void LCD_SEND_REAL_NUMBER(float64 real_number);

#endif /* LCD_H_ */
