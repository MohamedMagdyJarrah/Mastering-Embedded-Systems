#include "Utils.h"
#include "KPD.h"

GPIO_PinConfig_t KeypadPins;
int keypad_rows[KEYPAD_ROWS] = {R1,R2,R3,R4};
int keypad_columns[KEYPAD_COLUMNS] = {C1,C2,C3,C4};

void KEYPAD_INIT(void)
{
	uint8_t i=0;


	/* Set all the rows as input with pull up resistors */
	for(i=0; i<KEYPAD_ROWS;i++)
	{
		KeypadPins.GPIO_PinNumber = keypad_rows[i];
		KeypadPins.GPIO_Mode = GPIO_MODE_INPUT_PULL_UP;
		MCAL_GPIO_Init(KPD_ROWS_PORT, &KeypadPins);
	}

	/* Set all the columns as output */
	for(i=0; i<KEYPAD_COLUMNS;i++)
	{
		KeypadPins.GPIO_PinNumber = keypad_columns[i];
		KeypadPins.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ;
		MCAL_GPIO_Init(KPD_COLUMNS_PORT, &KeypadPins);
	}

}


char KEYPAD_GET_KEY(void)
{
	unsigned char i=0 , j=0,x=0;
	static char keys[KEYPAD_ROWS][KEYPAD_COLUMNS] = KPD_KEYS;

	for (i=0 ; i<KEYPAD_COLUMNS; i++)
	{
		/* Set all the columns to VCC */
		for(x=0; x<KEYPAD_COLUMNS;x++)
		{
			MCAL_GPIO_WritePin(KPD_COLUMNS_PORT, keypad_columns[x], GPIO_PINSTATE_HIGH);
		}

		MCAL_GPIO_WritePin(KPD_COLUMNS_PORT, keypad_columns[i], GPIO_PINSTATE_LOW);


		/* Loop on every row to see if a key is pressed */
		for(j=0 ; j< KEYPAD_ROWS ; j++)
		{
			if(MCAL_GPIO_ReadPin(KPD_ROWS_PORT, keypad_rows[j]) == GPIO_PINSTATE_LOW)
			{
				while(MCAL_GPIO_ReadPin(KPD_ROWS_PORT, keypad_rows[j]) == GPIO_PINSTATE_LOW);  // To make it single press
				return keys[j][i];
			}
		}

	}
	return '?';
}
