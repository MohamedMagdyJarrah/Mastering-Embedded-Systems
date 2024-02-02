#include "driver.h"
#include "SensorModule.h"
#include "PressureDetection.h"
#include "AlarmMonitor.h"
#include "AlarmActuator.h"
#include "FlashMemory.h"

void InitModules(void);

int main (){
	int i,j;
	InitModules();

	while (1)
	{
		PS_State();
		PD_State();
		AM_State();
		AC_State();
		//		Delay(50000);

	}

}

void InitModules(void)
{
	/* Init all drivers needed  */
	/* Initialize state block diagram */
	PS_Init();
	AC_Init();
	FM_Init();

	/* Start with the first state in each module */
	PS_State = NextState(PS_Reading);
	PD_State = NextState(PD_Detection);
	AM_State = NextState(AM_AlarmOFF);
	AC_State = NextState(AC_Waiting);
	FM_State = NextState(FM_Storing);
}
