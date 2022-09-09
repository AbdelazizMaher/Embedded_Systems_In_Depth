/*
 * lifo.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Abdel
 */

#ifndef LIFO_H_
#define LIFO_H_

#include "Platform_Types.h"
#include "stdio.h"

#define element_type    uint8_t

typedef struct
{
	element_type *base;
	element_type *head;
	uint8_t count;
	uint32_t length;
}LIFO_t;

typedef enum
{
	LIFO_NO_ERROR,
	LIFO_NULL,
	LIFO_EMPTY,
	LIFO_FULL
}LIFO_state;

LIFO_state LIFO_Init(LIFO_t* new ,element_type* pBuffer, uint32_t Length);
LIFO_state LIFO_Push(LIFO_t* push , element_type item );
LIFO_state LIFO_Pop(LIFO_t* pop, element_type* item);
LIFO_state LIFO_IsFull(LIFO_t* check);
void LIFO_print(LIFO_t* print);

#endif /* LIFO_H_ */
