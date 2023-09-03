/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC:    Circular Queue (FIFO)		******************/
/*****************		Version: 1.00 						******************/
/*****************************************************************************/
/*****************************************************************************/
#include <stdio.h>
#include "Platform_Types.h"
#include "FIFO.h"

void FIFO_IntegersDisplay(FIFO_Buff_t* buffer , char* bufferName);

int main(void)
{
	FIFO_Buff_t queue;
	uint8_t queueSize = 10 , i , dequeuedItem;

	FIFO_InitQueue(&queue,queueSize);

	FIFO_IntegersDisplay(&queue,"1st Buffer");
	printf("==============================================================\n");

	for(i=0; i<queueSize ; i++)
	{
		FIFO_EnqueueItem(&queue,i+1);
		printf("Enqueued %d\n",i+1);
	}
	FIFO_IntegersDisplay(&queue,"2nd Buffer");
	printf("==============================================================\n");

	for(i=0; i<5 ; i++)
	{
		FIFO_DequeueItem(&queue,&dequeuedItem);
		printf("Dequeued %d\n",dequeuedItem);
	}
	FIFO_IntegersDisplay(&queue,"3rd Buffer");
	printf("==============================================================\n");

	FIFO_EnqueueItem(&queue,20);
	printf("Enqueued %d\n",20);
	FIFO_EnqueueItem(&queue,60);
	printf("Enqueued %d\n",60);
	FIFO_IntegersDisplay(&queue,"4th Buffer");
	printf("==============================================================\n");

	FIFO_DequeueItem(&queue,&dequeuedItem);
	printf("Dequeued %d\n",dequeuedItem);
	FIFO_DequeueItem(&queue,&dequeuedItem);
	printf("Dequeued %d\n",dequeuedItem);
	FIFO_IntegersDisplay(&queue,"5th Buffer");
	return 0;
}


void FIFO_IntegersDisplay(FIFO_Buff_t* buffer , char* bufferName)
{
	uint32_t i;
	if(FIFO_QueueEmpty(buffer) == FIFO_Empty)
	{
		printf("%s is empty\n",bufferName);
	}
	else
	{
		printf("The %s contains: ",bufferName);
		i= buffer->tail;
		while(i-1 != buffer->head)
		{
			if(i == (buffer->size))
			{
				i = 0;
			}
			printf("%d ",buffer->data[i]);
			i++;
		}
		printf("\n");
	}
}
