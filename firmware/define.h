/**
 * @file	define.h
 * @brief	Global define file
 * @authors VuLong DuyKhanh
 */


#ifndef __DEFINE_H
#define __DEFINE_H

#include "include.h"

#define ON							(1)
#define OFF							(0)


/* Test definitions */
#define TESTMOTOR
#define TESTBUTTON
#define TESTENCODER
#define TESTUART
#define TESTIMU

#define USED_PID
// #define USED_LQR

/* Module used definitions */
#define USE_USART1

/* Time definitions */
#define SAMPLE_TIME_IMU 			(5000)  	// us
#define SAMPLE_TIME_ENCODER			(200)		// us
#define SAMPLE_TIME_PID				(1000)		// us
#define PERIOD_TIME_PID				(200000)	// us	
#define PERIOD_TIME_LQG				(200000)	// us

// TIM_Period = (Timer_tick_frequence/PWM_frequence )-1 =
// = (1000000/1000)-1 = 999
#define TIM_PERIOD 					(999)

#define MICRO_S						(0.000001f) 

/* Math definitions */
#define RAD_TO_DEGREE 				(57.2957795f)
#define PI 							(3.141593f)
#define g							(9.81f)

 
/* Type definitions */
typedef enum
{
	MOTOR_A = 0,
	MOTOR_B = 1,
	MOTOR_C = 2,
	MOTOR_D = 3
} MOTOR;

typedef enum
{
	AXIS_X = 0,
	AXIS_Y = 1,
	AXIS_Z = 2
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
