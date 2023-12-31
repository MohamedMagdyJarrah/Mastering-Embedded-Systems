/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TWI				******************/
/*****************************************************************/
/*****************************************************************/

#include "TWI_interface.h"

/*========================================================================================================
 * @Fun			:	getPrescaler
 * @Brief		:	Static Function to assign the prescaler of the TWI clock in its equation
 * @Param 		:	prescaler: the prescaler the user configured
 * @RetVal		:	None
 *========================================================================================================*/
static uint8 getPrescaler(uint8 prescaler)
{
	switch(prescaler)
	{
	case PRESCALER_1:	return 1; break;
	case PRESCALER_4:	return 4; break;
	case PRESCALER_16:	return 16; break;
	case PRESCALER_64:	return 64; break;
	}
	return 1;
}


/*========================================================================================================
 * @Fun			:	MCAL_TWI_MasterInit
 * @Brief		:	Initialize the TWI Controller of the MCU to be Master
 * @Param 		:	Address: Address assigned to the master if there is any node want to communicate to it as a slave
 * @RetVal		:	None
 * @Note		:   Send 0 to the function if you will use the controller as master only
 *========================================================================================================*/
void MCAL_TWI_MasterInit(uint8 Address)
{
	/* Configure the TWI Pins direction */
	MCAL_DIO_SetPinDirection(DIO_PORTC , DIO_PIN0 , DIO_PIN_INPUT_FLOATING);	/* Configure the SCL to be input floating */
	MCAL_DIO_SetPinDirection(DIO_PORTC , DIO_PIN1 , DIO_PIN_INPUT_FLOATING);	/* Configure the SDA to be input floating */

	/*Enable Master generating acknowledge bit for receiving data*/
	SET_BIT(TWCR,TWCR_TWEA);

	/* Setting the Clock of Master */
	TWBR = ((F_CPU/SCL_FREQUENCEY)-16) / (2*getPrescaler(SCL_PRESCALER));
	TWSR |= (SCL_PRESCALER<<0);

	/*Clear the two bits of TWPS*/
	CLR_BIT(TWSR,TWSR_TWPS1);
	CLR_BIT(TWSR,TWSR_TWPS0);


	/*Assign Address of Master as a slave*/
	if(Address != 0 )
	{
		TWAR = Address<<1 ;
	}

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SlaveInit
 * @Brief		:	Initialize the TWI Controller of the MCU to be Master
 * @Param 		:	SlaveAddress: Address assigned to the slave
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_TWI_SlaveInit(uint8 SlaveAddress)
{
	/* Configure the TWI Pins direction */
	MCAL_DIO_SetPinDirection(DIO_PORTC , DIO_PIN0 , DIO_PIN_INPUT_FLOATING);	/* Configure the SCL to be input floating */
	MCAL_DIO_SetPinDirection(DIO_PORTC , DIO_PIN1 , DIO_PIN_INPUT_FLOATING);	/* Configure the SDA to be input floating */

	/*Initialize Slave Address*/
	TWAR = SlaveAddress<<1 ;

	/*Enable Slave generating acknowledge bit for receiving data*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}


/*========================================================================================================
 * @Fun			:	MCAL_TWI_SendStartCondition
 * @Brief		:	Function to send the start condition of the I2C
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_SendStartCondition(void)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Setting Start Condition bit on the bus*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != START_ACK )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = START_CONDITION_ERROR;
	}
	else
	{
		/*Do nothing*/
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SendRepeatedStart
 * @Brief		:	Function to send the repeated start condition of the I2C
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus	MCAL_TWI_SendRepeatedStart(void)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Setting Start Condition bit on the bus*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != REP_START_ACK )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = REPEATED_START_CONDITION_ERROR;
	}
	else
	{
		/*Do nothing*/
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SendSlaveAddressWithWrite
 * @Brief		:	Function to send the slave address which we will write on it
 * @Param 		:	SlaveAddress: Address assigned to the slave we want to communicate with
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_SendSlaveAddressWithWrite(uint8 SlaveAddress)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Set the slave address in the 7 MSB and clear the last bit in the data register */
	TWDR = SlaveAddress<<1 ;
	CLR_BIT(TWDR,0);				// For write request

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = SLAVE_ADDRESS_WITH_WRITE_ERROR;
	}
	else
	{
		/*Do nothing*/
	}
	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SendSlaveAddressWithRead
 * @Brief		:	Function to send the slave address which we will read from it
 * @Param 		:	SlaveAddress: Address assigned to the slave we want to communicate with
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_SendSlaveAddressWithRead(uint8 SlaveAddress)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Set the slave address in the 7 MSB and clear the last bit in the data register */
	TWDR = SlaveAddress<<1 ;
	SET_BIT(TWDR,0);				// For read request

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = SLAVE_ADDRESS_WITH_READ_ERROR;
	}
	else
	{
		/*Do nothing*/
	}
	return ErrorState;
}

TWI_ErrorStatus MCAL_TWI_ReceiveSlaveAddressWithWrite(void)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != SLAVE_ADD_RCVD_WR_REQ )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = SLAVE_RECEIVE_ADDRESS_WITH_WRITE_ERROR;
	}
	else
	{
		/*Do nothing*/
	}
	return ErrorState;
}

TWI_ErrorStatus MCAL_TWI_ReceiveSlaveAddressWithRead(void)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != SLAVE_ADD_RCVD_RD_REQ )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = SLAVE_RECEIVE_ADDRESS_WITH_READ_ERROR;
	}
	else
	{
		/*Do nothing*/
	}
	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_MasterWriteDataByte
 * @Brief		:	Function to write the data byte on the slave we sent its address
 * @Param 		:	DataByte: Data sent to the slave controller
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_MasterWriteDataByte(uint8 DataByte)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Write the data byte*/
	TWDR = DataByte;

	/*Clear the interrupt flag to the start the previous operation by setting interrupt bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != MSTR_WR_BYTE_ACK )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = MASTER_WRITE_DATA_ERROR;
	}
	else
	{
		/*Do nothing*/
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_MasterReadDataByte
 * @Brief		:	Function to read the data byte from the slave we sent its address
 * @Param 		:	DataByte: Data received from the slave controller
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_MasterReadDataByte(uint8* DataByte)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Clear the interrupt flag to start the slave sending data*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != MSTR_RD_BYTE_WITH_ACK )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = MASTER_READ_DATA_ERROR;
	}
	else
	{
		/*Read the data received*/
		*DataByte = TWDR;
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SlaveReceiveByte
 * @Brief		:	Function to read the data byte the slave received
 * @Param 		:	DataByte: Data received from the master controller
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_SlaveReceiveByte(uint8* DataByte)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Clear the interrupt flag to start the slave sending data*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != SLAVE_DATA_RECEIVED )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = SLAVE_RECEIVE_DATA_ERROR;
	}
	else
	{
		/*Read the data received*/
		*DataByte = TWDR;
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SlaveSendByte
 * @Brief		:	Function to send the data byte the master want to read
 * @Param 		:	DataByte: Data sent by the slave to the master
 * @RetVal		:	Function error state
 *========================================================================================================*/
TWI_ErrorStatus MCAL_TWI_SlaveSendByte(uint8 DataByte)
{
	TWI_ErrorStatus ErrorState = ERROR_NONE;

	/*Write the data byte*/
	TWDR = DataByte;

	/*Clear the interrupt flag to start the slave sending data*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Waiting until the interrupt is raised again and the previous operation is complete*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check on the operation*/
	if( (TWSR & 0xF8) != SLAVE_BYTE_TRANSMITTED )	//Getting TWSR by masking with start condition bits and check on it
	{
		ErrorState = SLAVE_SEND_DATA_ERROR;
	}
	else
	{
		/* Wait for 1us to ensure sending the data */
		_delay_us(1);
	}

	return ErrorState;
}

/*========================================================================================================
 * @Fun			:	MCAL_TWI_SendStopCondition
 * @Brief		:	Send stop condition to end the transmission
 * @RetVal		:	None
 *=====================================================================s===================================*/
void MCAL_TWI_SendStopCondition(void)
{
	/*Clear Start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Generate the stop condition on the bus*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clear the interrupt flag to send the stop condition to end the frame*/
	SET_BIT(TWCR,TWCR_TWINT);
}
