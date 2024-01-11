
#ifndef US_SENSOR_H_
#define US_SENSOR_H_

/****************************** Includes *************************************/
#include <stdio.h>
#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	US_Reading,
}US_State_ID;

extern void (*US_State)(void);

/********************************* APIs ***************************************/
void US_Init(void);
STATE_Define(US_Reading);

#endif /* US_SENSOR_H_ */
