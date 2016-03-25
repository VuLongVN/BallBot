/**
 * @file	Encoder.h
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */

#include "include.h"

#define ENCODER_PULSES 									(20)
#define OMEGA_J													(2*PI/ ENCODER_PULSES)

#define calVarphi(MOTOR)								(varphi[MOTOR] 			= (OMEGA_J*counterEncoderPulse[MOTOR]);)
#define calArc(MOTOR)										(arc[MOTOR] 				= (RADIUS_WHEELS*varphi[MOTOR]);)
#define calOmega(MOTOR)									(omega[MOTOR]				= (OMEGA_J/periodEncoderPulse[MOTOR]);)

#define calVelocity(AXIS)								(velocity[AXIS]			= (RADIUS_BALL*phi[AXIS]);)
#define calCoordinate(AXIS)							(coordinate[AXIS]		+= (SAMPLE_TIME_ENCODER*velocity[AXIS]);)

extern float varphi[3];
extern float arc[3];
extern float omega[3];

extern float phi[3];

extern int16_t	velocity[3];
extern int32_t coordinate[3];

extern uint32_t periodEncoderPulse(MOTOR);
extern uint32_t counterEncoderPulse(MOTOR);

extern void encoderInit(void);
extern void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
extern void encoderInterrupt(void);
extern void encoderReset(void);

