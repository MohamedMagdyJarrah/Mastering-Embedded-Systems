#include "STM32F103x6_GPIO.h"

/*========================================================================================================
 * @Fun			:	GetConfigBit
 * @Brief		:	Get the number we want to shift bits in the regiesters according to parameter PinNumber
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
 * @Fun			:	MCAL_GPIO_Init
 * @Brief		:	Initialize GPIOx according to the specified parameter in PinConfig
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinConfig: pointer to structure that contain all GPIO configuration information
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_Init(GPIO_t* GPIOx, GPIO_PinConfig_t* PinConfig)
{
	vuint32_t* configuration = NULL;

	if(PinConfig->GPIO_PinNumber == GPIO_PIN_ALL)
	{
		/* Clear the Configuration of all bits first ( CNF & MODE ) */
		GPIOx->CRL = 0x0;
		GPIOx->CRH = 0x0;

		/* Put the configuration in all pins */
		GPIOx->CRL = (uint16_t)PinConfig->GPIO_Mode;
		GPIOx->CRH = (uint16_t)PinConfig->GPIO_Mode;

		/* Check if the pins is input pull */
		if(PinConfig->GPIO_Mode == GPIO_MODE_PORT_INPUT_PULL_UP)
		{
			GPIOx->ODR = (uint32_t)0xff;
		}
	}
	else
	{
		/* Point to CRL or CRH According to PinNumber */
		configuration = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH ;

		/* Clear the Configuration of the bit first ( CNF & MODE ) */
		(*configuration) &= ~(0xf<<GetConfigBit(PinConfig->GPIO_PinNumber));

		/* Put the configration of the pin */
		(*configuration) |= (PinConfig->GPIO_Mode<<GetConfigBit(PinConfig->GPIO_PinNumber));

		/* Check if the pin is input pull up */
		if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PULL_UP)
		{
			/* Set the coressponding bit to 1 according to the specification */
			SET_BIT(GPIOx->ODR,PinConfig->GPIO_PinNumber);
		}
	}


}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_Init_Prebuild
 * @Brief		:	Initialize GPIOx according to the configuration files
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_Init_Prebuild(GPIO_t* GPIOx)
{
	//	GPIOx->CRL =;
	//	GPIOx->CRH =;
	//
	//	GPIOx->ODR =;
	//	GPIOx->LCKR =;
}

/*========================================================================================================
 * @Fun			:	MCAL_GPIO_DeInit
 * @Brief		:	Reset GPIOx pins
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_GPIO_DeInit(GPIO_t* GPIOx)
{
	/* Return all the registers to its Reset value */
	//	GPIOx->CRL =  0x44444444;
	//	GPIOx->CRH =  0x44444444;
	//	GPIOx->ODR =  0x0;
	//	GPIOx->BSRR = 0x0;
	//	GPIOx->BRR =  0x0;
	//	GPIOx->LCKR = 0x0;

	/* It will be better to reset the peripheral using RCC (Reset Controller) */
	/* The peripheral will reset when I set then clear its bit in APB2RSTR Register */
	if(GPIOx == GPIOA)
	{
		SET_BIT(RCC->APB2RSTR,2);
		CLR_BIT(RCC->APB2RSTR,2);
	}
	else if(GPIOx == GPIOB)
	{
		SET_BIT(RCC->APB2RSTR,3);
		CLR_BIT(RCC->APB2RSTR,3);
	}
	else if(GPIOx == GPIOC)
	{
		SET_BIT(RCC->APB2RSTR,4);
		CLR_BIT(RCC->APB2RSTR,4);
	}
	else if(GPIOx == GPIOD)
	{
		SET_BIT(RCC->APB2RSTR,5);
		CLR_BIT(RCC->APB2RSTR,5);
	}
	else if(GPIOx == GPIOE)
	{
		SET_BIT(RCC->APB2RSTR,6);
		CLR_BIT(RCC->APB2RSTR,6);
	}
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
	uint8_t pinState =0;
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
	uint16_t PortState = (uint16_t)GPIOx->IDR;
	return PortState;
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
	GPIOx->ODR = (GPIOx->ODR & 0xffff0000) | PortValue;;

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
 * @Fun			:	MCAL_GPIO_LockPin
 * @Brief		:	Lock Pin in GPIOx
 * @Param[in]  	:	GPIOx: Where x can be (A...E depending on the device)
 * @Param[in]  	:	PinNumber: Value of Pin to be locked
 * @RetVal		:	Status to ensure that the pin be locked or not according to @ref GPIO_LOCKSTATE_define
 *========================================================================================================*/
uint8_t MCAL_GPIO_LockPin(GPIO_t* GPIOx,uint8_t PinNumber)
{
	uint8_t LockState = GPIO_LOCKSTATE_NOERROR;
	/* Temp variable to read only the lock pin */
	uint8_t x=0;
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
	x = GET_BIT(GPIOx->LCKR,16);
	if(GET_BIT(GPIOx->LCKR,16) == 0)
	{
		LockState = GPIO_LOCKSTATE_ERROR;
	}
	return LockState;
}
