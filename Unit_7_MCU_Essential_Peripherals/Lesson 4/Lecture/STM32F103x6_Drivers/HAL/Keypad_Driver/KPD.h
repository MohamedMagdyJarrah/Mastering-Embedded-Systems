#ifndef KPD_H_
#define KPD_H_

/*********************************************** Includes **********************************************/
#include "STM32F103x6.h"
#include "MCAL/GPIO Driver/STM32F103x6_GPIO.h"

/* Configure KPD Pins */
#define KPD_ROWS_PORT		GPIOB
#define KPD_COLUMNS_PORT	GPIOB

#define R1					GPIO_PIN_0
#define R2					GPIO_PIN_1
#define R3					GPIO_PIN_3
#define R4					GPIO_PIN_4
#define C1					GPIO_PIN_5
#define C2					GPIO_PIN_6
#define C3					GPIO_PIN_7
#define C4					GPIO_PIN_8

/* Configure KPD Keys */
#define KEYPAD_ROWS			4
#define KEYPAD_COLUMNS		4
#define KPD_KEYS			{{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'} ,{'@','0','=','+'}}

/*===============================================================================================
 * 								APIs supported by "HAL KEYPAD Driver"
 *===============================================================================================*/
void KEYPAD_INIT(void);
char KEYPAD_GET_KEY(void);

#endif /* KPD_H_ */
