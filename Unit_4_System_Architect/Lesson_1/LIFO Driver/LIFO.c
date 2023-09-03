/*********************************************************************/
/*********************************************************************/
/*****************		Author: Mohamed Magdy		******************/
/*****************		Layer:  APP					******************/
/*****************		SWC:    Stack (LIFO )		******************/
/*****************		Version: 1.00 				******************/
/*********************************************************************/
/*********************************************************************/

#include "LIFO.h"

LIFO_Status_t LIFO_InitStack(LIFO_Buff_t* buffer , uint32_t bufferSize)
{
	LIFO_Status_t returnStatus = LIFO_NO_ERROR;
	if(!buffer)							/* Check if the buffer is a null pointer or not */
	{
		returnStatus = LIFO_NULL;
	}
	else
	{
		buffer->size = bufferSize;		/* Initialize the size of the buffer */
		buffer->top = -1;				/* Initialize the stack pointer when the stack is empty */
	}
	return returnStatus;
}

LIFO_Status_t LIFO_IsEmpty(LIFO_Buff_t* buffer)
{
	return ( -1 == buffer->top ) ? LIFO_EMPTY : LIFO_NO_ERROR;
}

LIFO_Status_t LIFO_IsFull(LIFO_Buff_t* buffer)
{
	return ( (buffer->size)-1 == buffer->top ) ? LIFO_FULL : LIFO_NO_ERROR;
}


LIFO_Status_t LIFO_PushItem(LIFO_Buff_t* buffer,ELEMENTS_TYPE item)
{
	LIFO_Status_t returnStatus = LIFO_NO_ERROR;
	if(!buffer)
	{
		returnStatus = LIFO_NULL;
	}
	else if(LIFO_IsFull(buffer) == LIFO_FULL)
	{
		returnStatus = LIFO_FULL;
	}
	else
	{
		(buffer->top)++;					/* Increment the stack pointer to the next element we push an item */
		buffer->data[buffer->top] = item;	/* Push the item to the new place in the stack */
	}
	return returnStatus;
}

LIFO_Status_t LIFO_PopItem(LIFO_Buff_t* buffer,ELEMENTS_TYPE* item)
{
	LIFO_Status_t returnStatus = LIFO_NO_ERROR;
	if(!buffer)
	{
		returnStatus = LIFO_NULL;
	}
	else if(LIFO_IsEmpty(buffer) == LIFO_EMPTY)
	{
		returnStatus = LIFO_EMPTY;
	}
	else
	{
		*item = buffer->data[buffer->top];	/* First save the item popped from the stack */
		(buffer->top)--;					/* Then decrement the stack pointer to previous element */
	}
	return returnStatus;
}


