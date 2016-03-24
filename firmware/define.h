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

typedef enum
{
	MOTOR_A = 0,
	MOTOR_B,
	MOTOR_C,
	MOTOR_D
} MOTOR;

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
