/*
 * state.h
 *
 *  Created on: Oct 16, 2022
 *      Author: Abdelaziz Maher
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_statefunc_)    void ST_##_statefunc_()
#define STATE(_statefunc_)           ST_##_statefunc_

#endif /* STATE_H_ */
