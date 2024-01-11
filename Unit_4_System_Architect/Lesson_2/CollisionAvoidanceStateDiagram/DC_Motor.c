#include "DC_Motor.h"


/* Global variables used in the module */
int MOTOR_speed = 0;

/* Pointer to function to point to the current state */
void (*MOTOR_State)(void);


/* Initialization State */
void MOTOR_Init(void)
{
	/* Initialize the drivers used with motor like timer and configue the PWM */
	printf("DC Motor Initialization Done ....\n");
}


/************************* States Implementation ******************************/
STATE_Define(MOTOR_idle)
{
	/* Point to the current state */
	MOTOR_State_ID = MOTOR_idle;

	/* State Action */
	// Generate pwm according to the current speed

	/* State Transitions */
	printf("MOTOR_idle State: ======== Speed = %d ========\n",MOTOR_speed);
	MOTOR_State = NextState(MOTOR_idle);
}

STATE_Define(MOTOR_SpeedSetter)
{
	/* Point to the current state */
	MOTOR_State_ID = MOTOR_SpeedSetter;

	/* State Action */

	/* State Transitions */
	printf("MOTOR_SpeedSetter State: ======== Speed = %d ========\n",MOTOR_speed);

	MOTOR_State = NextState(MOTOR_idle);
}

void MOTOR_SetSpeed(int s)
{
	MOTOR_speed = s;
	MOTOR_State = NextState(MOTOR_SpeedSetter);
	printf("CA ------------ Speed = %d -----------------> MOTOR\n",MOTOR_speed);
}
