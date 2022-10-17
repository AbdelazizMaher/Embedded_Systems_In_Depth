/*
 * DC_Motor.h
 *
 *  Created on: Oct 17, 2022
 *      Author: Abdel
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "state.h"

// Define States
enum
{
	DC_IDLE,
	DC_BUSY
}DC_State_Id;

void DC_Motor_Init();

// Declare state fn.
STATE_define(DC_Idle);
STATE_define(DC_Busy);

// Pointer to State fn.
extern void (*DC_STATE) ();

#endif /* DC_MOTOR_H_ */
