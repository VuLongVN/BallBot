/**
 * @file	Feedback.c
 * @brief	Calculate feedback signals
 * @authors VuLong DuyKhanh
 */
 
#include "include.h"	

float varphi[3];
float arc[3];
float omega[3];

float phi[3];

int16_t	velocity[3];
int32_t coordinate[3];

extern volatile uint64_t periodEncoderPulse[4];
extern volatile uint64_t counterEncoderPulse[4];

void feedbackProcess(void);
void feedbackIMUProcess(void);

void arcOfMotor2PhiOfBall(	float localArcA, float localArcB, float localArcC, \
							float localPhiX, float localPhiY, float localPhiZ);

void IMUacce2Theta(uint16_t globalAccelerometer[3], float globalTheta[3]);
void IMUgyro2ThetaDot(uint16_t globalGyroscope[3], float globalThetaDot[3]);

void calVarphi(int8_t localMOTOR);								
void calArc(int8_t localMOTOR);									
void calOmega(int8_t localMOTOR);	

void calVelocity(int8_t localAXIS);						
void calCoordinate(int8_t localAXIS);

void feedbackEncoderProcess(void)
{
	calVarphi(MOTOR_A);
	calVarphi(MOTOR_B);
	calVarphi(MOTOR_C);
	calArc(MOTOR_A);
	calArc(MOTOR_B);
	calArc(MOTOR_C);
	//calOmega(MOTOR_A);
	//calOmega(MOTOR_B);
	//calOmega(MOTOR_C);
	arcOfMotor2PhiOfBall(arc[MOTOR_A], arc[MOTOR_B], arc[MOTOR_C], phi[AXIS_X], phi[AXIS_Y], phi[AXIS_Z]);
	calVelocity(AXIS_X);
	calVelocity(AXIS_Y);
	calVelocity(AXIS_Z);
	calCoordinate(AXIS_X);
	calCoordinate(AXIS_Y);
	calCoordinate(AXIS_Z);
}

void feedbackIMUProcess(void)
{

}

void arcOfMotor2PhiOfBall(	float localArcA, float localArcB, float localArcC, \
							float localPhiX, float localPhiY, float localPhiZ)
{

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
