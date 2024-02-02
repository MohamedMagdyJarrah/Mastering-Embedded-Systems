#include "AlarmMonitor.h"

/* Global variables used in the module */
int AlarmTimePeriod = 60000;

/* Pointer to function to point to the current state */
void (*AM_State)(void);

/************************* States Implementation ******************************/
STATE_Define(AM_AlarmOFF)
{
	/* Point to the current state */
	AM_State_ID = AM_AlarmOFF;

	/* State Action */
	StopAlarm();

//	printf("=======> Alarm stopped <=======\n");

	/* State Transitions */
	AM_State = NextState(AM_AlarmOFF);
}

STATE_Define(AM_AlarmON)
{
	/* Point to the current state */
	AM_State_ID = AM_AlarmON;

	/* State Action */
//	printf("=======> Alarm started <=======\n");
	StartAlarm();
	Delay(AlarmTimePeriod);
	/* State Transitions */
	AM_State = NextState(AM_Waiting);
//	AM_State();
}


STATE_Define(AM_Waiting)
{
	/* Point to the current state */
	AM_State_ID = AM_Waiting;

	/* State Action */
	/* Start timer for 60 seconds */
//	printf("=======> Alarm Waiting.... <=======\n");
	Delay(AlarmTimePeriod);

	/* State Transitions */
	AM_State = NextState(AM_AlarmOFF);
//	AM_State();
}

void HighPressureDetected(void)
{
	AM_State = NextState(AM_AlarmON);
}
