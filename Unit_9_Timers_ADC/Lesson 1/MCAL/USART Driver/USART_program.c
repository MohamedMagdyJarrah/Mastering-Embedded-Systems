/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    USART			******************/
/*****************************************************************/
/*****************************************************************/
#include "USART_interface.h"

/*State of USART Sending*/
uint8	USART_TransmitterBusyState = IDLE;
uint8	USART_RecieverBusyState = IDLE;

/*Source of Transmitter ISR*/
uint8 USART_TransmitterISRSource = SINGLE_CHAR;
/*Source of Receiver ISR*/
uint8 USART_RecieverISRSource = RECIEVE_CHAR;

/* Variables to store the data will be sent or received */
static uint8* USART_TransmittedData;
static uint8* USART_RecievedData = NULL;

static char* USART_StringTransmitted = NULL;
static uint8* USART_BufferRecieved = NULL;

/* For Characters callback functions */
static void (*USART_pvTransmitterNotificationFunction)(void) = NULL;
static void (*USART_pvRecieverNotificationFunction)(void) = NULL;
/* For strings callback functions */
static void(*USART_pvStringTransmittedNotifiFunc)(void)=NULL;
static void(*USART_pvBufferNotificationFunction)(void)=NULL;

/* Variables used in ISRs */
static uint8 GLobal_StringCounter = 0;
static uint8 GLobal_BufferCounter = 0;
static uint8 Global_BufferSize;

/*========================================================================================================
 * @Fun			:	MCAL_USART_Init
 * @Brief		:	Initialize the USART according to Pre-Build Configurations
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_USART_Init(void)
{
	/* Define variable to store the data will be stored in UCSRC Register and equate in with the main register as wanted in the specs
	 * And Initialize it with setting the seventh bit as mentioned in the specs to access UCSRC
	 * */
	uint8 Local_UCSRC = 0x80;

	/* Configure the USART Tx and Rx Pins in MCU */
	MCAL_DIO_SetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);			/* Tx as Output */
	MCAL_DIO_SetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT_FLOATING);	/* Rx as Input */


	/* Configuring the mode of the USART and The Baud rate if it is in Asynchronous mode */
#if USART_MODE == USART_MODE_ASYNCHRONOUS
	CLR_BIT(Local_UCSRC,UCSRC_UMSEL);
	UBRRL = USART_BAUDRATE;
#elif USART_MODE == USART_MODE_SYNCHRONOUS
	SET_BIT(Local_UCSRC,UCSRC_UMSEL);
#endif

	/* Configuring the Data length */
	Local_UCSRC |= (USART_DATALENGTH<<1);

	/* Configuring the parity bits of the frame */
	Local_UCSRC |= (USART_PARITY<<4);

	/* Configuring the stop bits of the frame */
	Local_UCSRC |= (USART_STOPBITS<<3);

	/* Store the data in the real UCSRC Register */
	UCSRC = Local_UCSRC;

	/* Enable Transmitter and Receiver */
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_SendCharSynch
 * @Brief		:	Send data using synchronous mode without using interrupt
 * @Param		:	Data: The data the user will send
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_SendCharSynch(uint8 Data)
{
	uint8 ErrorState = NO_ERROR;
	uint32 Counter = 0;

	if(USART_TransmitterBusyState == IDLE)
	{
		/* Change the state of transmitter to be busy */
		USART_TransmitterBusyState = BUSY;

		/* Wait until the transmit buffer is empty */
		while((GET_BIT(UCSRA,UCSRA_UDRE) == 0) && (Counter != USART_TIMEOUT))
		{
			Counter++;
		}

		if(Counter == USART_TIMEOUT)
		{
			ErrorState = ERROR_DETECTED;
		}
		else
		{
			/* Store the data in the buffer to send it */
			UDR = Data;
			/* Return the state of the transmitter back to idle as it finished transmitting */
			USART_TransmitterBusyState = IDLE;
		}
	}
	else
	{
		ErrorState = BUSY_FUNC;
	}

	return ErrorState;
}


/*========================================================================================================
 * @Fun			:	MCAL_USART_RecievesCharSynch
 * @Brief		:	Receive data using synchronous mode without using interrupt
 * @RetVal		:	The data received from the transmitter
 *========================================================================================================*/
uint8 MCAL_USART_RecievesCharSynch(void)
{
	uint8 ErrorState = NO_ERROR;

	if(USART_RecieverBusyState == IDLE)
	{
		/* Change the state of receiver to be busy */
		USART_RecieverBusyState = BUSY;

		/* Wait until the receiving process complete */
		while( (GET_BIT(UCSRA,UCSRA_RXC) == 0) );

		/* Return back the state of the receiver */
		USART_RecieverBusyState = IDLE;

		/* Return the data received from the transmitter */
		return UDR;
	}
	else
	{
		ErrorState = BUSY_FUNC;
	}

	return ErrorState;

	//	while (!GET_BIT(UCSRA,UCSRA_RXC));
	//	return UDR;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_SendStringSynch
 * @Brief		:	Send string using synchronous mode without using interrupt
 * @Param		:	String: The data the user will send
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_SendStringSynch(const char* String)
{
	uint8 ErrorState = NO_ERROR;
	uint8 Indexing=0;

	if(String == NULL)
	{
		ErrorState = NULL_POINTER;
	}
	else
	{
		while ( String[Indexing] != '\0')
		{
			MCAL_USART_SendCharSynch(String[Indexing]);
			Indexing++;
		}
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_RecieveBufferSynch
 * @Brief		:	Receive buffer using synchronous mode without using interrupt
 * @Param		:	Buffer: The data the user will send in the buffer
 * @Param		:	BufferSize: The size of the buffer
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_RecieveBufferSynch(uint8* Buffer,uint8 BufferSize)
{
	uint8 ErrorState = NO_ERROR;
	uint8 Counter = 0;

	if(Buffer == NULL)
	{
		ErrorState = NULL_POINTER;
	}
	else
	{
		for(Counter=0 ; Counter<BufferSize ; Counter++)
		{
			Buffer[Counter] = MCAL_USART_RecievesCharSynch();
		}
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_SendCharAsynch
 * @Brief		:	Send data using asynchronous mode using interrupt
 * @Param		:	Data: Pointer to the data the user will send
 * @Param		:	NotificationFunc : Pointer to function called when the data transmit
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_SendCharAsynch(uint8* Data,void(*NotificationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if(Data == NULL || NotificationFunc == NULL)
	{
		ErrorState = NULL_POINTER;
	}
	else
	{
		if(USART_TransmitterBusyState == BUSY)
		{
			ErrorState = BUSY_FUNC;
		}
		else
		{
			/* Change the state of transmitter to be busy */
			USART_TransmitterBusyState = BUSY;

			/*Let ISR Know the source of interrupt*/
			USART_TransmitterISRSource = SINGLE_CHAR;

			/*Initialize USART call back notification function will be used in ISR*/
			USART_pvTransmitterNotificationFunction = NotificationFunc;

			/*Initialize the transmitted data*/
			USART_TransmittedData = Data;

			/*Store the in UDR*/
			//			UDR = *USART_TransmittedData;

			/*Enable Transmitter Interrupt*/
			SET_BIT(UCSRB,UCSRB_UDRIE);

			/* Enable the general interrupt controller */
			SET_BIT(SREG,SREG_I);
		}
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_RecieveCharAsynch
 * @Brief		:	Receive data using asynchronous mode using interrupt
 * @Param		:	RecievedData: Pointer to variable to store the data the user will receive
 * @Param		:	NotificationFunc : Pointer to function called when the data received
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_RecieveCharAsynch(uint8* RecievedData,void(*NotificationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if( (RecievedData == NULL)  || (NotificationFunc == NULL))
	{
		ErrorState = NULL_POINTER;
	}
	else
	{
		if(USART_RecieverBusyState == BUSY)
		{
			ErrorState = BUSY_FUNC;
		}
		else
		{
			/* Change the state of Receiver to be busy */
			USART_RecieverBusyState = BUSY;

			/*Let ISR Know the source of interrupt*/
			USART_RecieverISRSource = RECIEVE_CHAR;

			/*Initialize USART call back notification function will be used in ISR*/
			USART_pvRecieverNotificationFunction = NotificationFunc;

			/*Initialize the received data reading*/
			USART_RecievedData = RecievedData;

			/*Enable Receiver Interrupt*/
			SET_BIT(UCSRB,UCSRB_RXCIE);

			/* Enable the general interrupt controller */
			SET_BIT(SREG,SREG_I);
		}
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_SendStringAsynch
 * @Brief		:	Send string using asynchronous mode using interrupt
 * @Param		:	String: Pointer to the string the user will send
 * @Param		:	NotificationFunc : Pointer to function called when the data transmit
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_SendStringAsynch(char* String,void(*NotificationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if(String == NULL || NotificationFunc == NULL)
	{
		ErrorState = NULL_POINTER;
	}
	else
	{
		if(USART_TransmitterBusyState == BUSY)
		{
			ErrorState = BUSY_FUNC;
		}
		else
		{
			/* Change the state of transmitter to be busy */
			USART_TransmitterBusyState = BUSY;

			/*Let ISR Know the source of interrupt*/
			USART_TransmitterISRSource = STRING;

			/*Initialize USART call back notification function will be used in ISR*/
			USART_pvStringTransmittedNotifiFunc = NotificationFunc;

			/*Initialize the transmitted data*/
			USART_StringTransmitted = String;

			/*Enable Transmitter Interrupt*/
			SET_BIT(UCSRB,UCSRB_UDRIE);

			/* Enable the general interrupt controller */
			SET_BIT(SREG,SREG_I);
		}
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_USART_RecieveBufferAsynch
 * @Brief		:	Receive Buffer using asynchronous mode using interrupt
 * @Param		:	Buffer: Pointer to the buffer the user will send
 * @Param		:	BufferSize: size of the buffer the user will send
 * @Param		:	NotificationFunc : Pointer to function called when the data received
 * @RetVal		:	The Error state of the function
 *========================================================================================================*/
uint8 MCAL_USART_RecieveBufferAsynch(uint8* Buffer,uint8 BufferSize,void(*NotificationFunc)(void))
{
	uint8 ErrorState = NO_ERROR;

	if(Buffer == NULL || NotificationFunc == NULL)
	{
		ErrorState = NULL_POINTER;
	}
	else
	{
		if(USART_RecieverBusyState == BUSY)
		{
			ErrorState = BUSY_FUNC;
		}
		else
		{
			/* Change the state of Receiver to be busy */
			USART_RecieverBusyState = BUSY;

			/*Let ISR Know the source of interrupt*/
			USART_RecieverISRSource = BUFFER;

			/*Initialize USART call back notification function will be used in ISR*/
			USART_pvBufferNotificationFunction = NotificationFunc;

			/*Initialize the received data reading*/
			USART_BufferRecieved = Buffer;

			/*Initialize the received data reading size*/
			Global_BufferSize = BufferSize;

			/*Enable Receiver Interrupt*/
			SET_BIT(UCSRB,UCSRB_RXCIE);

			/* Enable the general interrupt controller */
			SET_BIT(SREG,SREG_I);
		}
	}

	return ErrorState;
}

/*=======================================================================================
 * 										"USART ISRs"
 *=======================================================================================*/

/* ISR of USART Data Register Empty
 * When the register is empty the interrupt happens and inside it we will put the data in the register
 * */
void __vector_14(void) __attribute((signal));
void __vector_14(void)
{
	if(USART_TransmitterISRSource == SINGLE_CHAR)
	{
		/*Store the in UDR*/
		UDR = *USART_TransmittedData;

		/*Let the state of USART back to idle*/
		USART_TransmitterBusyState = IDLE;

		/*Disable Transmitter Interrupt*/
		CLR_BIT(UCSRB,UCSRB_UDRIE);

		/*Invoke call back notification function*/
		USART_pvTransmitterNotificationFunction();
	}
	else if (USART_TransmitterISRSource == STRING)
	{
		/* Store the char in UDR */
		UDR = USART_StringTransmitted[GLobal_StringCounter];

		/*Increasing the counter of string iterator */
		GLobal_StringCounter++;

		if(USART_StringTransmitted[GLobal_StringCounter] == '\0')
		{
			/*Let the state of USART back to idle*/
			USART_TransmitterBusyState = IDLE;

			/*Disable Transmitter Interrupt*/
			CLR_BIT(UCSRB,UCSRB_UDRIE);

			/*Invoke call back notification function*/
			USART_pvStringTransmittedNotifiFunc();

			/* Reset the string counter */
			GLobal_StringCounter = 0;
		}
	}
}

/* ISR of Rx USART
 * When the data finishes sending the interrupt happens to receive the data so I store it inside the ISR
 * */
void __vector_13(void) __attribute((signal));
void __vector_13(void)
{
	if(USART_RecieverISRSource == RECIEVE_CHAR)
	{
		/*READ the Received data from UDR register*/
		*USART_RecievedData = UDR;

		/*Let the state of USART back to idle*/
		USART_RecieverBusyState = IDLE;

		/*Disable Receiver Interrupt*/
		CLR_BIT(UCSRB,UCSRB_RXCIE);

		/*Invoke call back notification function*/
		USART_pvRecieverNotificationFunction();
	}
	else if(USART_RecieverISRSource == BUFFER)
	{
		/*Receive elements of buffer*/
		*(USART_BufferRecieved+GLobal_BufferCounter) = UDR;

		GLobal_BufferCounter++;

		if(GLobal_BufferCounter == Global_BufferSize)
		{
			/*Let the state of USART back to idle*/
			USART_RecieverBusyState = IDLE;

			/*Disable Receiver Interrupt*/
			CLR_BIT(UCSRB,UCSRB_RXCIE);

			/*Invoke call back notification function*/
			USART_pvBufferNotificationFunction();

			/*Re-initialize the buffer counter again*/
			GLobal_BufferCounter = 0;
		}
	}
}
