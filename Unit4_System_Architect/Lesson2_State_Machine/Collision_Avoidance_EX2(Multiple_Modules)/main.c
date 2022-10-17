/*
 * main.c
 *
 *  Created on: October 17, 2022
 *      Author: Abdelaziz Maher
 */

#include "CA.h"
#include "US_Sensor.h"
#include "DC_Motor.h"


void Setup()
{
	US_Init();
	DC_Motor_Init();

	CA_STATE = STATE(Waiting);
	DC_STATE = STATE(DC_Idle);
	US_STATE = STATE(US_Busy);
}

int main()
{
	volatile int i;

	Setup();

	while(1)
	{
		US_STATE();
		CA_STATE();
		DC_STATE();

		for( i = 0 ; i < 1000 ; i++ );
	}

   return 0;
}
