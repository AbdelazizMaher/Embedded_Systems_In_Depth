/*
 * AlarmMonitor.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Abdel
 */

#include "AlarmMonitor.h"


int AlarmDuration = 60;

void (*ALARM_MONITOR_STATE) ();

void Detect_HighPressure()
{
	//if ( ALARM_MONITOR_STATE != STATE(Alarm_Waiting) )
		ALARM_MONITOR_STATE = STATE(AlarmON);
}

STATE_define(AlarmOFF)
{
	Alarm_Monitor_ID = ALARM_OFF;

	StopAlarm();

}


STATE_define(AlarmON)
{
	Alarm_Monitor_ID = ALARM_ON;

	StartAlarm();

	ALARM_MONITOR_STATE = STATE(Alarm_Waiting);
}


STATE_define(Alarm_Waiting)
{
	Alarm_Monitor_ID = ALARM_WAITING;

	//Delay(6000);
	StopAlarm();

	ALARM_MONITOR_STATE = STATE(AlarmOFF);

}
