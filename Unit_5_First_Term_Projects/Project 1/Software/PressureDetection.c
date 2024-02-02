#include "PressureDetection.h"


/* Global variables used in the module */
int PressureValue = 0;
int Threshold = 20;

/* Pointer to function to point to the current state */
void (*PD_State)(void);

/************************* States Implementation ******************************/
STATE_Define(PD_Detection)
{
	/* Point to the current state */
	PD_State_ID = PD_Detection;

	/* State Action */
	if(PressureValue > Threshold)
	{
		HighPressureDetected();
//		printf("====================> High Pressure Detected <==================\n");
	}
	else
	{
//		printf("=================> No High Pressure Detected <================\n");
	}

	StorePressureInFlash(PressureValue);

	/* State Transitions */
	PD_State = NextState(PD_Detection);
}


void SetPressureVal(int PressureVal)
{
	PressureValue = PressureVal;
}

