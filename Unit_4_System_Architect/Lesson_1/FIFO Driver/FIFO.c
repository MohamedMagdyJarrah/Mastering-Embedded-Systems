/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC:    Circular Queue (FIFO)		******************/
/*****************		Version: 1.00 						******************/
/*****************************************************************************/
/*****************************************************************************/
#include "Platform_Types.h"
#include "FIFO.h"

FIFO_Status_t FIFO_InitQueue(FIFO_Buff_t* buffer,uint32_t bufferSize)
{
	FIFO_Status_t returnState = FIFO_No_Errors;
	if(!buffer)						/* Check if the buffer is a null pointer or not */
	{
		returnState = FIFO_Null;
	}
	else
	{

		buffer->size = bufferSize;		/* Initialize the size of the buffer */
		buffer->count = 0;				/* Initialize the count of the buffer */
		/* Initialize the head and tail pointers of the buffer */
		buffer->head = -1;
		buffer->tail = -1;
	}
	return returnState;
}

FIFO_Status_t FIFO_EnqueueItem(FIFO_Buff_t* buffer,ELEMENTS_TYPE item)
{
	FIFO_Status_t returnState = FIFO_No_Errors;
	if(!buffer)
	{
		returnState = FIFO_Null;
	}
	else if(FIFO_Full == FIFO_QueueFull(buffer))
	{
		returnState = FIFO_Full;
	}
	else
	{
		if(FIFO_Empty == FIFO_QueueEmpty(buffer))	/* If the first enqueue is when the queue is empty we need to increment head and tail */
		{
			(buffer->head)++;
			(buffer->tail)++;
		}
		else
		{
			(buffer->head)++;
			/* If the head reach the end of the queue we will start from beginng of queue (Cricular Queue) */
			if( buffer->head == (buffer->size) )
			{
				buffer->head = 0;
			}
		}
		buffer->data[buffer->head] = item;	/* Enqueue the item to the new place in the queue */
		(buffer->count)++;
	}

	return returnState;
}

FIFO_Status_t FIFO_DequeueItem(FIFO_Buff_t* buffer,ELEMENTS_TYPE* item)
{
	FIFO_Status_t returnState = FIFO_No_Errors;
	if(!buffer)
	{
		returnState = FIFO_Null;
	}
	else if(FIFO_Empty == FIFO_QueueEmpty(buffer))
	{
		returnState = FIFO_Empty;
	}
	else
	{
		*item = buffer->data[buffer->tail]; /* Dequeue the item from the its place in the queue */
		(buffer->tail)++;
		/* If the tail reach the end of the queue we will start from beginng of queue (Cricular Queue) */
		if( buffer->tail == (buffer->size) )
		{
			buffer->tail = 0;
		}
		(buffer->count)--;
	}

	return returnState;
}

FIFO_Status_t FIFO_QueueFull(FIFO_Buff_t* buffer)
{
	return (buffer->count == buffer->size) ? FIFO_Full : FIFO_No_Errors;
}

FIFO_Status_t FIFO_QueueEmpty(FIFO_Buff_t* buffer)
{
	return (buffer->count == 0) ? FIFO_Empty : FIFO_No_Errors;
}
