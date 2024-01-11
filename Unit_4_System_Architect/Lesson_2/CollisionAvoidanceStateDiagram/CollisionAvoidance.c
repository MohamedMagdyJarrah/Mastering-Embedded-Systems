#include "State.h"
#include "CollisionAvoidance.h"

/* Global variables used in the module */
int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;

/* Pointer to function to point to the current state */
void (*CA_State)(void);

/************************* States Implementation ******************************/
STATE_Define(CA_Waitng)
{
	/* Point to the current state */
	CA_State_ID = CA_Waitng;

	/* State Action */
	CA_speed = 0;
	MOTOR_SetSpeed(CA_speed);

	/* State Transitions */
	printf("CA_Waitng State: distance = %d , Speed = %d\n",CA_distance,CA_speed);
}

STATE_Define(CA_Driving)
{
	/* Point to the current state */
	CA_State_ID = CA_Driving;

	/* State Action */
	CA_speed = 30;
	MOTOR_SetSpeed(CA_speed);

	/* State Transitions */
	printf("CA_Driving State: distance = %d , Speed = %d\n",CA_distance,CA_speed);
}

void US_GetDistance(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold) ? (CA_State = NextState(CA_Waitng)) : (CA_State = NextState(CA_Driving)) ;
	printf("US ------------ Distance = %d -----------------> CA\n",CA_distance);
}

