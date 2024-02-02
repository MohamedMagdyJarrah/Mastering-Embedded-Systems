#ifndef PRESSUREDETECTION_PRESSUREDETECTION_H_
#define PRESSUREDETECTION_PRESSUREDETECTION_H_

/****************************** Includes *************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	PD_Detection
}PD_State_ID;

extern void (*PD_State)(void);

/********************************* APIs ***************************************/
STATE_Define(PD_Detection);


#endif /* PRESSUREDETECTION_PRESSUREDETECTION_H_ */
