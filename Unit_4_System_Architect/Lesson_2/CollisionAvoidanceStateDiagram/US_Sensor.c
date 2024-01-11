#include "US_Sensor.h"

/* Global variables used in the module */
int US_distance = 0;

/* Pointer to function to point to the current state */
void (*US_State)(void);

/* Prototype of Internal Functions */
static int GetRandomDistance(int min,int max);

/* Initialization State */
void US_Init(void)
{
	/* Initialize the drivers used in ultrasonic like timer and configue the ICU */
	printf("Ultrasonic Initialization Done ....\n");
}

/************************* States Implementation ******************************/
STATE_Define(US_Reading)
{
	/* Point to the current state */
	US_State_ID = US_Reading;

	/* State Action */
	US_distance = GetRandomDistance(45,55);
	US_GetDistance(US_distance);

	/* State Transitions */
	printf("US_Reading State: ======== distance = %d ========\n",US_distance);

	US_State = NextState(US_Reading);
}

static int GetRandomDistance(int min,int max)
{
	int ChoosenDist;

	ChoosenDist = (rand() % (max- min +1)) + min;

	return ChoosenDist;
}
