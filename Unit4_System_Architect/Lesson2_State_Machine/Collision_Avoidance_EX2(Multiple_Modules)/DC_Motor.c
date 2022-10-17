/*
 * DC_Motor.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Abdel
 */

#include "DC_Motor.h"


// Pointer to State fn.
void (*DC_STATE) ();

int DC_Speed;

void DC_Motor_Init()
{
	printf("DC INIT \n");
}

void Motor_SetSpeed(int Speed)
{
	DC_Speed = Speed;

	DC_STATE = STATE(DC_Busy);

	printf("CA ->>>>>> DC Motor_SetSpeed() = %d  \n" , DC_Speed);
}

STATE_define(DC_Idle)
{
	DC_State_Id = DC_IDLE;
	printf("DC_Idle State : DC_Speed = %d  \n" , DC_Speed);
}

STATE_define(DC_Busy)
{
	DC_State_Id = DC_BUSY;
	printf("DC_Busy State : DC_Speed = %d  \n" , DC_Speed);

	DC_STATE = STATE(DC_Idle);
}
