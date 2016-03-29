/**
 * @file	define.h
 * @brief	Global define file
 * @authors VuLong DuyKhanh
 */


#ifndef __DEFINE_H_
#define __DEFINE_H_

#include "include.h"

#define ON	1
#define OFF	0
#define TESTMOTOR
#define TESTBUTTON
#define SAMPLE_TIME_IMU 		(100)  	// us
#define SAMPLE_TIME_ENCODER	(100)		// us

// TIM_Period = (Timer_tick_frequence/PWM_frequence )-1 =
// = (1000000/1000)-1 = 999
#define TIM_PERIOD 					(999)

typedef enum
{
	MOTOR_A = 0,
	MOTOR_B,
	MOTOR_C,
	MOTOR_D
} MOTOR;

typedef enum
{
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z,
} AXIS;

typedef struct
{
	 int Power;	
	 int Dir;
	 int Speed;
} motorA;

typedef struct
{
	 int Power;	
	 int Dir;
	 int Speed;
} motorB;

typedef struct
{
	 int Power;	
	 int Dir;
	 int Speed;
} motorC;

#endif /* __DEFINE_H_ */
