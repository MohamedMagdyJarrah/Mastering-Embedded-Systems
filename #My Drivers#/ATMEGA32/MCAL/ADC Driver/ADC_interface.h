/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    ADC				******************/
/*****************************************************************/
/*****************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/ATMEGA32_MemMap.h"


/*=============================================================================================
 * 									Pre-Build Configuration
 *=============================================================================================*/
/*For Size of ADC Chain*/
#define MAX_CHAIN_SIZE						10

/*Struct for ADC Chain*/
typedef struct
{
	uint8* chainChannels;
	uint8 chainSize;
	uint16 *chainReadings;
	void (*Notf_Func) (void);
}ADC_Chain_t;

/*Options to select voltage reference:
 * 	1-AREF		(Internal Vref is off and operate with External reference voltage)
 * 	2-AVCC		(Operate with the voltage on AVCC pin (5 volt))
 * 	3-INT_AREF	(Internal 2.56V voltage reference in the microcontroller)
 * 	*/
#define VOLTAGE_REFRENCE_SELECTION		AVCC

/*Options for AUTO TRIGGER Mode:
 * 1- SINGLE_CONVERSION_MODE
 * 2- AUTO_TRIGGER_MODE
 * */
#define CONVERSION_MODE					SINGLE_CONVERSION_MODE

/*Options for Auto Trigger source:
 * 1-FREE_RUNNING_MODE
 * 2-ANALOG_COMPARATOR
 * 3-EXTERNAL_INTERRUPT_0
 * 4-TIMER_COUNTER0_COMPARE_MATCH
 * 5-TIMER_COUNTER0_OVERFLOW
 * 6-TIMER_COUNTER_COMPARE_MATCH_B
 * 7-TIMER_COUNTER1_OVERFLOW
 * 8-TIMER_COUNTER1_CAPTURE_EVENT
 * */
#define AUTO_TRIGGER_SOURCE				FREE_RUNNING_MODE

/*Options to select Adjust result mode:
 * 1-RIGHT_ADJUST_RESULT
 * 2-LEFT_ADJUST_RESULT
 * */
#define	ADLAR_ADJUST_RESULT				RIGHT_ADJUST_RESULT


/*Options to select the Prescaler of ADC:
 * 1-DIV_BY_2
 * 2-DIV_BY_4
 * 3-DIV_BY_8
 * 4-DIV_BY_16
 * 5-DIV_BY_32
 * 6-DIV_BY_64
 * 7-DIV_BY_128
 * */
#define ADC_PRESCALER					DIV_BY_128

/*Options to choose Resolution of Conversion:
 * 1-RESOLUTION_8_BIT
 * 2-RESOLUTION_10_BIT
 * */
#define CONVERSION_RESOLUTION			RESOLUTION_10_BIT

/*=======================================================================================
 * 						APIs supported by "MCAL ADC Driver"
 *=======================================================================================*/
/* You should choose your channel from this options:
 * 	1- ADC0								1-  ADC0_ADC0_10X	       	10- ADC1_ADC1_1X           19- ADC2_ADC2_1X
	2- ADC1                             2-  ADC1_ADC0_10X           11- ADC2_ADC1_1X           20- ADC3_ADC2_1X
	3- ADC2                             3-  ADC0_ADC0_200X          12- ADC3_ADC1_1X           21- ADC4_ADC2_1X
	4- ADC3                             4-  ADC1_ADC0_200X          13- ADC4_ADC1_1X           22- ADC5_ADC2_1X
	5- ADC4					or			5-  ADC2_ADC2_10X           14- ADC5_ADC1_1X
	6- ADC5                             6-  ADC3_ADC2_10X           15- ADC6_ADC1_1X
	7- ADC6                             7-  ADC2_ADC2_200X          16- ADC7_ADC1_1X
	8- ADC7                             8-  ADC3_ADC2_200X          17- ADC0_ADC2_1X
	                                    9-  ADC0_ADC1_1X	        18- ADC1_ADC2_1X
   And for creating a chain you can configure the array as this example:
   ADC_Chain->chainChannels[3] = {ADC0,ADC1,ADC2}
 */

/* Initialize the ADC */
void MCAL_ADC_Init(void);

/*Get Reading of ADC Value*/
uint8 MCAL_ADC_StartConversionSynch(uint8 Channel , uint16* ADCReading);

/*Note this function doesn't support general interrupt enable you must enable it*/
uint8 MCAL_ADC_StartConversionAsynch(uint8 Channel , uint16* pADCReading , void (*pvNotificationFunc)(void));

/*Get Reading of ADC Chain*/
uint8 MCAL_ADC_StartChainConversion(ADC_Chain_t* ADC_Chain);

#endif  /* ADC_INTERFACE_H_ */
