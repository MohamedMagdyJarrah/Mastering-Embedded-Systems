/*
 * State.h
 *
 *  Created on: Jan 11, 2024
 *      Author: LapStore
 */

#ifndef STATE_H_
#define STATE_H_

/* Generating functions for the states in the system */
#define STATE_Define(_ST_FUNC_)		void ST_##_ST_FUNC_(void)
#define NextState(_ST_FUNC_)		ST_##_ST_FUNC_

/* State Connections */
void US_GetDistance(int d);
void MOTOR_SetSpeed(int s);

#endif /* STATE_H_ */
