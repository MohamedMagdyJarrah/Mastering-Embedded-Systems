#ifndef ALARMMONITOR_ALARMMONITOR_H_
#define ALARMMONITOR_ALARMMONITOR_H_

/****************************** Includes *************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	AM_AlarmOFF,
	AM_AlarmON,
	AM_Waiting,
}AM_State_ID;

extern void (*AM_State)(void);

/********************************* APIs ***************************************/
STATE_Define(AM_AlarmOFF);
STATE_Define(AM_AlarmON);
STATE_Define(AM_Waiting);

#endif /* ALARMMONITOR_ALARMMONITOR_H_ */
