/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************************************************************/
/*****************************************************************/
#include "Timers_interface.h"

/*=============================================================================================
 * 										Global Variables
 *=============================================================================================*/
uint32 G_NumberOfOverflows = 0;
void (*G_pv_overflow_CallbackFunc)(void) = NULL;
void (*G_pv_compareMatch_CallbackFunc)(void) = NULL;
uint8 TIMER0_STATE = IDLE;

/*========================================================================================================
 * @Fun			:	getPrescaler
 * @Brief		:	Private function to get the value of the prescaler
 * @Param 		: 	prescaler: Value of the Prescaler Macros
 * @RetVal		:	Prescaler Value
 *========================================================================================================*/
static uint16 getPrescaler(uint8 prescaler)
{
	uint16 desiredPrescaler = 1;

	switch(prescaler)
	{
	case NO_PRESCALING:      desiredPrescaler = 1;    break;
	case PRESCALER_8_BIT:    desiredPrescaler = 8;    break;
	case PRESCALER_64_BIT:   desiredPrescaler = 64;   break;
	case PRESCALER_256_BIT:  desiredPrescaler = 256;  break;
	case PRESCALER_1024_BIT: desiredPrescaler = 1024; break;
	}

	return desiredPrescaler;
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_Init
 * @Brief		:	Initialize Timer 0 according to the pre-configuration
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TIMER0_Init(void)
{
	/*Waveform generation mode selection*/
	TCCR0 &= TIMER_MODE_MASK;
	TCCR0 |= TIMER_COUNTER0_MODE;

#if TIMER_COUNTER0_MODE == NORMAL

#elif TIMER_COUNTER0_MODE == PWM_PHASE_CORRECT

#elif TIMER_COUNTER0_MODE == CTC

	/*Compare Output mode Selection*/
	TCCR0 &= COMPARE_OUTPUT_MASK;
	TCCR0 |= OC_TOGGLE;


#elif TIMER_COUNTER0_MODE == FAST_PWM

	/*Compare Output mode Selection*/
	TCCR0 &= COMPARE_OUTPUT_MASK;
	TCCR0 |= CLR_CM_SET_TOP;
#endif

	/*Selecting Prescaler bits*/
	TCCR0 &= CLK_SELECT_MASK;
	TCCR0 |= CLK_SELECTION_TIMER0;
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_SetOverflowCallBack
 * @Brief		:	Setting the call back function that will be called in the overflow ISR
 * @Param		:	pv_NotifcationFunc: pointer to the callback function made by the user
 * @RetVal		:	Error state of the function
 *========================================================================================================*/
uint8 MCAL_TIMER0_SetOverflowCallBack(void(*pv_NotifcationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if(NULL != pv_NotifcationFunc)
	{
		G_pv_overflow_CallbackFunc = pv_NotifcationFunc;
	}
	else
	{
		ErrorState = NULL_POINTER;
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_SetCompareMatchCallBack
 * @Brief		:	Setting the call back function that will be called in the compare match ISR
 * @Param		:	pv_NotifcationFunc: pointer to the callback function made by the user
 * @RetVal		:	Error state of the function
 *========================================================================================================*/
uint8 MCAL_TIMER0_SetCompareMatchCallBack(void(*pv_NotifcationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if(NULL != pv_NotifcationFunc)
	{
		G_pv_compareMatch_CallbackFunc = pv_NotifcationFunc;
	}
	else
	{
		ErrorState = NULL_POINTER;
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_StartTimeMs_BusyWait
 * @Brief		:	Make a delay using polling concept with timer0
 * @Param		:	timeInMilli: the delay time the user want in milliseconds
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TIMER0_StartTimeMs_BusyWait(uint64 timeInMilli)
{
#if TIMER_COUNTER0_MODE == NORMAL
	/* Converting the time to microseconds to ease the calculations */
	uint64 timeInMicro = timeInMilli * 1000;
	/* Calculating Tick time in microseconds with the configured prescaler and system frequency */
	uint64 TickTimeMicro = ((float)(getPrescaler(CLK_SELECTION_TIMER0)) /SYSTEM_FREQUENCY) *1000000;
	/* Calculating the max time can be generated by timer0 in microseconds */
	uint64 MaxTimeInMicro = TickTimeMicro * 256;
	/* Number of overflows timer0 will make according to the input time */
	uint64 overflows = 0;


	if(timeInMicro == MaxTimeInMicro)
	{
		/*Setting initial value of the timer*/
		TCNT0 = 0;
		/*Busy waiting until overflow flag to be set*/
		while( GET_BIT(TIFR, TIFR_TOV0) == 0);
		/*Clear the overflow flag*/
		SET_BIT(TIFR,TIFR_TOV0);
	}
	else if(timeInMicro < MaxTimeInMicro)
	{
		/*Setting initial value of the timer*/
		TCNT0 = (MaxTimeInMicro - timeInMicro) / TickTimeMicro;
		/*Busy waiting until overflow flag to be set*/
		while( GET_BIT(TIFR, TIFR_TOV0) == 0);
		/*Clear the overflow flag*/
		SET_BIT(TIFR,TIFR_TOV0);
	}
	else if(timeInMicro > MaxTimeInMicro)
	{
		/*Calculating the number of overflows should be made to achieve the desired delay*/
		overflows = ceil(timeInMicro / MaxTimeInMicro) ;
		/*Setting initial value of the timer*/
		TCNT0 = 256 - ( (timeInMicro/TickTimeMicro) / overflows);
		/*Busy waiting until we finishes the calculated number of overflows*/
		while(overflows != 0)
		{
			/*Busy waiting until overflow flag to be set*/
			while( GET_BIT(TIFR, TIFR_TOV0) == 0);
			/*Clear the overflow flag*/
			SET_BIT(TIFR,TIFR_TOV0);
			overflows--;
		}
	}

#endif
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_StartTimeMS_Asynch
 * @Brief		:	Make a delay using asynchronous concept using interrupt with timer0
 * @Param		:	timeInMilli: the delay time the user want in milliseconds
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TIMER0_StartTimeMS_Asynch(uint64 timeInMilli)
{
#if TIMER_COUNTER0_MODE == NORMAL
	if(TIMER0_STATE == IDLE)
	{
		/* Converting the time to microseconds to ease the calculations */
		uint64 timeInMicro = timeInMilli * 1000;
		/* Calculating Tick time in microseconds with the configured prescaler and system frequency */
		uint64 TickTimeMicro = ((float)(getPrescaler(CLK_SELECTION_TIMER0)) /SYSTEM_FREQUENCY) *1000000;
		/* Calculating the max time can be generated by timer0 in microseconds */
		uint64 MaxTimeInMicro = TickTimeMicro * 256;
		/* Number of overflows timer0 will make according to the input time */
		uint64 overflows = 0;

		/*Set the timer state to be busy*/
		TIMER0_STATE = BUSY;

		if(timeInMicro == MaxTimeInMicro)
		{
			/*Setting initial value of the timer*/
			TCNT0 = 0;
			/*Setting the overflow to be only one as the desired time equal the maximum time*/
			G_NumberOfOverflows = 1;
		}
		else if(timeInMicro < MaxTimeInMicro)
		{
			/*Setting initial value of the timer*/
			TCNT0 = (MaxTimeInMicro - timeInMicro) / TickTimeMicro;
			/*Setting the overflow to be only one as the desired time smaller than the maximum time*/
			G_NumberOfOverflows = 1;
		}
		else if(timeInMicro > MaxTimeInMicro)
		{
			/*Calculating the number of overflows should be made to achieve the desired delay*/
			overflows = ceil(timeInMicro / MaxTimeInMicro) ;
			/*Setting initial value of the timer*/
			TCNT0 = 256 - ( (timeInMicro/TickTimeMicro) / overflows);
			/*Setting the overflow used in the ISR to the calculated number according to the input time*/
			G_NumberOfOverflows = overflows;
		}

		/*Enable Overflow Interrupt*/
		SET_BIT(TIMSK,TIMSK_TOIE0);

		/* Enable the general interrupt controller */
		SET_BIT(SREG,SREG_I);
	}
	else
	{
		/* Do Nothing */
	}


#endif
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_stopTimer
 * @Brief		:	Stop the Timer 0
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TIMER0_stopTimer(void)
{
	/*Selecting Prescaler bits*/
	TCCR0 &= CLK_SELECT_MASK;
	TCCR0 |= NO_CLK_SOURCE;
}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_GenerateSquareWave
 * @Brief		:	Generate square wave using CTC mode
 * @Param		:	frequency: the frequency needed for the waveform in kHz
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TIMER0_GenerateSquareWave(uint16 frequency)
{
	/* Time period of square wave: 2 x (OCR0+1) x Tick Time  */
	/* Frequency of square wave = 1/Time period of square wave */
	/* Explanation:
	 * The pin will toggle when it reach the OCR0 value every time so the total period ticks is 2x(OCR0+1)
	 * So the time period of the square wave = the total ticks x Tick Time
	 * And we will find that the frequency of the square wave is 1/Time period of square wave
	 * By putting the OCR0 in the left hand side the equation will be:
	 *	OCR0 =    (Time period of square wave / Tick Time)	/	2			*/

	OCR0 =  ( (1.0/(frequency*1000)) / (1.0/SYSTEM_FREQUENCY) ) /2 ;

	/*Enable output compare match interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);
	/* Enable the general interrupt controller */
	SET_BIT(SREG,SREG_I);

}

/*========================================================================================================
 * @Fun			:	MCAL_TIMER0_GeneratePwmSignal
 * @Brief		:	Generate PWM Signal
 * @Param		:	onPeriodTicks: the ticks of ON period
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TIMER0_GeneratePwmSignal(uint8 onPeriodTicks)
{
	OCR0 = onPeriodTicks;
}

/*=============================================================================================
 * 										ISRs
 *=============================================================================================*/
/* ISR of Timer0 Overflow */
void __vector_11(void) __attribute((signal));
void __vector_11(void)
{
	if(NULL == G_pv_overflow_CallbackFunc)
	{
		/* Do Nothing */
	}
	else
	{
		G_NumberOfOverflows--;

		if(G_NumberOfOverflows == 0)
		{
			G_pv_overflow_CallbackFunc();
			TIMER0_STATE = IDLE;
		}
	}
}

/* ISR of Timer0 Compare Match */
void __vector_10(void) __attribute((signal));
void __vector_10(void)
{
	if(NULL == G_pv_overflow_CallbackFunc)
	{
		/* Do Nothing */
	}
	else
	{
		G_pv_overflow_CallbackFunc();
	}
}
