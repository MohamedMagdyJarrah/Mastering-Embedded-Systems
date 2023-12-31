/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TWI				******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/ATMEGA32_MemMap.h"
#include "../DIO Driver/DIO_interface.h"

typedef enum
{
	ERROR_NONE,
	START_CONDITION_ERROR,
	REPEATED_START_CONDITION_ERROR,
	SLAVE_ADDRESS_WITH_WRITE_ERROR,
	SLAVE_ADDRESS_WITH_READ_ERROR,
	MASTER_WRITE_DATA_ERROR,
	MASTER_READ_DATA_ERROR,
	SLAVE_RECEIVE_DATA_ERROR,
	SLAVE_RECEIVE_ADDRESS_WITH_WRITE_ERROR,
	SLAVE_RECEIVE_ADDRESS_WITH_READ_ERROR
}TWI_ErrorStatus;

/*=============================================================================================
 * 									Pre-Build Configuration
 *=============================================================================================*/
#define SCL_FREQUENCEY				400000UL
/* You can choose from:
 * PRESCALER_1
 * PRESCALER_4
 * PRESCALER_16
 * PRESCALER_64
 *  */
#define SCL_PRESCALER				PRESCALER_1


/*=======================================================================================
 * 						APIs supported by "MCAL TWI Driver"
 *=======================================================================================*/

/*Pass 0 in Address if Master can't be addressed*/
void MCAL_TWI_MasterInit(uint8 Address);

void MCAL_TWI_SlaveInit(uint8 SlaveAddress);

TWI_ErrorStatus MCAL_TWI_SendStartCondition(void);

TWI_ErrorStatus	MCAL_TWI_SendRepeatedStart(void);

TWI_ErrorStatus MCAL_TWI_SendSlaveAddressWithWrite(uint8 SlaveAddress);

TWI_ErrorStatus MCAL_TWI_SendSlaveAddressWithRead(uint8 SlaveAddress);

TWI_ErrorStatus MCAL_TWI_ReceiveSlaveAddressWithWrite(void);

TWI_ErrorStatus MCAL_TWI_ReceiveSlaveAddressWithRead(void);

TWI_ErrorStatus MCAL_TWI_MasterWriteDataByte(uint8 DataByte);

TWI_ErrorStatus MCAL_TWI_MasterReadDataByte(uint8* DataByte);

TWI_ErrorStatus MCAL_TWI_SlaveReceiveByte(uint8* DataByte);

void MCAL_TWI_SendStopCondition(void);


#endif
