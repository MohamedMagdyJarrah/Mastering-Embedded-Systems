/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/*********************************************** Includes **********************************************/
#include "../../LIB/Platform_Types.h"
#include "../../LIB/Utils.h"
#include "../../LIB/ATMEGA32_MemMap.h"
#include <math.h>

/*=============================================================================================
 * 									Pre-Build Configuration
 *=============================================================================================*/
/*Setting System Frequency*/
#define SYSTEM_FREQUENCY					8000000UL

/*Choosing Timer/Counter mode*/
/*Options:
 * 1-NORMAL
 * 2-PWM_PHASE_CORRECT
 * 3-CTC
 * 4-FAST_PWM
 * */
#define TIMER_COUNTER0_MODE					FAST_PWM			//Timer 0 Mode


/*Clock bits selection*/
/*Options:
 * 1-NO_CLK_SOURCE
 * 2-NO_PRESCALING
 * 3-PRESCALER_8_BIT
 * 4-PRESCALER_64_BIT
 * 5-PRESCALER_256_BIT
 * 6-PRESCALER_1024_BIT
 * 7-EXT_CLK_FALLING_EDGE
 * 8-EXT_CLK_RISING_EDGE
 * */
#define CLK_SELECTION_TIMER0				PRESCALER_8_BIT


/*=======================================================================================
 * 						APIs supported by "MCAL Timers Driver"
 *=======================================================================================*/
void MCAL_TIMER0_Init(void);

/* Normal mode APIs */
uint8 MCAL_TIMER0_SetOverflowCallBack(void(*pv_NotifcationFunc)(void));
uint8 MCAL_TIMER0_SetCompareMatchCallBack(void(*pv_NotifcationFunc)(void));
void MCAL_TIMER0_StartTimeMs_BusyWait(uint64 timeInMilli);
void MCAL_TIMER0_StartTimeMS_Asynch(uint64 timeInMilli);
void MCAL_TIMER0_stopTimer(void);

/* CTC mode APIs */
/* You should configure TIMER_COUNTER0_MODE to be CTC also put the freq. in kilo */
void MCAL_TIMER0_GenerateSquareWave(uint16 frequency);

/* PWM mode APIs */
void MCAL_TIMER0_GeneratePwmSignal(uint8 onPeriodTicks);


#endif
