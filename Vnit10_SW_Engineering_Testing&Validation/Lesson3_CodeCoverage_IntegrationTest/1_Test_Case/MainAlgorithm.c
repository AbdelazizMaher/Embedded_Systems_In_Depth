/*
 * MainAlgorithm.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Abdel
 */

#include "MainAlgorithm.h"

int Threshold = 20;
int DetectedPressure =0;

void (*MAIN_ALGO_STATE) ();

void Set_PressureValue(int Pvalue)
{
	DetectedPressure = Pvalue;
}


STATE_define(HighPressure_detection)
{
	Main_Algorithm_ID = HIGH_PRESSURE_DETECTION;

	if( DetectedPressure >= Threshold)
	{
		Detect_HighPressure();
	}
}
