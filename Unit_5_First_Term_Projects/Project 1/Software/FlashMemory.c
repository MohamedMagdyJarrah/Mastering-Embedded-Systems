#include "FlashMemory.h"

/* Global variables used in the module */
int valueStored = 0;

/* Pointer to function to point to the current state */
void (*FM_State)(void);


/************************* Initialization State ******************************/
void FM_Init(void)
{
	/* Init Pressure Sensor Hardware */
	GPIO_INITIALIZATION();
}


/************************* States Implementation ******************************/
STATE_Define(FM_Storing)
{
	/* Point to the current state */
	FM_State_ID = FM_Storing;

	/* State action */
//	printf(" Pressure = %d is stored in the flash \n",valueStored);

	/* State Transitions */
	FM_State = NextState(FM_Storing);
}

void StorePressureInFlash(int PressureVal)
{
	valueStored = PressureVal;
}
