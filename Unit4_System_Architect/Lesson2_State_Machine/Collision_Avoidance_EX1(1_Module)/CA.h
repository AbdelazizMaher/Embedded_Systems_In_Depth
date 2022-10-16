/*
 * CA.h
 *
 *  Created on: Oct 16, 2022
 *      Author: Abdelaziz Maher
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
#include <stdio.h>
#include <stdlib.h>

// Define States
enum
{
	CA_WAITING,
	CA_DRIVING
}CA_State_Id;

// Declare state fn.
STATE_define(Waiting);
STATE_define(Driving);

// Pointer to State fn.
extern void (*CA_STATE) ();

#endif /* CA_H_ */
