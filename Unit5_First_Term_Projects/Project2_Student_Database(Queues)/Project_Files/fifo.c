/*
 * fifo.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Abdelaziz Maher
 */
#include "fifo.h"



FIFO_state FIFO_Init(FIFO_t* new ,element_type* pBuffer, uint32_t Length)
{
	if( !pBuffer )
		return FIFO_NULL;

	new->base = pBuffer;
	new->head = pBuffer;
	new->tail = pBuffer;
	new->length = Length;
	new->count = 0;

	return FIFO_NO_ERROR;
}

FIFO_state FIFO_Enqueue(FIFO_t* add , element_type item )
{
    if( FIFO_IsFull(add) == FIFO_FULL )
        return FIFO_FULL;
    else if( FIFO_IsFull(add) == FIFO_NULL )
    	return FIFO_NULL;

    *(add->head) = item;
    add->count++;

    if( add->head == ( add->base + ( add->length)  ) )
    	add->head = add->base;
    else
    	{add->head++;}

	return FIFO_NO_ERROR;
}

FIFO_state FIFO_Dequeue(FIFO_t* remove, element_type item)
{
    if( !(remove->base) || !(remove->head) || !(remove->tail) )
        return FIFO_NULL;

    if(remove->count == 0)
        return FIFO_EMPTY;

    item = *(remove->tail);
    remove->count--;

    if( remove->tail == ( remove->base + ( remove->length) ) )
    	remove->tail = remove->base;
    else
    	remove->tail++;

    return FIFO_NO_ERROR;
}

FIFO_state FIFO_IsFull(FIFO_t* check)
{
    if( !(check->base) || !(check->head) || !(check->tail) )
        return FIFO_NULL;

    if( check->count == check->length )
    	return FIFO_FULL;

    return FIFO_NO_ERROR;
}

void FIFO_print(FIFO_t* print)
{
    element_type* temp = print->tail;
    uint8_t i;
    if(print->count == 0)
    	printf("FIFO EMPTY\n");
    else
    {
    	printf("=========FIFO PRINT==========\n");
        for(i = 0 ; i < print->count ; i++ )
        {
            if( temp == ( print->base + ( print->length*sizeof(element_type) ) ) )
            	temp = print->base;
            printf("%d\n", *temp);
            temp++;
        }
        printf("=============================\n");
    }
}

