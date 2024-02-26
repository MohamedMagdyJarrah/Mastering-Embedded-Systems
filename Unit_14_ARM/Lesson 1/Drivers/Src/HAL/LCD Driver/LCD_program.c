/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    LCD				******************/
/*****************************************************************/
/*****************************************************************/
#include "LCD_interface.h"

static uint8_t LCD_DataPins[8] = LCD_DATA_PINS;

/*========================================================================================================
 * @Fun			:	wait_ms
 * @Brief		:	Function to generate software delay
 * @Param[in]  	:	time: The time in milliseconds
 * @RetVal		:	None
 * @Note		: 	This Function is an approximation for the time
 *========================================================================================================*/
static void wait_ms(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

/*========================================================================================================
 * @Fun			:	LCD_Kick
 * @Brief		:	Make Pulse on the enable pin to make an action
 * @RetVal		:	None
 *========================================================================================================*/
static void LCD_Kick(void)
{
	/* Make Pulse on enable pin for 2ms then set it back to zero */
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_E_PIN, GPIO_PINSTATE_HIGH);
	wait_ms(2);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_E_PIN, GPIO_PINSTATE_LOW);
	wait_ms(2);
}


/*========================================================================================================
 * @Fun			:	LCD_INIT
 * @Brief		:	Initialize the LCD according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_Init(void)
{
	/* Wait for 40ms */
	wait_ms(40);

	/* Configure the control pins to be output */
	MCAL_GPIO_SetPinMode(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_10_MHZ);
	MCAL_GPIO_SetPinMode(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_10_MHZ);
	MCAL_GPIO_SetPinMode(LCD_CTRL_PORT, LCD_E_PIN, 	GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_10_MHZ);


	/* Initialize the 8-bit mode Configuration */
#if LCD_Mode == EIGHT_BIT_MODE
	/* Configure the data pins to be output */
	for(uint8_t i =0 ; i< 8 ; i++)
	{
		MCAL_GPIO_SetPinMode(LCD_DATA_PORT, LCD_DataPins[i], GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_10_MHZ);
	}

	/*Wait for more than 40ms */
	wait_ms(40);

	/* Configure the LCD in 8 bit mode */
	LCD_SendCommand(LCD_FUNCTION_8BIT_2LINES);

	/* Initialize the 4-bit mode Configuration */
#elif LCD_Mode == FOUR_BIT_MODE
	/* Configure the data pins to be output */
	for(uint8_t i =0 ; i< 4 ; i++)
	{
		MCAL_GPIO_SetPinMode(LCD_DATA_PORT, LCD_DataPins[i], GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_10_MHZ);
	}

	/* Send Return Home command to initialize the 4-bit mode */
	LCD_SendCommand(LCD_FUNCTION_RETURN_HOME);
	/* Configure the LCD in 4 bit mode */
	LCD_SendCommand(LCD_FUNCTION_4BIT_2LINES);

#endif
	/*Display ON the screen with cursor blink */
	LCD_SendCommand(LCD_DISP_ON_CURSOR_BLINK);

	/*Display Clear*/
	LCD_SendCommand(LCD_CLEAR_SCREEN);

}

/*========================================================================================================
 * @Fun			:	LCD_SendCommand
 * @Brief		:	Send command to LCD controller according to the Specs
 * @Param[in]  	:	command: The commands according to @ref LCD Commands
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_SendCommand(uint8_t command)
{
	/*Set RS LOW for Command*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_PINSTATE_LOW);

	/*Set RW LOW for Write*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_PINSTATE_LOW);

	/* Sending Command in 8-bit mode */
#if LCD_Mode == EIGHT_BIT_MODE

	/* Put the command on the data pins */
	//	MCAL_DIO_SetPortValue(LCD_DATA_PORT,command);
	for(uint8_t i=0 ; i<8 ; i++)
	{
		MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DataPins[i], GET_BIT(command,(7-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

	/* Sending Command in 4-bit mode */
#elif LCD_Mode == FOUR_BIT_MODE

	/* Put the 4 Most significant bits first */
	for(uint8_t i =0 ; i<4 ; i++)
	{
		MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DataPins[i], GET_BIT(command,(7-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

	/* Then Put the 4 Least significant bits */
	for(uint8_t i =0 ; i<4 ; i++)
	{
		MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DataPins[i], GET_BIT(command,(3-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();


#endif
}

/*========================================================================================================
 * @Fun			:	LCD_SendChar
 * @Brief		:	Send data to LCD controller to display it on the screen
 * @Param[in]  	:	data: The data sent by the user
 * @RetVal		:	None
 * @Note		:	The data sent according to ASCII Table
 *========================================================================================================*/
void LCD_SendChar(uint8_t data)
{
	/*Set RS HIGH for Data*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_PINSTATE_HIGH);

	/*Set RW LOW for Write*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_PINSTATE_LOW);

	/* Sending data in 8-bit mode */
#if LCD_Mode == EIGHT_BIT_MODE

	/* Put the data on the data pins */
	//	MCAL_DIO_SetPortValue(LCD_DATA_PORT,data);
	for(uint8_t i=0 ; i<8 ; i++)
	{
		MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DataPins[i], GET_BIT(data,(7-i)));
	}

	/*Make Pulse on the enable pin to show the data*/
	LCD_Kick();

	/* Sending data in 4-bit mode */
#elif LCD_Mode == FOUR_BIT_MODE

	/* Put the 4 Most significant bits first */
	for(uint8_t i =0 ; i<4 ; i++)
	{
		MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DataPins[i], GET_BIT(data,(7-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

	/* Then Put the 4 Least significant bits */
	for(uint8_t i =0 ; i<4 ; i++)
	{
		MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DataPins[i], GET_BIT(data,(3-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

#endif
}

/*========================================================================================================
 * @Fun			:	LCD_SendString
 * @Brief		:	Send string to LCD controller to display it on the screen
 * @Param[in]  	:	data: The string sent by the user
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_SendString(const char* data)
{
	uint8_t i =0 , count= 0;
	/* Looping on the string until it ends */
	while(data[i] != '\0')
	{
		LCD_SendChar(data[i]);
		count++;
		i++;
		/* Go to the second line if I reach the end of the first one */
		if(count == 16)
		{
			LCD_GoToXY(1,0);
		}
		/* Clear the screen if I overcome the size of LCD Screen */
		else if(count == 32 || count == 33)
		{
			LCD_SendCommand(LCD_CLEAR_SCREEN);
			LCD_GoToXY(0,0);
			count = 0;
		}
	}
}

/*========================================================================================================
 * @Fun			:	LCD_GoToXY
 * @Brief		:	This Function give the user the control to specific point on the LCD
 * @Param[in]  	:	line: The horizontal line the user chose to write on it (X Point)
 * @Param[in]  	:	column: The vertical line the user chose to write on it (Y Point)
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_GoToXY(uint8_t line,uint8_t column)
{
	/* Moving along the first line of the LCD according to the column */
	if(line == 0)
	{
		/* Make sure that the user will not go out the range of the LCD */
		if(column>=0 && column <16)
		{
			LCD_SendCommand(LCD_BEGIN_AT_FIRST_ROW+column);
		}
	}
	/* Moving along the second line of the LCD according to the column */
	else if(line == 1 )
	{
		/* Make sure that the user will not go out the range of the LCD */
		if(column>=0 && column <16)
		{
			LCD_SendCommand(LCD_BEGIN_AT_SECOND_ROW+column);
		}
	}
}

/*========================================================================================================
 * @Fun			:	LCD_SendNumber
 * @Brief		:	Send Number to LCD controller to display it on the screen
 * @Param[in]  	:	number: The Number sent by the user
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_SendNumber(sint64_t number)
{
	/* Saving the number as a string using sprintf function and send it as a string */
	char str[7];
	sprintf(str,"%ld",number);
	LCD_SendString(str);
}

/*========================================================================================================
 * @Fun			:	LCD_SendRealNumber
 * @Brief		:	Send Real Number to LCD controller to display it on the screen
 * @Param[in]  	:	real_number: The Real Number sent by the user
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_SendRealNumber(float64_t real_number)
{
	char str[16];

	/* Check the number is negative or not */
	char* sign = (real_number<0) ? "-" : "";
	/* If the number is negative change it to positive to print the number */
	float val = (real_number<0) ? -real_number : real_number;

	/* Constructing the integer value */
	int num = val;
	/* Constructing the decimal value  */
	float dec = val - num;
	/* Take the first four decimal numbers only */
	int finalDec = dec*10000;

	/* Send the number as a string like we did in LCD_SendNumber Function */
	sprintf(str,"%s%d.%04d",sign,num,finalDec);
	LCD_SendString(str);
}

/*========================================================================================================
 * @Fun			:	LCD_ClearDisplay
 * @Brief		:	Clear the screen of the LCD
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_ClearDisplay(void)
{
	LCD_SendCommand(LCD_CLEAR_SCREEN);
}

/*========================================================================================================
 * @Fun			:	LCD_SinWaveDisplay
 * @Brief		:	Display string on the screen in Sin wave pattern
 * @Param[in]  	:	Pattern: The string sent by the user
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_SinWaveDisplay(const char* Pattern)
{
	uint8_t Local_u8Iterator=0 , row=0;
	for(Local_u8Iterator=0;Local_u8Iterator<16;Local_u8Iterator++)
	{
		LCD_GoToXY(row,Local_u8Iterator);
		LCD_SendString(Pattern);
		wait_ms(500);
		LCD_ClearDisplay();
		/* Switch between the two rows every time */
		row ^=1;
	}
}

/*========================================================================================================
 * @Fun			:	LCD_SinWaveDisplay
 * @Brief		:	This Function let you draw any unique shape on the LCD
 * @Param[in]  	:	Pattern: The Pattern sent by the user as it is an array contain the pixels of every block in LCD
 * @Param[in]  	:	PatternNumber: The Number of Pattern as it will be saved in a Table in LCD Memory
 * @Param[in]  	:	XPos: The line of the pattern the user will draw (X Position)
 * @Param[in]  	:	YPos: The Column of the pattern the user will draw (Y Position)
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_WriteSpecialCharacter(uint8_t* Pattern , uint8_t PatternNumber , uint8_t XPos, uint8_t YPos)
{
	uint8_t Local_u8CGRAMAddress =0 , Local_u8Iterator =0 ;

	/*Calculate the Address of the block you will access in CGRAM*/
	Local_u8CGRAMAddress = PatternNumber*8;
	/*Send command that we will write in this CGRAM Address with setting bit 6 to 1*/
	LCD_SendCommand(Local_u8CGRAMAddress+64);
	/*Putting the pattern in this in the CGRAM Address*/
	for(Local_u8Iterator=0 ; Local_u8Iterator<8 ; Local_u8Iterator++)
	{
		LCD_SendChar(Pattern[Local_u8Iterator]);
	}

	/*Choosing the place on the CLCD of the special character*/
	LCD_GoToXY(XPos,YPos);
	/*Display the Character on the CLCD  (DDRAM access the locations in CGRAM with blocks from 0 to 7*/
	LCD_SendChar(PatternNumber);
}
