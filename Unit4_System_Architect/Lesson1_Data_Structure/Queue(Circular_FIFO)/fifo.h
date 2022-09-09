/*
 * fifo.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Abdelaziz Maher
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "Platform_Types.h"
#include "stdio.h"

#define element_type    uint8_t

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
void FIFO_print(FIFO_t* print);

#endif /* FIFO_H_ */
