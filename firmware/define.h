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

#define SAMPLE_TIME_IMU 			(100)  	// us
#define SAMPLE_TIME_ENCODER			(100)	// us

// TIM_Period = (Timer_tick_frequence/PWM_frequence )-1 =
// = (1000000/1000)-1 = 999
#define TIM_PERIOD 					(999)

#define MAX_CONTROL_SIGNAL			(float)(100)	// rad/s
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
	int Dir;
	int Speed;
} MOTOR_PARAMETERS;

typedef struct
{
	uint16_t acceX;
} ACCELEROMETER_STRUCT;

typedef struct
{
	uint16_t gyroX;
} GYROSCOPE_STRUCT;

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float u;
	float u_;
	float e;
	float e_;
	float e__;
	float Ts;
} PID_PARAMETERS;

#endif /* __DEFINE_H_ */
