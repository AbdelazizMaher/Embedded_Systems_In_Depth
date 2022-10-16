/*
 * main.c
 *
 *  Created on: October 16, 2022
 *      Author: Abdelaziz Maher
 */

#include "CA.h"

void Setup()
{
	CA_STATE = STATE(Waiting);
}

int main()
{
	volatile int i;

	Setup();

	while(1)
	{
		CA_STATE();

		for( i = 0 ; i < 1000 ; i++ );
	}

   return 0;
}
