#include "LCD.h"

/* To Set and Reset the enable pin */
static void LCD_KICK(void)
{
	//SET_BIT(LCD_CONFIGE_PORT,LCD_E_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_E_PIN,GPIO_PINSTATE_HIGH);
	_delay_ms(50);
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_E_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_E_PIN,GPIO_PINSTATE_LOW);
	_delay_ms(50);
}

/* Check LCD is busy or not */
static void LCD_IS_BUSY(void)
{
	/* Set the direction of data port as input */
	//LCD_DATA_DIR = 0x00;
	MCAL_GPIO_PortInit(LCD_DATA_PORT,GPIO_MODE_INPUT_FLOATING);
	
	/*Set RS LOW to send Command*/
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RS_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RS_PIN,GPIO_PINSTATE_LOW);
	
	/*Set RW HIGH to READ from LCD */
	//SET_BIT(LCD_CONFIGE_PORT,LCD_RW_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RW_PIN,GPIO_PINSTATE_HIGH);

	LCD_KICK();
	
	//LCD_DATA_DIR = 0xFF;
	MCAL_GPIO_PortInit(LCD_DATA_PORT,GPIO_MODE_OUTPUT);
}

/* LCD initialization function */
void LCD_INIT(void)
{
	/* Configure the direction of the pins */
	//LCD_CONFIGE_DIR |= (1<<LCD_RS_PIN) | (1<<LCD_RW_PIN) | (1<<LCD_E_PIN);
	//LCD_CONFIGE_PORT &= ~((1<<LCD_RS_PIN) | (1<<LCD_RW_PIN) | (1<<LCD_E_PIN));
	//LCD_DATA_DIR = 0xff;
	
	GPIO_PinConfig_t pinConfig;
	pinConfig.GPIO_PinNumber = LCD_RS_PIN;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(LCD_CONFIGE_PORT,&pinConfig);
	pinConfig.GPIO_PinNumber = LCD_RW_PIN;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(LCD_CONFIGE_PORT,&pinConfig);
	pinConfig.GPIO_PinNumber = LCD_E_PIN;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(LCD_CONFIGE_PORT,&pinConfig);
	
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RS_PIN,GPIO_PINSTATE_LOW);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RW_PIN,GPIO_PINSTATE_LOW);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_E_PIN,GPIO_PINSTATE_LOW);
	
	MCAL_GPIO_PortInit(LCD_DATA_PORT,GPIO_MODE_OUTPUT);
	
	/* Configure LCD According to the mode */
	#if LCD_MODE == EIGHT_BIT_MODE
	/* Wait for 20ms */
	_delay_ms(40);
	/* Configure the LCD in 8 bit mode */
	LCD_SEND_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	/* Clear Screen */
	//LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);
	
	#elif LCD_MODE == FOUR_BIT_MODE
	/* Wait for 20ms */
	_delay_ms(40);
	/* Configure the LCD in 4 bit mode */
	LCD_SEND_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	
	#endif	
	
	LCD_SEND_COMMAND(LCD_ENTRY_MODE);
	LCD_SEND_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_SEND_COMMAND(LCD_DISP_ON_BLINK);
}

/* Send command into LCD */
void LCD_SEND_COMMAND(unsigned char command)
{
	LCD_IS_BUSY();
	#if LCD_MODE == EIGHT_BIT_MODE
	/*Set RS LOW to send Command*/
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RS_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RS_PIN,GPIO_PINSTATE_LOW);

	
	/*Set RW LOW to Write on LCD */
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RW_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RW_PIN,GPIO_PINSTATE_LOW);

	
	/*Put command in data port*/
	//LCD_DATA_PORT = command;
	MCAL_GPIO_WritePort(LCD_DATA_PORT,command);
	
	
	/*Put Enable pin high to show the data */
	LCD_KICK();
	
	#elif LCD_MODE == FOUR_BIT_MODE
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_7,GET_BIT(command,7));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_6,GET_BIT(command,6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_5,GET_BIT(command,5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_4,GET_BIT(command,4));
	
	/*Set RS LOW to send Command*/
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RS_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RS_PIN,GPIO_PINSTATE_LOW);

	
	/*Set RW LOW to Write on LCD */
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RW_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RW_PIN,GPIO_PINSTATE_LOW);
	
	LCD_KICK();
	
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_7,GET_BIT(command,3));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_6,GET_BIT(command,2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_5,GET_BIT(command,1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_4,GET_BIT(command,0));
	
	LCD_KICK();
	
	#endif
}

/* To send display string on LCD */
void LCD_SEND_CHAR(unsigned char data)
{
	#if LCD_MODE == EIGHT_BIT_MODE
	LCD_IS_BUSY();
	/*Set RS HIGH to send Data */
	//SET_BIT(LCD_CONFIGE_PORT,LCD_RS_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RS_PIN,GPIO_PINSTATE_HIGH);
	
	/*Set RW LOW to Write on LCD */
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RW_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RW_PIN,GPIO_PINSTATE_LOW);
	
	/*Put the data in data port*/
	//LCD_DATA_PORT = data;
	MCAL_GPIO_WritePort(LCD_DATA_PORT,data);
	
	/*Put Enable pin high to show the data */
	LCD_KICK();
	#elif LCD_MODE == FOUR_BIT_MODE
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_7,GET_BIT(data,7));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_6,GET_BIT(data,6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_5,GET_BIT(data,5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_4,GET_BIT(data,4));
	
	/*Set RS LOW to send Command*/
//	SET_BIT(LCD_CONFIGE_PORT,LCD_RS_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RS_PIN,GPIO_PINSTATE_HIGH);

	/*Set RW LOW to Write on LCD */
	//CLR_BIT(LCD_CONFIGE_PORT,LCD_RW_PIN);
	MCAL_GPIO_WritePin(LCD_CONFIGE_PORT,LCD_RW_PIN,GPIO_PINSTATE_LOW);
	
	LCD_KICK();
	
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_7,GET_BIT(data,3));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_6,GET_BIT(data,2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_5,GET_BIT(data,1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT,GPIO_PIN_4,GET_BIT(data,0));
	
	LCD_KICK();
	#endif
}

/* To send display string on LCD */
void LCD_SEND_STRING(const char* data)
{
	unsigned char i =0 , count= 0;
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
void LCD_GO_TO_XY(unsigned char line,unsigned char column)
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
void LCD_SEND_NUMBER(int number)
{
	char str[7];
	sprintf(str,"%d",number);
	LCD_SEND_STRING(str);
}

/*Display Real numbers */
void LCD_SEND_REAL_NUMBER(double real_number)
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