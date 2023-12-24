/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    DIO				******************/
/*****************************************************************/
/*****************************************************************/
#include "DIO_interface.h"

/*========================================================================================================
 * @Fun			:	MCAL_DIO_SetPinDirection
 * @Brief		:	Set the direction of the pin received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @Param[in]  	:	Copy_Pin: The number of pin will configure (DIO_PINx) (x = 0,1,2,3,4,5,6,7)
 * @Param[in]  	:	Copy_Direction: The direction of pin wanted (DIO_PIN_x) (x = INPUT_FLOATING,INPUT_PULL_UP,OUTPUT)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_SetPinDirection(uint8 Copy_Port, uint8 Copy_Pin, uint8 Copy_Direction)
{
	uint8 Local_ErrorState = NO_ERROR;

	if(Copy_Pin <= DIO_PIN7 )
	{
		if(Copy_Direction == DIO_PIN_INPUT_FLOATING)
		{
			switch(Copy_Port)
			{
			case DIO_PORTA:	CLR_BIT(DDRA,Copy_Pin);				break;
			case DIO_PORTB:	CLR_BIT(DDRB,Copy_Pin);				break;
			case DIO_PORTC:	CLR_BIT(DDRC,Copy_Pin);				break;
			case DIO_PORTD:	CLR_BIT(DDRD,Copy_Pin);				break;
			default:		Local_ErrorState = ERROR_DETECTED;	break;
			}
		}
		else if (Copy_Direction == DIO_PIN_INPUT_PULL_UP)
		{
			switch(Copy_Port)
			{
			case DIO_PORTA:	CLR_BIT(DDRA,Copy_Pin); SET_BIT(PORTA,Copy_Pin);	break;
			case DIO_PORTB:	CLR_BIT(DDRB,Copy_Pin); SET_BIT(PORTB,Copy_Pin);	break;
			case DIO_PORTC:	CLR_BIT(DDRC,Copy_Pin); SET_BIT(PORTC,Copy_Pin);	break;
			case DIO_PORTD:	CLR_BIT(DDRD,Copy_Pin); SET_BIT(PORTD,Copy_Pin);	break;
			default:		Local_ErrorState = ERROR_DETECTED;					break;
			}
		}
		else if (Copy_Direction == DIO_PIN_OUTPUT)
		{
			switch(Copy_Port)
			{
			case DIO_PORTA:	SET_BIT(DDRA,Copy_Pin); 			break;
			case DIO_PORTB:	SET_BIT(DDRB,Copy_Pin); 			break;
			case DIO_PORTC:	SET_BIT(DDRC,Copy_Pin); 			break;
			case DIO_PORTD:	SET_BIT(DDRD,Copy_Pin); 			break;
			default:		Local_ErrorState = ERROR_DETECTED;	break;
			}
		}
		else
		{
			Local_ErrorState = ERROR_DETECTED;
		}
	}
	else
	{
		Local_ErrorState = ERROR_DETECTED;
	}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_DIO_SetPortDirection
 * @Brief		:	Set the direction of the port received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @Param[in]  	:	Copy_Direction: The direction of pin wanted (DIO_PORT_x) (x = INPUT_FLOATING,INPUT_PULL_UP,OUTPUT)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_SetPortDirection(uint8 Copy_Port, uint8 Copy_Direction)
{
	uint8 Local_ErrorState = NO_ERROR;
	if(Copy_Direction == DIO_PORT_INPUT_FLOATING)
	{
		switch (Copy_Port)
		{
		case DIO_PORTA:	DDRA = 0x00;    break;
		case DIO_PORTB:	DDRB = 0x00;    break;
		case DIO_PORTC:	DDRC = 0x00;    break;
		case DIO_PORTD:	DDRD = 0x00;    break;
		default:		Local_ErrorState = ERROR_DETECTED;	break;
		}
	}
	else if (Copy_Direction == DIO_PORT_INPUT_PULL_UP)
	{
		switch (Copy_Port)
		{
		case DIO_PORTA:	DDRA = 0x00;  PORTA = 0xFF;         break;
		case DIO_PORTB:	DDRB = 0x00;  PORTB = 0xFF;         break;
		case DIO_PORTC:	DDRC = 0x00;  PORTC = 0xFF;         break;
		case DIO_PORTD:	DDRD = 0x00;  PORTD = 0xFF;         break;
		default:		Local_ErrorState = ERROR_DETECTED;	break;
		}
	}
	else if (Copy_Direction == DIO_PORT_OUTPUT)
	{
		switch (Copy_Port)
		{
		case DIO_PORTA:	DDRA = 0xFF;    break;
		case DIO_PORTB:	DDRB = 0xFF;    break;
		case DIO_PORTC:	DDRC = 0xFF;    break;
		case DIO_PORTD:	DDRD = 0xFF;    break;
		default:		Local_ErrorState = ERROR_DETECTED;	break;
		}
	}
	else
	{
		Local_ErrorState = ERROR_DETECTED;
	}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_DIO_SetPinValue
 * @Brief		:	Set the state of the pin received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @Param[in]  	:	Copy_Pin: The number of pin will configure (DIO_PINx) (x = 0,1,2,3,4,5,6,7)
 * @Param[in]  	:	Copy_Value: The state of pin wanted (DIO_PIN_x) (x = HIGH,LOW)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_SetPinValue(uint8 Copy_Port, uint8 Copy_Pin, uint8 Copy_Value)
{
	uint8 Local_ErrorState = NO_ERROR;

	if(Copy_Pin <= DIO_PIN7 )
	{
		if(Copy_Value == DIO_PIN_LOW)
		{
			switch(Copy_Port)
			{
			case DIO_PORTA:	CLR_BIT(PORTA,Copy_Pin);		    break;
			case DIO_PORTB:	CLR_BIT(PORTB,Copy_Pin);		    break;
			case DIO_PORTC:	CLR_BIT(PORTC,Copy_Pin);		    break;
			case DIO_PORTD:	CLR_BIT(PORTD,Copy_Pin);		    break;
			default:		Local_ErrorState = ERROR_DETECTED;	break;
			}
		}
		else if (Copy_Value == DIO_PIN_HIGH)
		{
			switch(Copy_Port)
			{
			case DIO_PORTA:	SET_BIT(PORTA,Copy_Pin); 			break;
			case DIO_PORTB:	SET_BIT(PORTB,Copy_Pin); 			break;
			case DIO_PORTC:	SET_BIT(PORTC,Copy_Pin); 			break;
			case DIO_PORTD:	SET_BIT(PORTD,Copy_Pin); 			break;
			default:		Local_ErrorState = ERROR_DETECTED;	break;
			}
		}
		else
		{
			Local_ErrorState = ERROR_DETECTED;
		}
	}
	else
	{
		Local_ErrorState = ERROR_DETECTED;
	}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_DIO_SetPortValue
 * @Brief		:	Set the state of the port received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @Param[in]  	:	Copy_Value: The state of pin wanted (DIO_PIN_x) (x = HIGH,LOW)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_SetPortValue(uint8 Copy_Port, uint8 Copy_Value)
{
	uint8 Local_ErrorState = NO_ERROR;

		switch (Copy_Port)
		{
		case DIO_PORTA:	PORTA = Copy_Value;    break;
		case DIO_PORTB:	PORTB = Copy_Value;    break;
		case DIO_PORTC:	PORTC = Copy_Value;    break;
		case DIO_PORTD:	PORTD = Copy_Value;    break;
		default:		Local_ErrorState = ERROR_DETECTED;	break;
		}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_DIO_TogglePinValue
 * @Brief		:	Toggle the pin received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @Param[in]  	:	Copy_Pin: The number of pin will configure (DIO_PINx) (x = 0,1,2,3,4,5,6,7)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_TogglePinValue(uint8 Copy_Port, uint8 Copy_Pin)
{
	uint8 Local_ErrorState = NO_ERROR;

	if(Copy_Pin <= DIO_PIN7 )
	{
		switch(Copy_Port)
		{
		case DIO_PORTA:	TOGGLE_BIT(PORTA,Copy_Pin);		    break;
		case DIO_PORTB:	TOGGLE_BIT(PORTB,Copy_Pin);		    break;
		case DIO_PORTC:	TOGGLE_BIT(PORTC,Copy_Pin);		    break;
		case DIO_PORTD:	TOGGLE_BIT(PORTD,Copy_Pin);		    break;
		default:		Local_ErrorState = ERROR_DETECTED;	break;
		}
	}
	else
	{
		Local_ErrorState = ERROR_DETECTED;
	}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_DIO_TogglePortValue
 * @Brief		:	Toggle the port received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_TogglePortValue(uint8 Copy_Port)
{
	uint8 Local_ErrorState = NO_ERROR;

	switch(Copy_Port)
	{
	case DIO_PORTA:	PORTA ^= 0xff;		    break;
	case DIO_PORTB:	PORTB ^= 0xff;		    break;
	case DIO_PORTC:	PORTC ^= 0xff;		    break;
	case DIO_PORTD:	PORTD ^= 0xff;		    break;
	default:		Local_ErrorState = ERROR_DETECTED;	break;
	}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_DIO_GetPinValue
 * @Brief		:	Set the state of the pin received from the user
 * @Param[in]  	:	Copy_Port: The port of the pin we will configure (DIO_PORTx) (x = A,B,C,D)
 * @Param[in]  	:	Copy_Pin: The number of pin will configure (DIO_PINx) (x = 0,1,2,3,4,5,6,7)
 * @Param[in]  	:	Copy_Value: Pointer to a variable to save the pin's state
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_DIO_GetPinValue(uint8 Copy_Port, uint8 Copy_Pin, uint8* Copy_PinValue)
{
	uint8 Local_ErrorState = NO_ERROR;

	if(Copy_Pin <= DIO_PIN7 )
	{

		switch(Copy_Port)
		{
		case DIO_PORTA:	*Copy_PinValue = GET_BIT(PINA,Copy_Pin);	    break;
		case DIO_PORTB:	*Copy_PinValue = GET_BIT(PINB,Copy_Pin);	    break;
		case DIO_PORTC:	*Copy_PinValue = GET_BIT(PINC,Copy_Pin);	    break;
		case DIO_PORTD:	*Copy_PinValue = GET_BIT(PIND,Copy_Pin);	    break;
		default:		Local_ErrorState = ERROR_DETECTED;				break;
		}
	}
	else
	{
		Local_ErrorState = ERROR_DETECTED;
	}

	return Local_ErrorState;
}
