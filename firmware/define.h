/**
 * @file	define.h
 * @brief	Global define file
 * @authors VuLong DuyKhanh
 */


#ifndef __DEFINE_H_
#define __DEFINE_H_

#include "include.h"

#define ON							(1)
#define OFF							(0)
#define PI 							(3.141593f)
#define g							(9.81f)
#define TESTMOTOR
#define TESTBUTTON
#define TESTENCODER

#define SAMPLE_TIME_IMU 			(5000)  	// us
#define SAMPLE_TIME_ENCODER		(200)		// us
#define SAMPLE_TIME_PID				(1000)		// us
#define PERIOD_TIME_PID				(200000)	// us	
#define PERIOD_TIME_LQG				(200000)	// us

#define MICRO_S								(0.000001f) 

 

// TIM_Period = (Timer_tick_frequence/PWM_frequence )-1 =
// = (1000000/1000)-1 = 999
#define TIM_PERIOD 					(999)

#define MAX_CONTROL_SIGNAL			(100.0f)	// rad/s


#define ENCODER_PULSES 				(20)
#define OMEGA_J						(2*PI/ENCODER_PULSES)

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
} PID_PARAMETERS;

#endif /* __DEFINE_H_ */
