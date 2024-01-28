/*
 * AlaramActuator.h
 *
 *  Created on: Dec 27, 2022
 *      Author: Abdel
 */

#ifndef ALARMACTUATOR_H_
#define ALARMACTUATOR_H_

#include "state.h"
#include "driver.h"

enum
{
	ALARM_ACT_WAITING,
}AlaramActuator_ID;

void AlaramActuator_Init();

STATE_define(AlaramActuator_Waiting);


extern void (*ALARM_ACT_STATE) ();

#endif /* ALARMACTUATOR_H_ */
