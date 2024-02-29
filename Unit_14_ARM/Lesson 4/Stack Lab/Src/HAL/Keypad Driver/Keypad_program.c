/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    KEYPAD			******************/
/*****************************************************************/
/*****************************************************************/

#include "Keypad_interface.h"

static uint8_t KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARRAY_VALUE;
static uint8_t ColumnArr[COLUMN_NUM] = {KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
static uint8_t RowArr[ROW_NUM] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


/*========================================================================================================
 * @Fun			:	KPD_Init
 * @Brief		:	Initialize the Keypad according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void KPD_Init(void)
{
	uint8_t i=0;
	for(i=0 ;i<4 ; i++)
	{
		MCAL_GPIO_SetPinMode(KPD_ROW_PORT, RowArr[i], GPIO_PIN_MODE_INPUT_PULL_DOWN);
		MCAL_GPIO_SetPinMode(KPD_COLUMN_PORT,ColumnArr[i],GPIO_PIN_MODE_OUTPUT_PUSH_PULL_10_MHZ);
	}
}

/*========================================================================================================
 * @Fun			:	KPD_GetPressedKey
 * @Brief		:	Get the pressed key from the keypad according to the configuration of the KPD_ARRAY_VALUE
 * @RetVal		:	The pressed key from the keypad and return the KPD_NOT_PRESSED_KEY if there is no key pressed
 * @Note		: 	The logic here is to pull down all the rows of the keypad and make every column high every time
 *========================================================================================================*/
uint8_t KPD_GetPressedKey(void)
{
	uint8_t PressedKey = KPD_NOT_PRESSED_KEY , ColumnIdx ,RowIdx , PinState;


	for(ColumnIdx=0 ; ColumnIdx<COLUMN_NUM ; ColumnIdx++)
	{
		/*Activate the current Column*/
		MCAL_GPIO_WritePin(KPD_COLUMN_PORT, ColumnArr[ColumnIdx], GPIO_PINSTATE_HIGH);

		for(RowIdx=0 ; RowIdx<ROW_NUM ; RowIdx++)
		{
			/*Read the current Row */
			PinState = MCAL_GPIO_ReadPin(KPD_ROW_PORT, RowArr[RowIdx]);

			/*Check if the key is pressed or not*/
			if (GPIO_PINSTATE_HIGH == PinState)
			{
				PressedKey = KPDArr[RowIdx][ColumnIdx];

				/*Polling (busy waiting) until the key is released*/
				while(GPIO_PINSTATE_HIGH == PinState)
				{
					PinState = MCAL_GPIO_ReadPin(KPD_ROW_PORT, RowArr[RowIdx]);
				}
				return PressedKey;
			}
		}
		/*Deactivate the current Column*/
		MCAL_GPIO_WritePin(KPD_COLUMN_PORT, ColumnArr[ColumnIdx], GPIO_PINSTATE_LOW);
	}

	return PressedKey;
}

