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

uint32_t periodEncoderPulse(MOTOR);
uint32_t counterEncoderPulse(MOTOR);

void encoderInit(void);
void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
void encoderInterrupt(void);
void encoderReset(void);
