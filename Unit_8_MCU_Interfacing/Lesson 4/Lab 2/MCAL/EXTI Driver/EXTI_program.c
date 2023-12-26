/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    EXTI			******************/
/*****************************************************************/
/*****************************************************************/

#include "EXTI_interface.h"

/* Global pointer to function to use it with callback functions */
void (*EXTI_pvINT0_ISR_Func)(void) = NULL;
void (*EXTI_pvINT1_ISR_Func)(void) = NULL;
void (*EXTI_pvINT2_ISR_Func)(void) = NULL;


/*========================================================================================================
 * @Fun			:	EXTI_INTxInit
 * @Brief		:	Initialize the EXTI for INTx according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_EXTI_INT0Init(void)
{
	/*Set Sense Control for INT0*/
#if (INT0_SENSE_CONTROL == EXTI_LOW_LEVEL) || (INT0_SENSE_CONTROL == EXTI_ON_CHANGE) \
		|| (INT0_SENSE_CONTROL == EXTI_FALLING_EDGE) || (INT0_SENSE_CONTROL == EXTI_RISING_EDGE)
	MCUCR |= INT0_SENSE_CONTROL;
#else
#error "Warning INT0_SENSE_CONTROL Configuration Option"
#endif

	/*Peripheral (Specific) interrupt for INT0 and The Interrupt controller of the MCU */
#if INT0_INITIAL_STATE == EXTI_ENABLED
	SET_BIT(GICR,GICR_INT0);
	SET_BIT(SREG,SREG_I);
#elif INT0_INITIAL_STATE == EXTI_DISABLED
	CLR_BIT(GICR,GICR_INT0);
	CLR_BIT(SREG,SREG_I);
#else
#error "Warning INT0_INITIAL_STATE Configuration Option"
#endif
}

void MCAL_EXTI_INT1Init(void)
{
	/*Set Sense Control for INT1*/
#if (INT1_SENSE_CONTROL == EXTI_LOW_LEVEL) || (INT1_SENSE_CONTROL == EXTI_ON_CHANGE) \
		|| (INT1_SENSE_CONTROL == EXTI_FALLING_EDGE) || (INT1_SENSE_CONTROL == EXTI_RISING_EDGE)
	MCUCR |= (INT1_SENSE_CONTROL<<2);
#else
#error "Warning INT1_SENSE_CONTROL Configuration Option"
#endif

	/*Peripheral (Specific) interrupt for INT1*/
#if INT1_INITIAL_STATE == EXTI_ENABLED
	SET_BIT(GICR,GICR_INT1);
	SET_BIT(SREG,SREG_I);
#elif INT1_INITIAL_STATE == EXTI_DISABLED
	CLR_BIT(GICR,GICR_INT1);
	CLR_BIT(SREG,SREG_I);
#else
#error "Warning INT1_INITIAL_STATE Configuration Option"
#endif

}

void MCAL_EXTI_INT2Init(void)
{
	/*Set Sense Control for INT2*/
#if INT2_SENSE_CONTROL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_SENSE_CONTROL == EXTI_RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error "Warning INT2_SENSE_CONTROL Configuration Option"
#endif

	/*Peripheral (Specific) interrupt for INT2*/
#if INT2_INITIAL_STATE == EXTI_ENABLED
	SET_BIT(GICR,GICR_INT2);
	SET_BIT(SREG,SREG_I);
#elif INT2_INITIAL_STATE == EXTI_DISABLED
	CLR_BIT(GICR,GICR_INT2);
	CLR_BIT(SREG,SREG_I);
#else
#error "Warning INT2_INITIAL_STATE Configuration Option"
#endif
}

/*========================================================================================================
 * @Fun			:	MCAL_EXTI_INTSetSenseControl
 * @Brief		:	Set the sense control of the interrupt according to Post-Build Configurations
 * @Param[in]  	:	Copy_INT: The Interrupt pin will be configured which is INTx where x is (0,1,2)
 * @Param[in]  	:	Copy_SenseControl: The sense control chose by the user according to the choices given in interface file
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_EXTI_INTSetSenseControl(uint8 Copy_INT ,uint8 Copy_SenseControl)
{
	uint8 Local_ErrorState = NO_ERROR;

	if((Copy_SenseControl == EXTI_LOW_LEVEL) || (Copy_SenseControl == EXTI_ON_CHANGE)
			|| (Copy_SenseControl == EXTI_FALLING_EDGE) || (Copy_SenseControl == EXTI_RISING_EDGE) )
	{
		switch(Copy_INT)
		{
		case INT0: MCUCR |= Copy_SenseControl; 	 break;
		case INT1: MCUCR |= (Copy_SenseControl<<2); break;
		case INT2:
			if(Copy_SenseControl == EXTI_FALLING_EDGE)
			{
				CLR_BIT(MCUCSR,MCUCSR_ISC2);
			}
			else if (Copy_SenseControl == EXTI_RISING_EDGE)
			{
				SET_BIT(MCUCSR,MCUCSR_ISC2);
			}
			break;
		default: Local_ErrorState = ERROR_DETECTED; break;
		}
	}
	else
	{
		Local_ErrorState = ERROR_DETECTED;
	}

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_EXTI_INTEnable
 * @Brief		:	Enable the external interrupt according to Post-Build Configurations
 * @Param[in]  	:	Copy_INT: The Interrupt pin will be configured which is INTx where x is (0,1,2)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_EXTI_INTEnable(uint8 Copy_INT)
{
	uint8 Local_ErrorState = NO_ERROR;

	switch (Copy_INT)
	{
	case INT0: SET_BIT(GICR,GICR_INT0); 		break;
	case INT1: SET_BIT(GICR,GICR_INT1); 		break;
	case INT2: SET_BIT(GICR,GICR_INT2); 		break;
	default: Local_ErrorState = ERROR_DETECTED; break;
	}
	/* Enable the general interrupt controller */
	SET_BIT(SREG,SREG_I);

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_EXTI_INTDisable
 * @Brief		:	Disable the external interrupt according to Post-Build Configurations
 * @Param[in]  	:	Copy_INT: The Interrupt pin will be configured which is INTx where x is (0,1,2)
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_EXTI_INTDisable(uint8 Copy_INT)
{
	uint8 Local_ErrorState = NO_ERROR;

	switch (Copy_INT)
	{
	case INT0: CLR_BIT(GICR,GICR_INT0); 		break;
	case INT1: CLR_BIT(GICR,GICR_INT1); 		break;
	case INT2: CLR_BIT(GICR,GICR_INT2); 		break;
	default: Local_ErrorState = ERROR_DETECTED; break;
	}
	/* Disable the general interrupt controller */
	CLR_BIT(SREG,SREG_I);

	return Local_ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_EXTI_INTxSetCallBack
 * @Brief		:	Set the callback function that will be called when the interrupt occurs
 * @Param[in]  	:	Copy_pvINTx_ISR: pointer to function to save the function we will call in ISR
 * @RetVal		:	The Error status of the function
 *========================================================================================================*/
uint8 MCAL_EXTI_INT0SetCallBack(void (*Copy_pvINT0_ISR)(void))
{
	uint8 Local_ErrorState = NO_ERROR;

	if (Copy_pvINT0_ISR != NULL)
	{
		EXTI_pvINT0_ISR_Func = Copy_pvINT0_ISR;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

uint8 MCAL_EXTI_INT1SetCallBack(void (*Copy_pvINT1_ISR)(void))
{
	uint8 Local_ErrorState = NO_ERROR;

	if (Copy_pvINT1_ISR != NULL)
	{
		EXTI_pvINT1_ISR_Func = Copy_pvINT1_ISR;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

uint8 MCAL_EXTI_INT2SetCallBack(void (*Copy_pvINT2_ISR)(void))
{
	uint8 Local_ErrorState = NO_ERROR;

	if (Copy_pvINT2_ISR != NULL)
	{
		EXTI_pvINT2_ISR_Func = Copy_pvINT2_ISR;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

/*=======================================================================================
 * 										"EXTI ISRs"
 *=======================================================================================*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	if(EXTI_pvINT0_ISR_Func != NULL)
	{
		EXTI_pvINT0_ISR_Func();
	}
	else
	{
		/* Do Nothing */
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pvINT1_ISR_Func != NULL)
	{
		EXTI_pvINT1_ISR_Func();
	}
	else
	{
		/* Do Nothing */
	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_pvINT2_ISR_Func != NULL)
	{
		EXTI_pvINT2_ISR_Func();
	}
	else
	{
		/* Do Nothing */
	}
}
