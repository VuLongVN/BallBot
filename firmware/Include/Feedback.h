/**
 * @file	Feedback.h
 * @brief	Calculate feedback signals
 * @authors VuLong DuyKhanh
 */
 
#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include "include.h"

extern float varphi[3];
extern float arc[3];
extern float omega[3];

extern float phi[3];

extern int16_t velocity[3];
extern int32_t coordinate[3];

extern volatile uint64_t periodEncoderPulse[4];
extern volatile uint64_t counterEncoderPulse[4];

extern void feedbackEncoderProcess(void);
extern void feedbackIMUProcess(void);

extern void arcOfMotor2PhiOfBall(	float localArcA, float localArcB, float localArcC, \
									float localPhiX, float localPhiY, float localPhiZ);

extern void IMUacce2Theta(uint16_t localAccelerometer[3], float localTheta[3]);
extern void IMUgyro2ThetaDot(uint16_t localGyroscope[3], float localThetaDot[3]);

extern void calVarphi(int8_t localMOTOR);
extern void calArc(int8_t localMOTOR);
extern void calOmega(int8_t localMOTOR);
extern void calVelocity(int8_t localAXIS);
extern void calCoordinate(int8_t localAXIS);

#endif /* __FEEDBACK_H */

