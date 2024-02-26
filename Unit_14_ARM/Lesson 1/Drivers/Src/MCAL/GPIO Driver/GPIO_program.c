/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    GPIO			******************/
/*****************************************************************/
/*****************************************************************/
#include "GPIO_interface.h"

/*========================================================================================================
 * @Fun			:	GetConfigBit
 * @Brief		:	Get the number we want to shift bits in the registers according to parameter PinNumber
 * @Param[in]  	:	PinNumber: Number of Pin to be configured
 * @RetVal		:	None
 * @Note		:	This is static function for internal use only
 *========================================================================================================*/
static uint8_t GetConfigBit(uint8_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:	return 0;  break;
	case GPIO_PIN_1:	return 4;  break;
	case GPIO_PIN_2:	return 8;  break;
	case GPIO_PIN_3:	return 12; break;
	case GPIO_PIN_4:	return 16; break;
	case GPIO_PIN_5:	return 20; break;
	case GPIO_PIN_6:	return 24; break;
	case GPIO_PIN_7:	return 28; break;
	case GPIO_PIN_8:	return 0;  break;
	case GPIO_PIN_9:	return 4;  break;
	case GPIO_PIN_10:	return 8;  break;
	case GPIO_PIN_11:	return 12; break;
	case GPIO_PIN_12:	return 16; break;
	case GPIO_PIN_13:	return 20; break;
	case GPIO_PIN_14:	return 24; break;
	case GPIO_PIN_15:	return 28; break;
	default:			return 0;  break;
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_SetPinMode
 * @Brief		:	Initialize GPIOx pin direction according to the user inputs
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinMode:The mode of the pin according to @ref GPIO_PIN_MODE_define
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_SetPinMode(GPIO_t* GPIOx,uint8_t PinNumber,uint8_t PinMode)
{
	vuint32_t* configuration = NULL;

	/* Point to CRL or CRH According to PinNumber */
	configuration = (PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH ;

	/* Clear the Configuration of the bit first ( CNF & MODE ) */
	(*configuration) &= ~(0xf<<GetConfigBit(PinNumber));

	/* Put the configuration of the pin */
	(*configuration) |= (PinMode<<GetConfigBit(PinNumber));

	/* Check if the pin is input pull up */
	if(PinMode == GPIO_PIN_MODE_INPUT_PULL_UP)
	{
		/* Set the corresponding bit to 1 according to the specification */
		SET_BIT(GPIOx->ODR,PinNumber);
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_SetPortMode
 * @Brief		:	Initialize GPIOx port direction according to the user inputs
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PortMode:The mode of the port according to @ref GPIO_PORT_MODE_define
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_SetPortMode(GPIO_t* GPIOx,uint32_t PortMode)
{
	/* Set the all pins to the mode according to @ref GPIO_PORT_MODE_define Macros */
	GPIOx->CRL = PortMode;
	GPIOx->CRH = PortMode;

	if(PortMode == GPIO_PORT_MODE_INPUT_PULL_UP)
	{
		/* Set the ODR bits to 1 according to the specification */
		GPIOx->ODR = 0xFFFF;
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_WritePin
 * @Brief		:	Write on Pin in GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinNumber: Number of Pin to be accessed to write on it
 * @Param[in]  	:	PinValue: Value of Pin to be written according to @ref GPIO_PINSTATE_define
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_WritePin(GPIO_t* GPIOx,uint8_t PinNumber, uint8_t PinValue)
{
	if(PinValue == GPIO_PINSTATE_HIGH)
	{
		SET_BIT(GPIOx->ODR,PinNumber);
	}
	else
	{
		CLR_BIT(GPIOx->ODR,PinNumber);
	}
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_WritePort
 * @Brief		:	Write on Port in GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PortValue: Value of Port to be written
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_WritePort(GPIO_t* GPIOx,uint16_t PortValue)
{
	GPIOx->ODR = (uint32_t)PortValue;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_TogglePin
 * @Brief		:	Toggle Pin in GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinNumber: Value of Pin to be toggled
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_TogglePin(GPIO_t* GPIOx,uint8_t PinNumber)
{
	TOGGLE_BIT(GPIOx->ODR,PinNumber);
}


/*========================================================================================================
 * @Fun			:	MCAL_GPIO_TogglePort
 * @Brief		:	Toggle Port in GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_TogglePort(GPIO_t* GPIOx)
{
	GPIOx->ODR ^= 0xFFFF;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_ReadPin
 * @Brief		:	Read pin from GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinNumber: Number of Pin to be accessed to read it
 * @RetVal		:	The value of the pin according to @ref	GPIO_PIN_define
 *========================================================================================================*/
uint8_t MCAL_GPIO_ReadPin(GPIO_t* GPIOx,uint8_t PinNumber)
{
	uint8_t pinState = 0;
	pinState = GET_BIT(GPIOx->IDR,PinNumber);
	return pinState;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_ReadPort
 * @Brief		:	Read Port of GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @RetVal		:	The value of the port
 *========================================================================================================*/
uint16_t MCAL_GPIO_ReadPort(GPIO_t* GPIOx)
{
	uint16_t PortState = 0;
	PortState = (uint16_t)GPIOx->IDR;
	return PortState;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_LockPin
 * @Brief		:	Lock Pin in GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinNumber: Value of Pin to be locked
 * @RetVal		:	Status to ensure that the pin be locked or not according to @ref GPIO_LOCKSTATE_define
 *========================================================================================================*/
uint8_t MCAL_GPIO_LockPin(GPIO_t* GPIOx,uint8_t PinNumber)
{
	uint8_t LockState = GPIO_LOCKSTATE_NOERROR;
	/* Choosing the pin we want to lock */
	SET_BIT(GPIOx->LCKR,PinNumber);

	/* Writing the sequence in specs to lock the pin */
	/*=====================================================
	 * Write 1
	 * Write 0
	 * Write 1
	 * Read 0
	 * Read 1 (this read is optional but confirms that the lock is active)
	 *===================================================== */
	SET_BIT(GPIOx->LCKR,16);
	CLR_BIT(GPIOx->LCKR,16);
	SET_BIT(GPIOx->LCKR,16);
	GET_BIT(GPIOx->LCKR,16);
	if(GET_BIT(GPIOx->LCKR,16) == 0)
	{
		LockState = GPIO_LOCKSTATE_ERROR;
	}
	return LockState;
}
