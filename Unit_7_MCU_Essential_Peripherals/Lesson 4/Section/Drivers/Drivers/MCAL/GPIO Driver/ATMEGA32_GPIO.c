#include "ATMEGA32_GPIO.h"

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_Init
 * @Brief		:	Initialize GPIOx according to the specified parameter in PinConfig
 * @Param[in]  	:	GPIOx: Where x can be (A...D) based on @ref GPIOx
 * @Param[in]  	:	PinConfig: pointer to structure that contain all GPIO configuration information
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_Init(uint8_t GPIOx, GPIO_PinConfig_t* PinConfig)
{
	if (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT)
	{
		switch(GPIOx)
		{
			case GPIOA:	SET_BIT(DDRA,PinConfig->GPIO_PinNumber); break;
			case GPIOB:	SET_BIT(DDRB,PinConfig->GPIO_PinNumber); break;
			case GPIOC:	SET_BIT(DDRC,PinConfig->GPIO_PinNumber); break;
			case GPIOD:	SET_BIT(DDRD,PinConfig->GPIO_PinNumber); break;
		}
	}
	else if (PinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLOATING)
	{
		switch(GPIOx)
		{
			case GPIOA:	CLR_BIT(DDRA,PinConfig->GPIO_PinNumber); break;
			case GPIOB:	CLR_BIT(DDRB,PinConfig->GPIO_PinNumber); break;
			case GPIOC:	CLR_BIT(DDRC,PinConfig->GPIO_PinNumber); break;
			case GPIOD:	CLR_BIT(DDRD,PinConfig->GPIO_PinNumber); break;
		}
	}
	else if (PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PULL_UP)
	{
		switch(GPIOx)
		{
			case GPIOA:	
				CLR_BIT(DDRA,PinConfig->GPIO_PinNumber);
				SET_BIT(PORTA,PinConfig->GPIO_PinNumber);
				break;
			case GPIOB:	
				CLR_BIT(DDRB,PinConfig->GPIO_PinNumber);
				SET_BIT(PORTB,PinConfig->GPIO_PinNumber); 
				break;
			case GPIOC:	
				CLR_BIT(DDRC,PinConfig->GPIO_PinNumber);
				SET_BIT(PORTC,PinConfig->GPIO_PinNumber); 
				break;
			case GPIOD:	
				CLR_BIT(DDRD,PinConfig->GPIO_PinNumber);
				SET_BIT(PORTD,PinConfig->GPIO_PinNumber); 
				break;
		}
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_PORT_Init
 * @Brief		:	Initialize GPIOx Port according to the specified parameter in GPIO_MODE
 * @Param[in]  	:	GPIOx: Where x can be (A...D) based on @ref GPIOx
 * @Param[in]  	:	GPIO_MODE: the mode of the port you want according to @ref GPIO_MODE_define 
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_PortInit(uint8_t GPIOx,uint8_t GPIO_MODE)
{
	if(GPIO_MODE == GPIO_MODE_OUTPUT)
	{
		switch(GPIOx)
		{
			case GPIOA: DDRA = 0xff; break;
			case GPIOB: DDRB = 0xff; break;
			case GPIOC: DDRC = 0xff; break;
			case GPIOD: DDRD = 0xff; break;
		}
	}
	else if(GPIO_MODE == GPIO_MODE_INPUT_FLOATING)
	{
		switch(GPIOx)
		{
			case GPIOA: DDRA = 0x00; break;
			case GPIOB: DDRB = 0x00; break;
			case GPIOC: DDRC = 0x00; break;
			case GPIOD: DDRD = 0x00; break;
		}
	}
	else if(GPIO_MODE_INPUT_PULL_UP)
	{
		switch(GPIOx)
		{
			case GPIOA: DDRA = 0x00; PORTA = 0xff; break;
			case GPIOB: DDRB = 0x00; PORTB = 0xff; break;
			case GPIOC: DDRC = 0x00; PORTC = 0xff; break;
			case GPIOD: DDRD = 0x00; PORTD = 0xff; break;
		}
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_DeInit
 * @Brief		:	Reset GPIOx Pins
 * @Param[in]  	:	GPIOx: Where x can be (A...D) based on @ref GPIOx
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_DeInit(uint8_t GPIOx)
{
	switch(GPIOx)
	{
		case GPIOA:
		PORTA = 0x0;
		DDRA =	0x0;
		break;
		case GPIOB:
		PORTB = 0x0;
		DDRB =	0x0;
		break;
		case GPIOC:
		PORTC = 0x0;
		DDRC =	0x0;
		break;
		case GPIOD:
		PORTD = 0x0;
		DDRD =	0x0;
		break;
	}	
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_ReadPin
 * @Brief		:	Read GPIOx Pin
 * @Param[in]  	:	GPIOx: Where x can be (A...D) based on @ref GPIOx
 * @Param[in]  	:	PinNumber: number of the pin you want to read according to @ref GPIO_PIN_define
 * @RetVal		:	The state of the pin we read
 *========================================================================================================*/
uint8_t MCAL_GPIO_ReadPin(uint8_t GPIOx,uint8_t PinNumber)
{
	uint8_t PinState = 0;
	switch(GPIOx)
	{
		case GPIOA:	PinState = GET_BIT(PINA,PinNumber); break;
		case GPIOB:	PinState = GET_BIT(PINB,PinNumber); break;
		case GPIOC:	PinState = GET_BIT(PINC,PinNumber); break;
		case GPIOD:	PinState = GET_BIT(PIND,PinNumber); break;
	}
	return PinState;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_ReadPort
 * @Brief		:	Read GPIOx Port
 * @Param[in]  	:	GPIOx: Where x can be (A...D) based on @ref GPIOx
 * @RetVal		:	The state of the Port we read
 *========================================================================================================*/
uint8_t MCAL_GPIO_ReadPort(uint8_t GPIOx)
{
	uint8_t PortValue = 0;
	switch(GPIOx)
	{
		case GPIOA:	PortValue = PORTA; break;
		case GPIOB:	PortValue = PORTB; break;
		case GPIOC:	PortValue = PORTC; break;
		case GPIOD:	PortValue = PORTD; break;
	}
	return PortValue;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_WritePin
 * @Brief		:	Write on GPIOx Pin
 * @Param[in]  	:	GPIOx: Where x can be (A...D) based on @ref GPIOx
 * @Param[in]  	:	PinNumber: number of the pin you want to write on it according to @ref GPIO_PIN_define
 * @Param[in]  	:	PinValue: Value of the pin according to @ref GPIO_PINSTATE_define
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_WritePin(uint8_t GPIOx,uint8_t PinNumber, uint8_t PinValue)
{
	if(PinValue == GPIO_PINSTATE_HIGH)
	{
		switch(GPIOx)
		{
			case GPIOA:	SET_BIT(PORTA,PinNumber); break;
			case GPIOB:	SET_BIT(PORTB,PinNumber); break;
			case GPIOC:	SET_BIT(PORTC,PinNumber); break;
			case GPIOD:	SET_BIT(PORTD,PinNumber); break;
		}
	}
	else if(PinValue == GPIO_PINSTATE_LOW)
	{
		switch(GPIOx)
		{
			case GPIOA:	CLR_BIT(PORTA,PinNumber); break;
			case GPIOB:	CLR_BIT(PORTB,PinNumber); break;
			case GPIOC:	CLR_BIT(PORTC,PinNumber); break;
			case GPIOD:	CLR_BIT(PORTD,PinNumber); break;
		}
	}	
}

void MCAL_GPIO_WritePort(uint8_t GPIOx,uint16_t PortValue)
{
	switch(GPIOx)
	{
		case GPIOA:	PORTA = PortValue; break;
		case GPIOB:	PORTB = PortValue; break;
		case GPIOC:	PORTC = PortValue; break;
		case GPIOD:	PORTD = PortValue; break;
	}
}

void MCAL_GPIO_TogglePin(uint8_t GPIOx,uint8_t PinNumber)
{
	switch(GPIOx)
	{
		case GPIOA:	TOGGLE_BIT(PORTA,PinNumber); break;
		case GPIOB:	TOGGLE_BIT(PORTB,PinNumber); break;
		case GPIOC:	TOGGLE_BIT(PORTC,PinNumber); break;
		case GPIOD:	TOGGLE_BIT(PORTD,PinNumber); break;
	}
}