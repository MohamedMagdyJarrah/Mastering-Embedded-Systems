#ifndef FLASHMEMORY_FLASHMEMORY_H_
#define FLASHMEMORY_FLASHMEMORY_H_

/****************************** Includes *************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include "State.h"

/***************************** Decelerations **********************************/
enum{
	FM_Storing
}FM_State_ID;

extern void (*FM_State)(void);

/********************************* APIs ***************************************/
void FM_Init(void);
STATE_Define(FM_Storing);


#endif /* FLASHMEMORY_FLASHMEMORY_H_ */
