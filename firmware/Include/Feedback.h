/**
 * @file	Feedback.h
 * @brief	Calculate feedback signals
 * @authors VuLong DuyKhanh
 */
 
#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include "include.h"

extern double varphi[3];
extern double arc[3];
extern double omega[3];

extern double phi[3];

extern int16_t velocity[3];
extern int32_t coordinate[3];

extern double globalTheta[3];
extern double globalThetaDot[3];

extern volatile uint64_t periodEncoderPulse[4];
extern volatile uint64_t counterEncoderPulse[4];

extern void feedbackEncoderProcess(void);
extern void feedbackIMUProcess(void);

extern void arcOfMotor2PhiOfBall(	double localArcA, double localArcB, double localArcC, \
									double localPhiX, double localPhiY, double localPhiZ);

extern void IMUacce2Theta(void);
extern void IMUgyro2ThetaDot(void);

extern void calVarphi(int8_t localMOTOR);
extern void calArc(int8_t localMOTOR);
extern void calOmega(int8_t localMOTOR);
extern void calVelocity(int8_t localAXIS);
extern void calCoordinate(int8_t localAXIS);

#endif /* __FEEDBACK_H */

