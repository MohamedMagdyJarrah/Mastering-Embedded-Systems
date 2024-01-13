/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    ADC				******************/
/*****************************************************************/
/*****************************************************************/
#include "ADC_interface.h"

/* The States of the Interrupt operations */
uint8 ADC_CurrentState = IDLE;
uint8 ADC_InterruptSource = ASYNCHRONOUS_SINGLE_CONVERSION;

/* For Asynchronous Conversion */
static uint16* ADC_Reading = NULL;
static void (*ADC_SingleConversionCallBack)(void) = NULL;

/* For Chain Conversion */
static void (*ADC_ChainConversionCallBack)(void) = NULL;
uint16 *ADC_ChainReadings = NULL;
uint8 *ADC_ChainChannels = NULL;
uint8 ADC_ChainSize = 0;
uint8 ADC_ChainIndex = 0;

/*========================================================================================================
 * @Fun			:	MCAL_ADC_Init
 * @Brief		:	Initialize the ADC according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_ADC_Init(void)
{
	/* Select the Voltage Reference */
	ADMUX &= CLR_REFERENCE_SELECTION;
	ADMUX |= VOLTAGE_REFRENCE_SELECTION;

	/*Choosing Left or Right Adjust Result*/
#if ADLAR_ADJUST_RESULT == RIGHT_ADJUST_RESULT
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#elif ADLAR_ADJUST_RESULT == LEFT_ADJUST_RESULT
	SET_BIT(ADMUX,ADMUX_ADLAR);
#endif

	/* Adjusting the ADC Prescaler */
	ADCSRA &= ADC_PRESCALER_MASKING;
	ADCSRA |= ADC_PRESCALER;

	/*Enable ADC Peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}


/*========================================================================================================
 * @Fun			:	MCAL_ADC_StartConversionSynch
 * @Brief		:	Convert the analog signal received to digital value
 * @Param 		:	Channel: The channel used by the user
 * @Param		:	ADCReading: Pointer to variable to store the digital value received
 * @RetVal		:	Error state of the function
 *========================================================================================================*/
uint8 MCAL_ADC_StartConversionSynch(uint8 Channel , uint16* ADCReading)
{
	uint8 ErrorState = NO_ERROR;

	/* Selecting the channel passed by the user */
	ADMUX &= CLR_MUX_BITS;
	ADMUX |= Channel;

#if CONVERSION_MODE == SINGLE_CONVERSION_MODE
	/* Start the ADC Conversion */
	SET_BIT(ADCSRA,ADCSRA_ADSC);


	/* Polling (Busy waiting until ADC flag is set) */
	while( (GET_BIT(ADCSRA,ADCSRA_ADIF))== 0 );

	/*Clearing ADC flag when the conversion complete*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);

#elif CONVERSION_MODE == AUTO_TRIGGER_MODE

	/* Enable Auto trigger mode */
	SET_BIT(ADCSRA,ADCSRA_ADATE);

	/* Selecting the Auto trigger source */
	SFIOR &= AUTO_TRIGGER_MASK;
	SFIOR |= AUTO_TRIGGER_SOURCE;

	/*Start Conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	/*Enable ADC Interrupt*/
	SET_BIT(ADCSRA,ADCSRA_ADIE);
	/* Enable the general interrupt controller */
	SET_BIT(SREG,SREG_I);
#endif

#if CONVERSION_RESOLUTION == RESOLUTION_8_BIT
	*ADCReading = ADCL;
#elif CONVERSION_RESOLUTION == RESOLUTION_10_BIT
	*ADCReading = ADCLH;
//	*ADCReading = ADCL | (ADCH << 8) ;
#endif

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_ADC_StartConversionAsynch
 * @Brief		:	Convert the analog signal received to digital value using asynchronous method (interrupt)
 * @Param 		:	Channel: The channel used by the user
 * @Param		:	ADCReading: Pointer to variable to store the digital value received
 * @Param		:	pvNotificationFunc: Pointer to callback function we will call it in the ISR
 * @RetVal		:	Error state of the function
 *========================================================================================================*/
uint8 MCAL_ADC_StartConversionAsynch(uint8 Channel , uint16* pADCReading , void (*pvNotificationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if (ADC_CurrentState == IDLE)
	{
		if( (pADCReading == NULL) || (pvNotificationFunc == NULL) )
		{
			ErrorState = NULL_POINTER;
		}
		else
		{
			/* Setting the current state to be busy */
			ADC_CurrentState = BUSY;

			/* Make the ISR know when the interrupt occur it comes from the Asynchronous conversion function */
			ADC_InterruptSource = ASYNCHRONOUS_SINGLE_CONVERSION;

			/* Selecting the channel passed by the user */
			ADMUX &= CLR_MUX_BITS;
			ADMUX |= Channel;

			/* Setting the callback function */
			ADC_SingleConversionCallBack = pvNotificationFunc;

			/* Save the address that will store the ADC reading */
			ADC_Reading = pADCReading;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
			/* Enable the general interrupt controller */
			SET_BIT(SREG,SREG_I);
		}
	}
	else
	{
		ErrorState = BUSY_FUNC;
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_ADC_StartConversionAsynch
 * @Brief		:	Convert the analog signal received to digital value using asynchronous method (interrupt)
 * @Param 		:	Channel: The channel used by the user
 * @RetVal		:	Error state of the function
 *========================================================================================================*/
uint8 MCAL_ADC_StartChainConversion(ADC_Chain_t* ADC_Chain)
{
	uint8 ErrorState = NO_ERROR;

	if(ADC_CurrentState == IDLE)
	{
		if(ADC_Chain == NULL)
		{
			ErrorState = NULL_POINTER;
		}
		else
		{
			/* Setting the current state to be busy */
			ADC_CurrentState = BUSY;

			/* Make the ISR know when the interrupt occur it comes from the chain conversion function */
			ADC_InterruptSource = CHAIN_CONVERSION;

			/* Setting the callback function */
			ADC_ChainConversionCallBack = ADC_Chain->Notf_Func;

			/* Setting the channels in the chain */
			ADC_ChainChannels = ADC_Chain->chainChannels;

			/* Setting the channel size of the chain */
			ADC_ChainSize= ADC_Chain->chainSize;

			/* Setting the channel readings of the chain */
			ADC_ChainReadings= ADC_Chain->chainReadings;

			/* Selecting the first channel passed by the user */
			ADMUX &= CLR_MUX_BITS;
			ADMUX |= ADC_ChainChannels[ADC_ChainIndex];

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
			/* Enable the general interrupt controller */
			SET_BIT(SREG,SREG_I);
		}
	}
	else
	{
		ErrorState = BUSY_FUNC;
	}

	return ErrorState;
}


/*=======================================================================================
 * 										"ADC ISRs"
 *=======================================================================================*/
void __vector_16 (void) __attribute((signal));
void __vector_16 (void)
{
	if(ADC_InterruptSource == ASYNCHRONOUS_SINGLE_CONVERSION)
	{
		/* Read the converted data */
#if CONVERSION_RESOLUTION == RESOLUTION_8_BIT
		*ADC_Reading = ADCL;
#elif CONVERSION_RESOLUTION == RESOLUTION_10_BIT
		*ADC_Reading = ADCLH;
#endif
		/*Turn back Conversion State to IDLE to make another conversion*/
		ADC_CurrentState = IDLE;

		/*Invoke the callback notification function*/
		ADC_SingleConversionCallBack();

		/*Disable ADC Conversion complete Interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_InterruptSource == CHAIN_CONVERSION)
	{
		/* Read the converted data */
#if CONVERSION_RESOLUTION == RESOLUTION_8_BIT
		ADC_ChainReadings[ADC_ChainIndex] = ADCL;
#elif CONVERSION_RESOLUTION == RESOLUTION_10_BIT
		ADC_ChainReadings[ADC_ChainIndex] = ADCLH;
#endif
		/* Increment the chain Index for the next conversion */
		ADC_ChainIndex++;

		if(ADC_ChainIndex == ADC_ChainSize)
		{
			/*Turn back Conversion State to IDLE to make another conversion*/
			ADC_CurrentState = IDLE;

			/*Invoke the callback notification function*/
			ADC_ChainConversionCallBack();

			/*Disable ADC Conversion complete Interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*Setting the required channel in MUX bits*/
			ADMUX &= CLR_MUX_BITS;
			ADMUX |= ADC_ChainChannels[ADC_ChainIndex];

			/*Start the next conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
