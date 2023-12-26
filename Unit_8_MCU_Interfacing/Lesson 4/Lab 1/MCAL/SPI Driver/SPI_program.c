/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    SPI				******************/
/*****************************************************************/
/*****************************************************************/

#include "SPI_interface.h"


/*========================================================================================================
 * @Fun			:	SPI_MasterInit
 * @Brief		:	Initialize the SPI Controller of the MCU to be Master
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_SPI_MasterInit(void)
{
	/* Configure the pins of the slave controller */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT);				/* Configure the MOSI to be output */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_INPUT_FLOATING);		/* Configure the MISO to be input */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);				/* Configure the SCK to be output */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT);				/* Configure the SS to be output */

	/* Selecting Master mode */
	SET_BIT(SPCR,SPCR_MSTR);

	/* Setting the Prescaler */
	/* SCK_FREQUENCEY contains SPI2X,SPR1,SPR0 */
	SPCR |= ( (0b011 & SCK_FREQUENCEY) << 0 );		/* Masked the first two bits and put them in SPR0 & SPR1 */
	SPSR |= ( ((0b100)>>2) << 0 );					/* Take the third bit and put in SPI2X */

	/* Enable SPI */
	SET_BIT(SPCR,SPCR_SPE);
}

/*========================================================================================================
 * @Fun			:	SPI_SlaveInit
 * @Brief		:	Initialize the SPI Controller of the MCU to be Slave
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_SPI_SlaveInit(void)
{
	/* Configure the pins of the slave controller */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_INPUT_FLOATING);		/* Configure the MOSI to be input */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT);				/* Configure the MISO to be output */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_INPUT_FLOATING);		/* Configure the SCK to be input */
	MCAL_DIO_SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_INPUT_FLOATING);		/* Configure the SS to be input */

	/*Selecting Slave mode*/
	CLR_BIT(SPCR,SPCR_MSTR);


	/*Enable SPI*/
	SET_BIT(SPCR,SPCR_SPE);
}

/*========================================================================================================
 * @Fun			:	SPI_Transcieve
 * @Brief		:	Initialize the SPI Controller of the MCU to be Slave
 * @Param		:	Data: The data will be sent if we use this function in master code
 * 							otherwise it will the data in the shift register of the slave
 * @RetVal		:	None
 *========================================================================================================*/
uint8 MCAL_SPI_Transcieve(uint8 Data)
{
	/* Put the data in the shift register */
	SPDR = Data;

	/* Busy waiting until the interrupt flag is raised and transfer is complete */
	while(GET_BIT(SPSR,SPSR_SPIF) == 0);

	/* Get the exchanged data */
	return SPDR;
}

