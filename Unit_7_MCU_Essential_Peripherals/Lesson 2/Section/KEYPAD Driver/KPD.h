#ifndef KPD_H_
#define KPD_H_

#define F_CPU				1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define KPD_ROWS_PORT		PORTD
#define KPD_COLUMNS_PORT	PORTD
#define KPD_ROWS_DIR		DDRD
#define KPD_COLUMNS_DIR		DDRD	
#define KPD_ROWS_PIN		PIND

#define R1					0
#define R2					1
#define R3					2
#define R4					3
#define C1					4
#define C2					5
#define C3					6
#define C4					7

#define KEYPAD_ROWS			4
#define KEYPAD_COLUMNS		4
#define KPD_KEYS			{{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'} ,{'@','0','=','+'}}


void KEYPAD_INIT(void);
char KEYPAD_GET_KEY(void);

#endif /* KPD_H_ */