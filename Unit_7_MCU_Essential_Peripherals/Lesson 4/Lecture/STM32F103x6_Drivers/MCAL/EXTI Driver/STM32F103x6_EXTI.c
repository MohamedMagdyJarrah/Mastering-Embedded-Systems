#include "STM32F103x6_EXTI.h"

/**************************************** Global Variables *****************************************/
void (*GP_IRQ_CallBackFunc[16])(void) ;			// Array of 16 pointer to function that return void and take nothing


/**************************************** Helper Macros *****************************************/
#define AFIO_GPIO_PORT_MAPPING(Port)		((Port==GPIOA)?0:\
		(Port==GPIOB)?1:\
				(Port==GPIOC)?2:\
						(Port==GPIOD)?3:0)

/**************************************** Private Functions *****************************************/
void NVIC_ENABLE(uint8_t EXTI_LINE)
{
	switch(EXTI_LINE)
	{
	case 0:
		NVIC_IRQ6_EXTI0_ENABLE;      break;
	case 1:
		NVIC_IRQ7_EXTI1_ENABLE;      break;
	case 2:
		NVIC_IRQ8_EXTI2_ENABLE;      break;
	case 3:
		NVIC_IRQ9_EXTI3_ENABLE;      break;
	case 4:
		NVIC_IRQ10_EXTI4_ENABLE;     break;
	case 5:case 6:case 7:case 8:case 9:
		NVIC_IRQ23_EXTI9_5_ENABLE;   break;
	case 10:case 11:case 12:case 13:case 14:case 15:
		NVIC_IRQ40_EXTI15_10_ENABLE; break;
	}
}

void NVIC_DISABLE(uint8_t EXTI_LINE)
{
	switch(EXTI_LINE)
	{
	case 0:
		NVIC_IRQ6_EXTI0_DISABLE;      break;
	case 1:
		NVIC_IRQ7_EXTI1_DISABLE;      break;
	case 2:
		NVIC_IRQ8_EXTI2_DISABLE;      break;
	case 3:
		NVIC_IRQ9_EXTI3_DISABLE;      break;
	case 4:
		NVIC_IRQ10_EXTI4_DISABLE;     break;
	case 5:case 6:case 7:case 8:case 9:
		NVIC_IRQ23_EXTI9_5_DISABLE;   break;
	case 10:case 11:case 12:case 13:case 14:case 15:
		NVIC_IRQ40_EXTI15_10_DISABLE; break;
	}
}


void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	/*********************** Configure GPIO Pin to be alternate input (floating input) *******************************/
	GPIO_PinConfig_t pinCfg;
	pinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	pinCfg.GPIO_Mode = GPIO_MODE_ALTERNATE_INPUT;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.EXTI_GPIO, &pinCfg);

	/*************************** Select the external interrupt line in the AFIO Registers *******************************/
	uint8_t AFIO_EXTICR_Index = (EXTI_Config->EXTI_PIN.EXTI_LINE) / 4;				// To get the register that contain the EXTI_LINE
	uint8_t AFIO_EXTICR_BitPosition = ((EXTI_Config->EXTI_PIN.EXTI_LINE) % 4) * 4;	// To get the position of the bits for specified EXTI_LINE

	// First Clear (Mask) the bits of the specified EXTI_LINE
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xf<<AFIO_EXTICR_BitPosition);
	// Configure the EXTI_LINE according to the port
	AFIO->EXTICR[AFIO_EXTICR_Index] |= (AFIO_GPIO_PORT_MAPPING(EXTI_Config->EXTI_PIN.EXTI_GPIO)<<AFIO_EXTICR_BitPosition);

	/*************************** Select the Trigger of the external interrupt from EXTI Registers *******************************/
	// First Reset the rising and falling edge configurations because this function we will use it in the update function too
	CLR_BIT(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_LINE);
	CLR_BIT(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_LINE);

	// Set the trigger case of the specified EXTI_LINE
	switch(EXTI_Config->Trigger_Case)
	{
	case EXTI_TRIGGER_RISING:
		SET_BIT(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_LINE);
		break;
	case EXTI_TRIGGER_FALLING:
		SET_BIT(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_LINE);
		break;
	case EXTI_TRIGGER_RISING_AND_FALLING:
		SET_BIT(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_LINE);
		SET_BIT(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_LINE);
		break;
	}

	/*************************** Initilizing the call back function sent by the user *******************************/
	GP_IRQ_CallBackFunc[EXTI_Config->EXTI_PIN.EXTI_LINE] = EXTI_Config->P_IRQ_CallBack;

	/******************** Enable/Disable the interrupt & Enable NVIC Controller for this interrupt *************************/
	/* Enable/disable EXTI */
	switch (EXTI_Config->IRQ_EN)
	{
	case EXTI_STATE_ENABLE:
		SET_BIT(EXTI->IMR,EXTI_Config->EXTI_PIN.EXTI_LINE);
		/* Enable NVIC Controller */
		NVIC_ENABLE(EXTI_Config->EXTI_PIN.EXTI_LINE);
		break;
	case EXTI_STATE_DISABLE:
		CLR_BIT(EXTI->IMR,EXTI_Config->EXTI_PIN.EXTI_LINE);
		/* Enable NVIC Controller */
		NVIC_DISABLE(EXTI_Config->EXTI_PIN.EXTI_LINE);
		break;
	}
}


/*========================================================================================================
 * @Fun			:	MCAL_EXTI_GPIO_Init
 * @Brief		:	Initialize EXTI by specifing the GPIO_PIN and the tigger condition and IRQ Callback function
 * @Param[in]  	:	EXTI_Config: Pointer to structure contain the configuration of the interrupt according to
 * 				    @ref EXTI_PIN_define, EXTI_TRIGGER_define, EXTI_STATE_define
 * @RetVal		:	None
 * @Note		:	Enable RCC Clock for AFIO and the coressponding GPIO
 *========================================================================================================*/
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/*========================================================================================================
 * @Fun			:	MCAL_EXTI_GPIO_DeInit
 * @Brief		:	Reset all external interrupt registers including NVIC IRQ MASK
 * @RetVal		:	None
 * @Note		:	None
 *========================================================================================================*/
void MCAL_EXTI_GPIO_DeInit(void)
{
	/* Resetting EXTI Registers */
	EXTI->IMR = 0;
	EXTI->EMR = 0;
	EXTI->RTSR = 0;
	EXTI->FTSR = 0;
	EXTI->SWIER = 0;
	// Clearing the pending flag of the interrupts (cleared by writing a ‘1’ into the bit)
	EXTI->PR = 0xFFFFFFFF;

	/* Disable EXTI IRQ From NVIC */
	NVIC_IRQ6_EXTI0_DISABLE		 ;
	NVIC_IRQ7_EXTI1_DISABLE		 ;
	NVIC_IRQ8_EXTI2_DISABLE		 ;
	NVIC_IRQ9_EXTI3_DISABLE		 ;
	NVIC_IRQ10_EXTI4_DISABLE	 ;
	NVIC_IRQ23_EXTI9_5_DISABLE	 ;
	NVIC_IRQ40_EXTI15_10_DISABLE ;
}

/*========================================================================================================
 * @Fun			:	MCAL_EXTI_GPIO_Update
 * @Brief		:	Initialize EXTI by specifing the GPIO_PIN and the tigger condition and IRQ Callback function
 * @Param[in]  	:	EXTI_Config: Pointer to structure contain the configuration of the interrupt according to
 * 				    @ref EXTI_PIN_define, EXTI_TRIGGER_define, EXTI_STATE_define
 * @RetVal		:	None
 * @Note		:	Enable RCC Clock for AFIO and the coressponding GPIO
 *========================================================================================================*/
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


/******************************************************************************
 * 								ISR Functions
 * ****************************************************************************/
void EXTI0_IRQHandler(void)
{
	// First Clear the pending flag to avoid staying in the isr forever (By Setting 1 to the bit in PR Register)
	SET_BIT(EXTI->PR,0);

	// Calling the callback function that assigned by the user
	GP_IRQ_CallBackFunc[0]();
}

void EXTI1_IRQHandler(void)
{
	SET_BIT(EXTI->PR,1);
	GP_IRQ_CallBackFunc[1]();
}

void EXTI2_IRQHandler(void)
{
	SET_BIT(EXTI->PR,2);
	GP_IRQ_CallBackFunc[2]();
}

void EXTI3_IRQHandler(void)
{
	SET_BIT(EXTI->PR,3);
	GP_IRQ_CallBackFunc[3]();
}

void EXTI4_IRQHandler(void)
{
	SET_BIT(EXTI->PR,4);
	GP_IRQ_CallBackFunc[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1<<5)) {	SET_BIT(EXTI->PR,5); GP_IRQ_CallBackFunc[5](); }
	if(EXTI->PR & (1<<6)) {	SET_BIT(EXTI->PR,6); GP_IRQ_CallBackFunc[6](); }
	if(EXTI->PR & (1<<7)) {	SET_BIT(EXTI->PR,7); GP_IRQ_CallBackFunc[7](); }
	if(EXTI->PR & (1<<8)) { SET_BIT(EXTI->PR,8); GP_IRQ_CallBackFunc[8](); }
	if(EXTI->PR & (1<<9)) { SET_BIT(EXTI->PR,9); GP_IRQ_CallBackFunc[9](); }
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<10)) { SET_BIT(EXTI->PR,10); GP_IRQ_CallBackFunc[10](); }
	if(EXTI->PR & (1<<11)) { SET_BIT(EXTI->PR,11); GP_IRQ_CallBackFunc[11](); }
	if(EXTI->PR & (1<<12)) { SET_BIT(EXTI->PR,12); GP_IRQ_CallBackFunc[12](); }
	if(EXTI->PR & (1<<13)) { SET_BIT(EXTI->PR,13); GP_IRQ_CallBackFunc[13](); }
	if(EXTI->PR & (1<<14)) { SET_BIT(EXTI->PR,14); GP_IRQ_CallBackFunc[14](); }
	if(EXTI->PR & (1<<15)) { SET_BIT(EXTI->PR,15); GP_IRQ_CallBackFunc[15](); }
}
