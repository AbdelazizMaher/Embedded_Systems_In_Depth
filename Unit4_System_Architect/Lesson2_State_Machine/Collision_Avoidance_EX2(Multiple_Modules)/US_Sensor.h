/*
 * US_Sensor.h
 *
 *  Created on: Oct 17, 2022
 *      Author: Abdel
 */

#ifndef US_SENSOR_H_
#define US_SENSOR_H_

#include "state.h"

// Define States
enum
{
	US_BUSY
}US_State_Id;


void US_Init();

// Declare state fn.
STATE_define(US_Busy);

// Pointer to State fn.
extern void (*US_STATE) ();



#endif /* US_SENSOR_H_ */
