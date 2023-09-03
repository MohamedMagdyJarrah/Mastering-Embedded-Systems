/*********************************************************************/
/*********************************************************************/
/*****************		Author: Mohamed Magdy		******************/
/*****************		Layer:  APP					******************/
/*****************		SWC:    Stack (LIFO )		******************/
/*****************		Version: 1.00 				******************/
/*********************************************************************/
/*********************************************************************/

#ifndef LIFO_H_
#define LIFO_H_

#include "Platform_Types.h"

/******************************************* Buffer Configurations *******************************************/
/* Put maximum size the buffer can reach */
#define MAX_BUFFER_SIZE			10
/* Enter your buffer datatype from options
 *  ( uint8_t / uint16_t / uint32_t / uint64_t / sint8_t / sint16_t / sint32_t / sint64_t) */
#define ELEMENTS_TYPE			uint8_t

/* Buffer Structure */
typedef struct{
	ELEMENTS_TYPE data[MAX_BUFFER_SIZE];
	sint32_t top;
	uint32_t size;
}LIFO_Buff_t;

/* LIFO Error States */
typedef enum{
	LIFO_NO_ERROR,
	LIFO_EMPTY,
	LIFO_FULL,
	LIFO_NULL,
}LIFO_Status_t;


/**
  * @brief  This API initialize an empty stack with its stack pointer.
  * @param  (bufferSize) Stack maximum number of elements
  * @param  (buffer) pointer to stack structure
  * @retval Status returned while performing this operation
  */
LIFO_Status_t LIFO_InitStack(LIFO_Buff_t* buffer, uint32_t bufferSize);

/**
  * @brief  This API push an item to the stack and let the stack pointer points to it.
  * @param  (item) item will be push with datatype of ELEMENTS_TYPE Macro
  * @param  (buffer) pointer to stack structure
  * @retval Status returned while performing this operation
  */
LIFO_Status_t LIFO_PushItem(LIFO_Buff_t* buffer,ELEMENTS_TYPE item);

/**
  * @brief  This API pop an item out of the stack and decrement the stack pointer.
  * @param  (item) pointer to item will be popped with datatype of ELEMENTS_TYPE Macro
  * @param  (buffer) pointer to stack structure
  * @retval Status returned while performing this operation
  */
LIFO_Status_t LIFO_PopItem(LIFO_Buff_t* buffer,ELEMENTS_TYPE* item);

/**
  * @brief  This API check if the stack is empty or not.
  * @param  (buffer) pointer to stack structure
  * @retval Status returned while performing this operation
  */
LIFO_Status_t LIFO_IsEmpty(LIFO_Buff_t* buffer);

/**
  * @brief  This API check if the stack is full or not.
  * @param  (buffer) pointer to stack structure
  * @retval Status returned while performing this operation
  */
LIFO_Status_t LIFO_IsFull(LIFO_Buff_t* buffer);


#endif
