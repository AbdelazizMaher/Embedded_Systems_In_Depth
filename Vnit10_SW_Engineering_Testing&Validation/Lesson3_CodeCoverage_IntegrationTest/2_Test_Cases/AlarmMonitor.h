/*
 * AlarmMonitor.h
 *
 *  Created on: Dec 27, 2022
 *      Author: Abdel
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_

#include "state.h"
#include "driver.h"

enum
{
	ALARM_OFF,
	ALARM_ON,
	ALARM_WAITING
}Alarm_Monitor_ID;


STATE_define(AlarmOFF);
STATE_define(AlarmON);
STATE_define(Alarm_Waiting);


extern void (*ALARM_MONITOR_STATE) ();

#endif /* ALARMMONITOR_H_ */
