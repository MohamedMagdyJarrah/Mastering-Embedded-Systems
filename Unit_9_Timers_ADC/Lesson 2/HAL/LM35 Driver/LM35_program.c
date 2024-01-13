/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    LM35			******************/
/*****************************************************************/
/*****************************************************************/

#include "LM35_interface.h"

/*========================================================================================================
 * @Fun			:	HAL_LM35_GetTemperature
 * @Brief		:	Get the temperature from LM35 Sensor
 * @Param[in]  	:	Sensor: pointer to struct that contain the configurations of the LM35
 * @RetVal		:	The temperature parallel to the measured analog value
 *========================================================================================================*/
uint16 HAL_LM35_GetTemperature(LM35_t* Sensor)
{
	uint16 LM35_TempReading = 0;
	uint16 CalculatedDigitalValue = 0;
	float64 stepSize = 0;
	float64 LM35_AnalogReading = 0;

	/* Get the digital value measured from LM35 */
	MCAL_ADC_StartConversionSynch(Sensor->LM35_CHANNEL,&CalculatedDigitalValue);

	/* Calculate the step size according to the resolution chose */
	if(Sensor->LM35_OPERATION_RESOLUTION == RESOLUTION_8_BIT)
	{
		stepSize = LM35_VREF/256.0;
	}
	else if(Sensor->LM35_OPERATION_RESOLUTION == RESOLUTION_10_BIT)
	{
		stepSize = LM35_VREF/1024.0;
	}

	/* Get the analog voltage from the measured digital value */
	LM35_AnalogReading = CalculatedDigitalValue * stepSize;

	/* We have the voltage measured from LM35, And our Sensor measure 10mv per degree so,
	 * 		10mv 			  ====>  1 degree celsius
	 *		Measured Voltage  ====>  Temperature
	 *	Therefore, Temperature = ( Measured Voltage * 1 ) / 10mv = Measured Voltage * 100
	 *  */
	LM35_TempReading = LM35_AnalogReading*100;

	return LM35_TempReading;
}
