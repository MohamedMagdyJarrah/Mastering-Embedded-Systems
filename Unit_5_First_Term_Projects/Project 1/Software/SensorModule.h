#ifndef PRESSURESENSOR_SENSORMODULE_H_
#define PRESSURESENSOR_SENSORMODULE_H_

/****************************** Includes *************************************/
#include <stdio.h>
#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	PS_Reading,
	PS_Waiting
}PS_State_ID;

extern void (*PS_State)(void);

/********************************* APIs ***************************************/
void PS_Init(void);
STATE_Define(PS_Reading);
STATE_Define(PS_Waiting);

#endif /* PRESSURESENSOR_SENSORMODULE_H_ */
