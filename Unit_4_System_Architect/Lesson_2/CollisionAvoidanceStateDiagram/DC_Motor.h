

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/****************************** Includes *************************************/
#include <stdio.h>
#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	MOTOR_idle,
	MOTOR_SpeedSetter
}MOTOR_State_ID;

extern void (*MOTOR_State)(void);

/********************************* APIs ***************************************/
void MOTOR_Init(void);
STATE_Define(MOTOR_idle);
STATE_Define(MOTOR_SpeedSetter);



#endif /* DC_MOTOR_H_ */
