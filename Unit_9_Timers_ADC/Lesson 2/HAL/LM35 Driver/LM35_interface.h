/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    LM35			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../MCAL/ADC Driver/ADC_interface.h"
#include "LM35_private.h"

/* Struct for LM35 Configuration */
typedef struct
{
	uint8 LM35_CHANNEL;
	uint8 LM35_OPERATION_RESOLUTION;
}LM35_t;

/*=============================================================================================
 * 									Pre-Build Configuration
 *=============================================================================================*/
/* Put the value of reference voltage used with ADC */
#define LM35_VREF					(2.56)

/*=======================================================================================
 * 						APIs supported by "HAL LM35 Driver"
 *=======================================================================================*/
/*	You should configure the sensor with your channel and resolution from this options:
	1-  LM35_ADC0_RESOLUTION_8BIT
	2-  LM35_ADC1_RESOLUTION_8BIT
	3-  LM35_ADC2_RESOLUTION_8BIT
	4-  LM35_ADC3_RESOLUTION_8BIT
	5-  LM35_ADC4_RESOLUTION_8BIT
	6-  LM35_ADC5_RESOLUTION_8BIT
	7-  LM35_ADC6_RESOLUTION_8BIT
	8-  LM35_ADC7_RESOLUTION_8BIT
	9-  LM35_ADC0_RESOLUTION_10_BIT
	10- LM35_ADC1_RESOLUTION_10_BIT
	11- LM35_ADC2_RESOLUTION_10_BIT
	12- LM35_ADC3_RESOLUTION_10_BIT
	13- LM35_ADC4_RESOLUTION_10_BIT
	14- LM35_ADC5_RESOLUTION_10_BIT
	15- LM35_ADC6_RESOLUTION_10_BIT
	16- LM35_ADC7_RESOLUTION_10_BIT
*/
uint16 HAL_LM35_GetTemperature(LM35_t* Sensor);


#endif
