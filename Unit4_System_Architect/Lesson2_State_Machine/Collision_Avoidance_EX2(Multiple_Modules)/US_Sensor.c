/*
 * US_Sensor.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Abdel
 */

#include "US_Sensor.h"

// Pointer to State fn.
void (*US_STATE) ();

int US_Distance;

void US_Init()
{
	printf("US INIT \n");
}

int US_GetRandDistance(int l ,int r , int count)
{
	int i , rand_num = 0;

	for( i = 0 ; i < count ; i++ )
	{
		rand_num =(rand() % (r - l + 1 )) + 45;
	    return rand_num;
	}
	return rand_num;
}

STATE_define(US_Busy)
{
	US_State_Id = US_BUSY;

	US_Distance = US_GetRandDistance(45,55,1);
	printf("US_Busy State : US_Distance = %d  \n" , US_Distance);
	US_GetDistance(US_Distance);

	US_STATE = STATE(US_Busy);
}
