/*
 * state.h
 *
 *  Created on: Oct 17, 2022
 *      Author: Abdelaziz Maher
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>

#define STATE_define(_statefunc_)    void ST_##_statefunc_()
#define STATE(_statefunc_)           ST_##_statefunc_

void US_GetDistance(int Distance);
void Motor_SetSpeed(int Speed);

#endif /* STATE_H_ */
