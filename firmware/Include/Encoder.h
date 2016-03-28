/**
 * @file	Encoder.h
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */

#include "include.h"

#define ENCODER_PULSES 									(20)
#define OMEGA_J													(2*PI/ ENCODER_PULSES)


extern float varphi[3];
extern float arc[3];
extern float omega[3];

extern float phi[3];

extern int16_t velocity[3];
extern int32_t coordinate[3];

extern uint32_t periodEncoderPulse[3];
extern uint32_t counterEncoderPulse[3];

extern void encoderInit(void);
extern float encoder2VarphiOfMotor(int8_t localMotor);
extern void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
extern void encoderInterrupt(void);
extern void encoderReset(void);

extern void calVarphi(int8_t localMOTOR);
extern void calArc(int8_t localMOTOR);
extern void calOmega(int8_t localMOTOR);
extern void calVelocity(int8_t localAXIS);
extern void calCoordinate(int8_t localAXIS);

