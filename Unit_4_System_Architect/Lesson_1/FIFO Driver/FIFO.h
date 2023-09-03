/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC:    Circular Queue (FIFO)		******************/
/*****************		Version: 1.00 						******************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

/******************************************* Buffer Configurations *******************************************/
/* Put maximum size the buffer can reach */
#define MAXIMUM_FIFO_SIZE				15
/* Enter your buffer datatype from options
 *  ( uint8_t / uint16_t / uint32_t / uint64_t / sint8_t / sint16_t / sint32_t / sint64_t) */
#define ELEMENTS_TYPE					uint8_t

/* Buffer Structure */
typedef struct{
	ELEMENTS_TYPE data[MAXIMUM_FIFO_SIZE];
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint32_t count;
}FIFO_Buff_t;

/* FIFO Error States */
typedef enum{
	FIFO_No_Errors,
	FIFO_Full,
	FIFO_Empty,
	FIFO_Null
}FIFO_Status_t;

/**
  * @brief  This API initialize an empty queue with its head and tail pointers.
  * @param  (bufferSize) Queue maximum number of elements
  * @param  (buffer) pointer to queue structure
  * @retval Status returned while performing this operation
  */
FIFO_Status_t FIFO_InitQueue(FIFO_Buff_t* buffer,uint32_t bufferSize);

/**
  * @brief  This API enqueue an item in queue and increment head pointer and taking care for Circular queue concept.
  * @param  (item) item will be enqueued with datatype of ELEMENTS_TYPE Macro
  * @param  (buffer) pointer to queue structure
  * @retval Status returned while performing this operation
  */
FIFO_Status_t FIFO_EnqueueItem(FIFO_Buff_t* buffer,ELEMENTS_TYPE item);

/**
  * @brief  This API dequeue an item from queue and increment tail pointer and taking care for Circular queue concept.
  * @param  (item) item will be dequeued with datatype of ELEMENTS_TYPE Macro
  * @param  (buffer) pointer to queue structure
  * @retval Status returned while performing this operation
  */
FIFO_Status_t FIFO_DequeueItem(FIFO_Buff_t* buffer,ELEMENTS_TYPE* item);

/**
  * @brief  This API check if the queue is full or not.
  * @param  (buffer) pointer to queue structure
  * @retval Status returned while performing this operation
  */
FIFO_Status_t FIFO_QueueFull(FIFO_Buff_t* buffer);

/**
  * @brief  This API check if the queue is empty or not.
  * @param  (buffer) pointer to queue structure
  * @retval Status returned while performing this operation
  */
FIFO_Status_t FIFO_QueueEmpty(FIFO_Buff_t* buffer);

#endif /* FIFO_H_ */
