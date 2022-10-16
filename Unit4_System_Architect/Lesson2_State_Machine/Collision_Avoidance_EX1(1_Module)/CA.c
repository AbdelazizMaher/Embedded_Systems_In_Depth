/*
 * CA.c
 *
 *  Created on: Oct 16, 2022
 *      Author: Abdelaziz Maher
 */


#include "CA.h"


int Speed;
int Distance;
int Threshold = 50 ;

// Pointer to State fn.
void (*CA_STATE) ();

int generate_random(int l ,int r , int count)
{
	int i , rand_num = 0;

	for( i = 0 ; i < count ; i++ )
	{
	    rand_num =(rand() % (r - l + 1 )) + 45;
	    return rand_num;
	}
	return rand_num;
}



STATE_define(Waiting)
{
	CA_State_Id = CA_WAITING;
	Speed = 0;
	Distance = generate_random(45,55,1);

	( Distance <= Threshold )	? ( CA_STATE = STATE(Waiting) ) : ( CA_STATE = STATE(Driving) );
	printf("Waiting State: Speed = %d , Distance = %d \n" , Speed, Distance);
}

STATE_define(Driving)
{
	CA_State_Id = CA_DRIVING;
	Speed = 30;
	Distance = generate_random(45,55,1);

	( Distance <= Threshold )	? ( CA_STATE = STATE(Waiting) ) : ( CA_STATE = STATE(Driving) );
	printf("Driving State: Speed = %d , Distance = %d \n" , Speed, Distance);
}

