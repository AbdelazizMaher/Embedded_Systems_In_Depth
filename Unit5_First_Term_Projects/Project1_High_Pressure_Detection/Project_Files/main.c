/*
 * main.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Abdelaziz Maher
 */

#include <stdint.h>
#include <stdio.h>

#include "PressureSensor.h"
#include "MainAlgorithm.h"
#include "AlarmMonitor.h"
#include "AlarmActuator.h"


void Setup()
{
	GPIO_INITIALIZATION();
	PressureSensor_Init();
	MAIN_ALGO_STATE = STATE(HighPressure_detection);
	ALARM_MONITOR_STATE = STATE(AlarmOFF);
	AlaramActuator_Init();
}

int main()
{
	Setup();

	while(1)
	{
		PSENSOR_STATE();
		MAIN_ALGO_STATE();
		ALARM_MONITOR_STATE();
		ALARM_ACT_STATE();

	}

   return 0;
}
