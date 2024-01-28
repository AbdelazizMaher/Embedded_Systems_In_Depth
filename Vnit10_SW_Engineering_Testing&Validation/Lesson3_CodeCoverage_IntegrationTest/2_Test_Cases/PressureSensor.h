/*
 * PressureSensor.h
 *
 *  Created on: Dec 27, 2022
 *      Author: Abdel
 */

#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_

#include "state.h"
#include "driver.h"

enum
{
	PSENSOR_READING,
	PSENSOR_WAITING
}PressureSensor_ID;


STATE_define(Psensor_Reading);
STATE_define(Psensor_Waiting);

void PressureSensor_Init();

extern void (*PSENSOR_STATE) ();

#endif /* PRESSURESENSOR_H_ */
