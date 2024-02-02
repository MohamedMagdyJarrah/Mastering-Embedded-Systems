#ifndef ALARMACTUATOR_ALARMACTUATOR_H_
#define ALARMACTUATOR_ALARMACTUATOR_H_

/****************************** Includes *************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	AC_Waiting,
	AC_AlarmOFF,
	AC_AlarmON
}AC_State_ID;

extern void (*AC_State)(void);

/********************************* APIs ***************************************/
void AC_Init(void);
STATE_Define(AC_Waiting);
STATE_Define(AC_AlarmOFF);
STATE_Define(AC_AlarmON);

#endif /* ALARMACTUATOR_ALARMACTUATOR_H_ */
