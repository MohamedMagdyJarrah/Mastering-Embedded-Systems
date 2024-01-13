/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    EXTI			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/ATMEGA32_MemMap.h"

/*=============================================================================================
 * 									Pre-Build Configuration
 *=============================================================================================*/
/********************* Interrupt Initial Sense Control Configuration: ***********************************
 **************** 	For Low Level interrupt sense control put EXTI_LOW_LEVEL 	    *********************
 ****************	For On Change interrupt sense control put EXTI_ON_CHANGE 	    *********************
 **************** 	For Falling edge interrupt sense control put EXTI_FALLING_EDGE   ********************
 **************** 	For Rising edge interrupt sense control put EXTI_RISING_EDGE     ********************
 ********************************************************************************************************/
#define INT0_SENSE_CONTROL		EXTI_FALLING_EDGE
#define INT1_SENSE_CONTROL		EXTI_FALLING_EDGE
#define INT2_SENSE_CONTROL		EXTI_FALLING_EDGE

/**********************    Peripheral Interrupt Initial state Configuration:     ************************
 **************** 	To initialize Peripheral Interrupt with Enable  put EXTI_ENABLED 	*****************
 ****************	To initialize Peripheral Interrupt with Disable put EXTI_DISABLED 	*****************
 ******************************************************************************************************* */
#define INT0_INITIAL_STATE 		EXTI_ENABLED
#define INT1_INITIAL_STATE 		EXTI_DISABLED
#define INT2_INITIAL_STATE 		EXTI_DISABLED



/*=======================================================================================
 * 						APIs supported by "MCAL EXTI Driver"
 *=======================================================================================*/
/*Description : Functions to set the required Configuration for INTx using Pre-Build Configuration */
void MCAL_EXTI_INT0Init(void);
void MCAL_EXTI_INT1Init(void);
void MCAL_EXTI_INT2Init(void);

/*Description : Function to set the required Sense Control for INTx using Post-Build Configuration
 * Input:   Copy_u8INT  , 	Copy_u8SenseControl
 * Options: 1-INT0			1-EXTI_LOW_LEVEL
 *          2-INT1			2-EXTI_ON_CHANGE
 *          3-INT2			3-EXTI_FALLING_EDGE
 *          				4-EXTI_RISING_EDGE
 * Output: Error status with type uint8
 *   */
uint8 MCAL_EXTI_INTSetSenseControl(uint8 Copy_INT ,uint8 Copy_SenseControl);

/*Description : Functions to Enable or Disable INTX using Post-Build Configuration
 * Input:   Copy_u8INT
 * Options: 1-INT0
 *          2-INT1
 *          3-INT2
 * Output: Error status with type uint8
 *   */
uint8 MCAL_EXTI_INTEnable(uint8 Copy_INT);
uint8 MCAL_EXTI_INTDisable(uint8 Copy_INT);

/*Description : Functions to send ISR Function of INTX to implement it with its vector table number
 * Input:   (*Copy_pvINTx_ISR)(void)    --->   (x = 0,1,2)
 * Output: Error status with type uint8
 *   */
uint8 MCAL_EXTI_INT0SetCallBack(void (*Copy_pvINT0_ISR)(void));
uint8 MCAL_EXTI_INT1SetCallBack(void (*Copy_pvINT1_ISR)(void));
uint8 MCAL_EXTI_INT2SetCallBack(void (*Copy_pvINT2_ISR)(void));


#endif
