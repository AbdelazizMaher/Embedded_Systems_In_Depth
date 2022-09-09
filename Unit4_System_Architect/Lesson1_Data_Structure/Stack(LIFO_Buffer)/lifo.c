/*
 * lifo.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Abdel
 */

#include "lifo.h"



LIFO_state LIFO_Init(LIFO_t* new ,element_type* pBuffer, uint32_t Length)
{
	if( !pBuffer )
		return LIFO_NULL;

	new->base = pBuffer;
	new->head = pBuffer;
	new->length = Length;
	new->count = 0;

	return LIFO_NO_ERROR;
}

LIFO_state LIFO_Push(LIFO_t* push , element_type item )
{
    if( LIFO_IsFull(push) == LIFO_FULL )
        return LIFO_FULL;
    else if( LIFO_IsFull(push) == LIFO_NULL )
    	return LIFO_NULL;

    *(push->head) = item;
    push->head++;
    push->count++;

	return LIFO_NO_ERROR;
}

LIFO_state LIFO_Pop(LIFO_t* pop, element_type* item)
{
    if( !(pop->base) || !(pop->head) )
        return LIFO_NULL;

    if(pop->count == 0)
        return LIFO_EMPTY;

    pop->head--;
    *item = *(pop->head);
    pop->count--;

    return LIFO_NO_ERROR;
}

LIFO_state LIFO_IsFull(LIFO_t* check)
{
    if( !(check->base) || !(check->head) )
        return LIFO_NULL;

    if( check->count == check->length )
    	return LIFO_FULL;

    return LIFO_NO_ERROR;
}

void LIFO_print(LIFO_t* print)
{
    element_type* temp = print->base;
    uint8_t i;
    if(print->count == 0)
    	printf("LIFO is empty\n");
    else
    {
    	printf("=========LIFO PRINT==========\n");
        for(i = 0 ; i < print->count ; i++ )
        {
            printf("%d\n", *temp);
            temp++;
        }
        printf("=============================\n");
    }

}


