/*
 * MainAlgorithm.h
 *
 *  Created on: Dec 27, 2022
 *      Author: Abdel
 */

#ifndef MAINALGORITHM_H_
#define MAINALGORITHM_H_

#include "state.h"
#include "driver.h"

enum
{
	HIGH_PRESSURE_DETECTION,
}Main_Algorithm_ID;


STATE_define(HighPressure_detection);

extern void (*MAIN_ALGO_STATE) ();

#endif /* MAINALGORITHM_H_ */
