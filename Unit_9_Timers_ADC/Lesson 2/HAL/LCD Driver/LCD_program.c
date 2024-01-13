/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    LCD				******************/
/*****************************************************************/
/*****************************************************************/
#include "LCD_interface.h"

static uint8 LCD_DataPins[8] = LCD_DATA_PINS;

/*========================================================================================================
 * @Fun			:	LCD_Kick
 * @Brief		:	Make Pulse on the enable pin to make an action
 * @RetVal		:	None
 *========================================================================================================*/
static void LCD_Kick(void)
{
	/* Make Pulse on enable pin for 2ms then set it back to zero */
	MCAL_DIO_SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	MCAL_DIO_SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_PIN_LOW);
	_delay_us(100);
}


/*========================================================================================================
 * @Fun			:	LCD_INIT
 * @Brief		:	Initialize the LCD according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void LCD_Init(void)
{
	/* Wait for 40ms */
	_delay_ms(40);

	/* Configure the control pins to be output */
	MCAL_DIO_SetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	MCAL_DIO_SetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,DIO_PIN_OUTPUT);

	/* Initialize the 8-bit mode Configuration */
#if LCD_Mode == EIGHT_BIT_MODE
	/* Configure the data pins to be output */
	for(uint8 i =0 ; i< 8 ; i++)
	{
		MCAL_DIO_SetPinDirection(LCD_DATA_PORT,LCD_DataPins[i],DIO_PIN_OUTPUT);
	}

	/*Wait for more than 40ms */
	_delay_ms(40);

	/* Configure the LCD in 8 bit mode */
	LCD_SendCommand(LCD_FUNCTION_8BIT_2LINES);

	/* Initialize the 4-bit mode Configuration */
#elif LCD_Mode == FOUR_BIT_MODE
	/* Configure the data pins to be output */
	for(uint8 i =0 ; i< 4 ; i++)
	{
		MCAL_DIO_SetPinDirection(LCD_DATA_PORT,LCD_DataPins[i],DIO_PIN_OUTPUT);
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
void LCD_SendCommand(uint8 command)
{
	/*Set RS LOW for Command*/
	MCAL_DIO_SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_LOW);

	/*Set RW LOW for Write*/
	MCAL_DIO_SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_LOW);

	/* Sending Command in 8-bit mode */
#if LCD_Mode == EIGHT_BIT_MODE

	/* Put the command on the data pins */
	MCAL_DIO_SetPortValue(LCD_DATA_PORT,command);
	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

	/* Sending Command in 4-bit mode */
#elif LCD_Mode == FOUR_BIT_MODE

	/* Put the 4 Most significant bits first */
	for(uint8 i =0 ; i<4 ; i++)
	{
		MCAL_DIO_SetPinValue(LCD_DATA_PORT,LCD_DataPins[i],GET_BIT(command,(7-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

	/* Then Put the 4 Least significant bits */
	for(uint8 i =0 ; i<4 ; i++)
	{
		MCAL_DIO_SetPinValue(LCD_DATA_PORT,LCD_DataPins[i],GET_BIT(command,(3-i)));
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
void LCD_SendChar(uint8 data)
{
	/*Set RS HIGH for Data*/
	MCAL_DIO_SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_HIGH);

	/*Set RW LOW for Write*/
	MCAL_DIO_SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_LOW);

	/* Sending data in 8-bit mode */
#if LCD_Mode == EIGHT_BIT_MODE

	/* Put the data on the data pins */
	MCAL_DIO_SetPortValue(LCD_DATA_PORT,data);
	/*Make Pulse on the enable pin to show the data*/
	LCD_Kick();

	/* Sending data in 4-bit mode */
#elif LCD_Mode == FOUR_BIT_MODE

	/* Put the 4 Most significant bits first */
	for(uint8 i =0 ; i<4 ; i++)
	{
		MCAL_DIO_SetPinValue(LCD_DATA_PORT ,LCD_DataPins[i] ,GET_BIT(data,(7-i)));
	}

	/*Make Pulse on the enable pin to send the command*/
	LCD_Kick();

	/* Then Put the 4 Least significant bits */
	for(uint8 i =0 ; i<4 ; i++)
	{
		MCAL_DIO_SetPinValue(LCD_DATA_PORT,LCD_DataPins[i],GET_BIT(data,(3-i)));
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
	uint8 i =0 , count= 0;
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
void LCD_GoToXY(uint8 line,uint8 column)
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
void LCD_SendNumber(sint64 number)
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
void LCD_SendRealNumber(float64 real_number)
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
	uint8 Local_u8Iterator=0 , row=0;
	for(Local_u8Iterator=0;Local_u8Iterator<16;Local_u8Iterator++)
	{
		LCD_GoToXY(row,Local_u8Iterator);
		LCD_SendString(Pattern);
		_delay_ms(500);
		LCD_ClearDisplay();
		/* Switch between the two rows every time */
		row ^=1;
	}
}
