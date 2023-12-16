/*
 * OS_Queue.h
 *
 *  Created on: Dec 13, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_OS_QUEUE_H_
#define INC_OS_QUEUE_H_

#include "OS_Scheduler.h"

#define element_type    sOS_Task_ControlBlock*

typedef struct
{
	element_type *base;
	element_type *head;
	element_type *tail;
	uint8_t count;
	uint32_t length;
}FIFO_t;

typedef enum
{
	FIFO_NO_ERROR,
	FIFO_NULL,
	FIFO_EMPTY,
	FIFO_FULL
}FIFO_state;

FIFO_state FIFO_Init(FIFO_t* new ,element_type* pBuffer, uint32_t Length);
FIFO_state FIFO_Enqueue(FIFO_t* add , element_type item );
FIFO_state FIFO_Dequeue(FIFO_t* remove, element_type* item);
FIFO_state FIFO_IsFull(FIFO_t* check);


#endif /* INC_OS_QUEUE_H_ */
