/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    KEYPAD			******************/
/*****************************************************************/
/*****************************************************************/
#include "Keypad_interface.h"

static uint8 KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARRAY_VALUE;
static uint8 ColumnArr[COLUMN_NUM] = {KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
static uint8 RowArr[ROW_NUM] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


/*========================================================================================================
 * @Fun			:	KPD_Init
 * @Brief		:	Initialize the Keypad according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void KPD_Init(void)
{
	uint8 i=0;
	for(i=0 ;i<4 ; i++)
	{
		MCAL_DIO_SetPinDirection(KPD_ROW_PORT	 ,RowArr[i]	 , DIO_PIN_INPUT_PULL_UP);
		MCAL_DIO_SetPinDirection(KPD_COLUMN_PORT ,ColumnArr[i], DIO_PIN_OUTPUT);
	}
}

/*========================================================================================================
 * @Fun			:	KPD_GetPressedKey
 * @Brief		:	Get the pressed key from the keypad according to the configuration of the KPD_ARRAY_VALUE
 * @RetVal		:	The pressed key from the keypad and return the KPD_NOT_PRESSED_KEY if there is no key pressed
 * @Note		: 	The logic here is to pull up all the rows of the keypad and make every column low every time
 *========================================================================================================*/
uint8 KPD_GetPressedKey(void)
{
	uint8 PressedKey = KPD_NOT_PRESSED_KEY , ColumnIdx ,RowIdx , PinState;


	for(ColumnIdx=0 ; ColumnIdx<COLUMN_NUM ; ColumnIdx++)
	{
		/*Activate the current Column*/
		MCAL_DIO_SetPinValue(KPD_COLUMN_PORT,ColumnArr[ColumnIdx],DIO_PIN_LOW);

		for(RowIdx=0 ; RowIdx<ROW_NUM ; RowIdx++)
		{
			/*Read the current Row */
			MCAL_DIO_GetPinValue(KPD_ROW_PORT,RowArr[RowIdx],&PinState);

			/*Check if the key is pressed or not*/
			if (DIO_PIN_LOW == PinState)
			{
				PressedKey = KPDArr[RowIdx][ColumnIdx];

				/*Polling (busy waiting) until the key is released*/
				while(DIO_PIN_LOW == PinState)
				{
					MCAL_DIO_GetPinValue(KPD_ROW_PORT,RowArr[RowIdx],&PinState);
				}
				return PressedKey;
			}
		}
		/*Deactivate the current Column*/
		MCAL_DIO_SetPinValue(KPD_COLUMN_PORT,ColumnArr[ColumnIdx],DIO_PIN_HIGH);
	}

	return PressedKey;
}
