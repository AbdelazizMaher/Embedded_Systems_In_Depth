/*
 * CA.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Abdelaziz Maher
 */


#include "CA.h"


int CA_Speed;
int CA_Distance;
int CA_Threshold = 50 ;

// Pointer to State fn.
void (*CA_STATE) ();


void US_GetDistance(int Distance)
{
	CA_Distance = Distance;

	( CA_Distance <= CA_Threshold )	? ( CA_STATE = STATE(Waiting) ) : ( CA_STATE = STATE(Driving) );

	printf("US ->>>>>> CA Get_Distance() = %d  \n" , CA_Distance);
}


STATE_define(Waiting)
{
	CA_State_Id = CA_WAITING;

	printf("CA_Waiting State: Speed = %d , Distance = %d \n" , CA_Speed, CA_Distance);

	CA_Speed = 0;
	Motor_SetSpeed(CA_Speed);
}

STATE_define(Driving)
{
	CA_State_Id = CA_DRIVING;

	printf("CA_Driving State: Speed = %d , Distance = %d \n" , CA_Speed, CA_Distance);

	CA_Speed = 30;
	Motor_SetSpeed(CA_Speed);
}

