#include "LCD.h"

GPIO_PinConfig_t LCDPins;

#if LCD_MODE == EIGHT_BIT_MODE
uint8_t DataPins[8] = LCD_DATA_PINS_8_BIT_MODE;
#elif LCD_MODE == FOUR_BIT_MODE
uint8_t DataPins[8] = LCD_DATA_PINS_4_BIT_MODE;
#endif


/* Make a delay function */
static void waitMs(uint32_t time)
{
	uint32_t i,j;
	for(i=0 ; i< time ;i++)
		for(j=0 ; j< 255 ;j++);
}

/* To Set and Reset the enable pin */
static void LCD_KICK(void)
{
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_E_PIN, GPIO_PINSTATE_HIGH);
	waitMs(50);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_E_PIN, GPIO_PINSTATE_LOW);
}

/* Check LCD is busy or not */
//static void LCD_IS_BUSY(void)
//{
//	uint8_t i =0;
//	/* Set the direction of data port as input */
//	for(i=0 ; i< 8 ; i++)
//	{
//		LCDPins.GPIO_PinNumber = DataPins[i];
//		LCDPins.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
//		MCAL_GPIO_Init(LCD_DATA_PORT, &LCDPins);
//	}
//
//	/*Set RS LOW to send Command*/
//	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RS_PIN, GPIO_PINSTATE_LOW);
//
//	/*Set RW HIGH to READ from LCD */
//	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RW_PIN, GPIO_PINSTATE_HIGH);
//
//	LCD_KICK();
//
//	for(i=0 ; i< 8 ; i++)
//	{
//		LCDPins.GPIO_PinNumber = DataPins[i];
//		LCDPins.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ;
//		MCAL_GPIO_Init(LCD_DATA_PORT, &LCDPins);
//	}
//
//}

/* LCD initialization function */
void LCD_INIT(void)
{
	uint8_t i = 0;
	waitMs(20);
	/* Configure the direction of the pins */
	LCDPins.GPIO_PinNumber = LCD_RW_PIN;
	LCDPins.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ;
	MCAL_GPIO_Init(LCD_CONFIGE_PORT, &LCDPins);

	LCDPins.GPIO_PinNumber = LCD_RS_PIN;
	LCDPins.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ;
	MCAL_GPIO_Init(LCD_CONFIGE_PORT, &LCDPins);

	LCDPins.GPIO_PinNumber = LCD_E_PIN;
	LCDPins.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ;
	MCAL_GPIO_Init(LCD_CONFIGE_PORT, &LCDPins);

#if LCD_MODE == EIGHT_BIT_MODE
	for(i=0 ; i< 8 ; i++)
	{
		LCDPins.GPIO_PinNumber = DataPins[i];
		LCDPins.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL_10_MHZ;
		MCAL_GPIO_Init(LCD_DATA_PORT, &LCDPins);
	}
#elif LCD_MODE == FOUR_BIT_MODE


#endif

	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_E_PIN, GPIO_PINSTATE_LOW);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RS_PIN, GPIO_PINSTATE_LOW);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RW_PIN, GPIO_PINSTATE_LOW);


	waitMs(15);
	/* Clear Screen */
	LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);
	/* Configure LCD According to the mode */
#if LCD_MODE == EIGHT_BIT_MODE
	/* Configure the LCD in 8 bit mode */
	LCD_SEND_COMMAND(LCD_FUNCTION_8BIT_2LINES);

#elif LCD_MODE == FOUR_BIT_MODE


#endif

	LCD_SEND_COMMAND(LCD_ENTRY_MODE);
	LCD_SEND_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_SEND_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

/* Send command into LCD */
void LCD_SEND_COMMAND(uint8_t command)
{
//	LCD_IS_BUSY();
#if LCD_MODE == EIGHT_BIT_MODE
	/*Set RS LOW to send Command*/
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RS_PIN, GPIO_PINSTATE_LOW);
	/*Set RW LOW to Write on LCD */
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RW_PIN, GPIO_PINSTATE_LOW);
	/*Put command in data port*/
	//	MCAL_GPIO_WritePort(LCD_DATA_PORT, command);
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xff00) | command;


	waitMs(1);
	/*Put Enable pin high to show the data */
	LCD_KICK();

#elif LCD_MODE == FOUR_BIT_MODE

#endif
}

/* To send display string on LCD */
void LCD_SEND_CHAR(uint8_t data)
{
//	LCD_IS_BUSY();
	/*Set RS HIGH to send Data */
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RS_PIN, GPIO_PINSTATE_HIGH);
	/*Set RW LOW to Write on LCD */
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT, LCD_RW_PIN, GPIO_PINSTATE_LOW);
	/*Put the data in data port*/
	//	MCAL_GPIO_WritePort(LCD_DATA_PORT, data);

	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xff00) | data;
	waitMs(1);
	/*Put Enable pin high to show the data */
	LCD_KICK();
}

/* To send display string on LCD */
void LCD_SEND_STRING(const char* data)
{
	uint8_t i =0 , count= 0;
	while(data[i] != '\0')
	{
		count++;
		LCD_SEND_CHAR(data[i]);
		i++;
		if(count == 16)
		{
			LCD_GO_TO_XY(1,0);
		}
		else if(count == 32 || count == 33)
		{
			LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);
			LCD_GO_TO_XY(0,0);
			count = 0;
		}
	}
}

/* To adjust the place of the cursor */
void LCD_GO_TO_XY(uint8_t line,uint8_t column)
{
	if(line == 0)
	{
		if(column>=0 && column <16)
		{
			LCD_SEND_COMMAND(LCD_BEGIN_AT_FIRST_ROW+column);
		}
	}
	else if(line == 1 )
	{
		if(column>=0 && column <16)
		{
			LCD_SEND_COMMAND(LCD_BEGIN_AT_SECOND_ROW+column);
		}
	}

}

/* Display number on LCD */
void LCD_SEND_NUMBER(uint32_t number)
{
	char str[7];
	sprintf(str,"%d",number);
	LCD_SEND_STRING(str);
}

/*Display Real numbers */
void LCD_SEND_REAL_NUMBER(float64 real_number)
{
	char str[16];

	char* sign = (real_number<0) ? "-" : "";
	float val = (real_number<0) ? -real_number : real_number;

	int num = val;
	float dec = val - num;
	int finalDec = dec*10000;

	sprintf(str,"%s%d.%04d",sign,num,finalDec);
	LCD_SEND_STRING(str);
}
