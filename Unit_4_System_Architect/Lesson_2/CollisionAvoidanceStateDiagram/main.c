#include "US_Sensor.h"
#include "DC_Motor.h"
#include "CollisionAvoidance.h"

void Modules_Setup(void)
{
	/* Initialize all the drivers needed */
	/* Initialize the interrupts if occurs */
	/* Initialize state block diagram */
	US_Init();
	MOTOR_Init();
	/* Start with the first state in each module */
	US_State = NextState(US_Reading);
	CA_State = NextState(CA_Waitng);
	MOTOR_State = NextState(MOTOR_idle);
}


int main(void)
{
	volatile int i = 0 , j=0;
	Modules_Setup();

	while(1)
	{
		US_State();
		CA_State();
		MOTOR_State();
		for(i= 0 ; i<60000; i++)
		{
			for(j= 0 ; j<600; j++);
		}

	}

	return 0;
}
