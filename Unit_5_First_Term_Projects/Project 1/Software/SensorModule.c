#include "SensorModule.h"

/* Global variables used in the module */
int PressureVal = 0;
/* 100 seconds to poll on the sensor */
int pollingReadingTime = 100000;

/* Pointer to function to point to the current state */
void (*PS_State)(void);

/* Static function for test */
//static int GetRandomDistance(int min,int max);

/************************* Initialization State ******************************/
void PS_Init(void)
{
	/* Init Pressure Sensor Hardware */
	GPIO_INITIALIZATION();
}


/************************* States Implementation ******************************/
STATE_Define(PS_Reading)
{
	/* Point to the current state */
	PS_State_ID = PS_Reading;

	/* State Action */
//	PressureVal = GetRandomDistance(15,25);
	PressureVal = getPressureVal();
	SetPressureVal(PressureVal);

//	printf("PS_Reading -------- Pressure = %d ------> PS_Waiting\n",PressureVal);

	/* State Transitions */
	PS_State = NextState(PS_Waiting);
//	PS_State();
}


STATE_Define(PS_Waiting)
{
	/* Point to the current state */
	PS_State_ID = PS_Waiting;

	/* State Action */
//	Delay(pollingReadingTime);
//	printf("Sensor Waiting....\n");

	/* State Transitions */
	PS_State = NextState(PS_Reading);
}

/* For test */
/*static int GetRandomDistance(int min,int max)
{
	int ChoosenDist;

	ChoosenDist = (rand() % (max- min +1)) + min;

	return ChoosenDist;
}*/

