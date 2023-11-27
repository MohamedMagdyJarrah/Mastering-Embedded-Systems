#include "../LIB/Utils.h"
#include "KPD.h"

static int keypad_rows[KEYPAD_ROWS] = {R1,R2,R3,R4};
static int keypad_columns[KEYPAD_COLUMNS] = {C1,C2,C3,C4}; 

void KEYPAD_INIT(void)
{
	/* Set all the rows as input */
	KPD_ROWS_DIR &= ~( (1<<R1) | (1<<R2) | (1<<R3) | (1<<R4) );
	
	/* Set all the columns as output */
	KPD_COLUMNS_DIR |= ( (1<<C1) | (1<<C2) | (1<<C3) | (1<<C4) );
	
	/* Make all columns in the beginning to be high and all rows connected with pull up resistors */
	KPD_COLUMNS_PORT |= ( (1<<C1) | (1<<C2) | (1<<C3) | (1<<C4) );
	KPD_COLUMNS_PORT |= ( (1<<R1) | (1<<R2) | (1<<R3) | (1<<R4) );
}


char KEYPAD_GET_KEY(void)
{
	unsigned char i=0 , j=0;
	static char keys[KEYPAD_ROWS][KEYPAD_COLUMNS] = KPD_KEYS;
	
	for (i=0 ; i<KEYPAD_COLUMNS; i++)
	{
		/* Set all the columns to VCC */
		KPD_COLUMNS_PORT |= ( (1<<C1) | (1<<C2) | (1<<C3) | (1<<C4) );
		
		/*Set Every column to ground  */
		CLR_BIT(KPD_COLUMNS_PORT,keypad_columns[i]);
		
		/* Loop on every row to see if a key is pressed */
		for(j=0 ; j< KEYPAD_ROWS ; j++)
		{
			if(GET_BIT(KPD_ROWS_PIN,keypad_rows[j]) == 0)
			{
				while(GET_BIT(KPD_ROWS_PIN,keypad_rows[j]) == 0);	// To make it single press
				return keys[j][i];
			}
		}
		
	}
	
	return '?';
}
