/*
 * main.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Abdelaziz Maher
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "PressureSensor.h"
#include "MainAlgorithm.h"
#include "AlarmMonitor.h"
#include "AlarmActuator.h"
#include "Test.h"

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


unsigned char Test_CaseNumber = 1;

int Test_getPressureVal()
{
	int Test_PressureSensorReading = 0;
	
	switch( Test_CaseNumber )
	{
	case 1:
		printf("\n\n\n======================================== \n");
		printf("***************INTEGRATION TEST***************\n");
		printf(".High Pressure Detection Project \n");
		printf(".Eng. Abdelaziz Maher (www.learn-in-depth.com) \n");
		printf("========================================\n\n\n");
		
		Test_PressureSensorReading = 12;
		
		printf("======================================== \n");
		printf("Test Case 1: Input = 12 -> Output: NoALarm \n");
		printf("Test Case 1: Running \n");
		
		break;		
	}
	
	return Test_PressureSensorReading;
}

void Test_SetAlarmActuator(int i)
{
	if( Test_CaseNumber == 1 && i == 0 )
	{
		printf("Test Case 1: FAIL \n");
		printf("======================================== \n");
		
		Test_CaseNumber = 2;
		exit(1);
	}
	else if( Test_CaseNumber == 1 && i == 1 )
	{
		printf("Test Case 1: PASS \n");
		printf("======================================== \n");
		
		Test_CaseNumber = 2;
		exit(1);		
	}
}




