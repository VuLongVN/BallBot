/**
 * @file	Encoder.c
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */


#include "include.h"

float varphi[3];
float arc[3];
float omega[3];

float phi[3];

int16_t	velocity[3];
int32_t coordinate[3];

uint32_t periodEncoderPulse[3];
uint32_t counterEncoderPulse[3];

void encoderInit(void);
float encoder2VarphiOfMotor(int8_t localMotor);
void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
void encoderInterrupt(void);
void encoderReset(void);

void calVarphi(int8_t localMOTOR);								
void calArc(int8_t localMOTOR);									
void calOmega(int8_t localMOTOR);								

void calVelocity(int8_t localAXIS);						
void calCoordinate(int8_t localAXIS);


float encoder2VarphiOfMotor(int8_t localMotor)
{
	calVarphi(localMotor);
	return varphi[localMotor];
}

void calVarphi(int8_t localMOTOR)
{
	varphi[localMOTOR] = (OMEGA_J*counterEncoderPulse[localMOTOR]);
}

void calArc(int8_t localMOTOR)
{								
	arc[localMOTOR] = (RADIUS_WHEELS*varphi[localMOTOR]);
}

void calOmega(int8_t localMOTOR)
{
	omega[localMOTOR] = (OMEGA_J/periodEncoderPulse[localMOTOR]);
}

void calVelocity(int8_t localAXIS)
{
	velocity[localAXIS] = (RADIUS_BALL*phi[localAXIS]);
}

void calCoordinate(int8_t localAXIS)
{
	coordinate[localAXIS] += (SAMPLE_TIME_ENCODER*velocity[localAXIS]);
}
