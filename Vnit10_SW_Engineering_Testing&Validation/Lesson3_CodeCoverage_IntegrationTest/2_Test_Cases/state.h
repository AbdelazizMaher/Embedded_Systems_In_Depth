/*
 * state.h
 *
 *  Created on: December 26, 2022
 *      Author: Abdelaziz Maher
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>


#define STATE_define(_statefunc_)    void ST_##_statefunc_()
#define STATE(_statefunc_)           ST_##_statefunc_


void Set_PressureValue(int Pvalue);
void StartAlarm();
void StopAlarm();
void Detect_HighPressure();

#endif /* STATE_H_ */
