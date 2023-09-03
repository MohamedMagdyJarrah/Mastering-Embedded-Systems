/*********************************************************************/
/*********************************************************************/
/*****************		Author: Mohamed Magdy		******************/
/*****************		Layer:  APP					******************/
/*****************		SWC:    Stack (LIFO )		******************/
/*****************		Version: 1.00 				******************/
/*********************************************************************/
/*********************************************************************/

#include "Platform_Types.h"
#include <stdio.h>
#include "LIFO.h"

void LIFO_IntegersDisplay(LIFO_Buff_t* buffer, char* bufferName);

int main(void)
{
	LIFO_Buff_t LIFO_UART;
	uint8_t stackSize = 7 , poppedItem;

	LIFO_InitStack(&LIFO_UART,stackSize);

	//padding LIFO UART Buffer by its values
	for( int i=0 ; i<stackSize ; i++ )
	{
		LIFO_PushItem( &LIFO_UART , i );
	}

	LIFO_IntegersDisplay(&LIFO_UART,"LIFO_UART");


	for( int i=0 ; i<3 ; i++ )
	{
		LIFO_PopItem( &LIFO_UART , &poppedItem );
	}

	LIFO_IntegersDisplay(&LIFO_UART,"LIFO_UART");

	return 0;
}


void LIFO_IntegersDisplay(LIFO_Buff_t* buffer , char* bufferName)
{
	uint32_t i;
	if(LIFO_IsEmpty(buffer) == LIFO_EMPTY)
	{
		printf("%s is empty\n",bufferName);
	}
	else
	{
		printf("The %s contains: ",bufferName);
		for(i=0; i<= buffer->top;i++)
		{
			printf("%d ",buffer->data[i]);
		}
		printf("\n");
	}
}
