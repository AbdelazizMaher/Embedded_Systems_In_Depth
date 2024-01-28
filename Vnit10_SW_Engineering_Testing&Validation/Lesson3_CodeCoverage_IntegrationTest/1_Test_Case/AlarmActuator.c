/*
 * AlarmActuator.c
 *
 *  Created on: Dec 27, 2022
 *      Author: Abdel
 */

#include "AlarmActuator.h"

int AlarmFlag = 0;

void (*ALARM_ACT_STATE) ();

void AlaramActuator_Init()
{
	ALARM_ACT_STATE = STATE(AlaramActuator_Waiting);
}


void StartAlarm()
{
	AlarmFlag = 1;
	
}


void StopAlarm()
{
	AlarmFlag = 0;
	
}


STATE_define(AlaramActuator_Waiting)
{
	AlaramActuator_ID = ALARM_ACT_WAITING;

	if( AlarmFlag == 0)
		Set_Alarm_actuator(1);
	else
		Set_Alarm_actuator(0);

	ALARM_ACT_STATE = STATE(AlaramActuator_Waiting);
}
