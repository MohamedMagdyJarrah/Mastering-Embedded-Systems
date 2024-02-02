#include "AlarmActuator.h"

/* Pointer to function to point to the current state */
void (*AC_State)(void);

/************************* Initialization State ******************************/
void AC_Init(void)
{
	/* Initialize the alarm actuator */
	GPIO_INITIALIZATION();
}


/************************* States Implementation ******************************/
STATE_Define(AC_Waiting)
{
	/* Point to the current state */
	AC_State_ID = AC_Waiting;

	/* State action */

	/* State Transitions */
	AC_State = NextState(AC_Waiting);
}

STATE_Define(AC_AlarmOFF)
{
	/* Point to the current state */
	AC_State_ID = AC_AlarmOFF;

	/* State action */
//	printf("Alarm OFF\n");

	/* State Transitions */
	AC_State = NextState(AC_Waiting);
}

STATE_Define(AC_AlarmON)
{
	/* Point to the current state */
	AC_State_ID = AC_AlarmON;

	/* State action */

	/* State Transitions */
	AC_State = NextState(AC_Waiting);
}


void StartAlarm(void)
{
	Set_Alarm_actuator(1);
//	printf("Alarm ON\n");
	AC_State = NextState(AC_AlarmON);
}

void StopAlarm(void)
{
	Set_Alarm_actuator(0);
//	printf("Alarm OFF\n");
	AC_State = NextState(AC_AlarmOFF);
}
