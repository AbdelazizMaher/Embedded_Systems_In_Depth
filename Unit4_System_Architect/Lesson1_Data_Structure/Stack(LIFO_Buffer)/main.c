/*
 * main.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "lifo.h"
#include <stdlib.h>


#define buffer1_length  5
element_type Buffer1[buffer1_length];

int main()
{
	LIFO_t stack1,stack2;
	uint8_t i;
	element_type temp =0;

	element_type* Buffer2 = (element_type*)malloc(5*sizeof(element_type));

	if( LIFO_Init(&stack1, Buffer1, buffer1_length) == LIFO_NO_ERROR)
		printf("STATIC STACK1 INIT ... DONE\n\n");

	if( LIFO_Init(&stack2, Buffer2 , 5) == LIFO_NO_ERROR)
		printf("DYNAMIC STACK2 INIT ... DONE\n\n");


	for( i = 0 ; i < 5 ; i++,temp++ )
	{
		if(LIFO_Push(&stack2,temp) == LIFO_NO_ERROR)
			printf("STACK2 PUSH : %d\n",temp);
	}

	for( i = 0 ; i < 5 ; i++ )
	{
		if(LIFO_Pop(&stack2,&temp) == LIFO_NO_ERROR)
			printf("STACK2 POP : %d\n",temp);
	}
    return 0;
}
