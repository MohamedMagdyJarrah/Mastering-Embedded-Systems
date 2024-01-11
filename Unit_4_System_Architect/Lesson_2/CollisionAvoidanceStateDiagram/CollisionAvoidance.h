#ifndef COLLISIONAVOIDANCE_H_
#define COLLISIONAVOIDANCE_H_

/****************************** Includes *************************************/
#include <stdio.h>
#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	CA_Waitng,
	CA_Driving
}CA_State_ID;

extern void (*CA_State)(void);

/********************************* APIs ***************************************/
STATE_Define(CA_Waitng);
STATE_Define(CA_Driving);

#endif /* COLLISIONAVOIDANCE_H_ */
