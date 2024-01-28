/*
 * PressureSensor.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Abdel
 */

#include "PressureSensor.h"


int Sensor_Reading = 0;

void (*PSENSOR_STATE) ();

void PressureSensor_Init()
{
	PSENSOR_STATE = STATE(Psensor_Reading);
}

STATE_define(Psensor_Reading)
{
	PressureSensor_ID = PSENSOR_READING;

	Sensor_Reading = getPressureVal();
	Set_PressureValue(Sensor_Reading);
	

	//PSENSOR_STATE = STATE(Psensor_Waiting);
}


STATE_define(Psensor_Waiting)
{
	PressureSensor_ID = PSENSOR_WAITING;

	Delay(10000);

	PSENSOR_STATE = STATE(Psensor_Reading);

}
