/*
 * main.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "fifo.h"

#define dummybuffer_length  5
element_type DummyBuffer[dummybuffer_length];

int main()
{
    FIFO_t DummyFIFO;
    uint8_t i;
    element_type temp=0;

    if( FIFO_Init(&DummyFIFO , DummyBuffer , dummybuffer_length ) == FIFO_NO_ERROR)
    	printf("FIFO INIT ... DONE\n\n");

    for( i = 0 ; i < 7 ; i++, temp++ )
    {
    	if( FIFO_Enqueue(&DummyFIFO , temp ) == FIFO_NO_ERROR )
    		printf("FIFO Enqueue (%d) ... DONE\n", temp);
    	else
    		printf("FIFO Enqueue (%d) ... FAILED\n", temp);
    }

    FIFO_print(&DummyFIFO);

    for( i = 0 ; i < 2 ; i++ )
    {
    	if( FIFO_Dequeue(&DummyFIFO, &temp) == FIFO_NO_ERROR )
    		printf("FIFO Dequeue (%d) ... DONE\n", temp);
    	else
    		printf("FIFO Dequeue ... FAILED\n");
    }

    FIFO_print(&DummyFIFO);

    return 0;
}
