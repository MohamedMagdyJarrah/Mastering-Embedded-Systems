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
#define HIGH_PRESSURE		((int)1)
#define NORMAL_PRESSURE		((int)0)

void SetPressureVal(int PressureVal);
void StorePressureInFlash(int PressureVal);
void HighPressureDetected(void);
void StartAlarm(void);
void StopAlarm(void);


#endif /* STATE_H_ */
