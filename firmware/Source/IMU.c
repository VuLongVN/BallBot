/**
 * @file	IMU.c
 * @brief	IMU
 * @authors VuLong DuyKhanh
 */
 
#include "include.h"
 
void IMUconfig(void);
void IMUreadAccelerometer(uint16_t globalAccelerometer[3]);
void IMUreadGyroscope(uint16_t globalGyroscope[3]);
void IMUacce2Theta(uint16_t globalAccelerometer[3], float globalTheta[3]);
void IMUgyro2ThetaDot(uint16_t globalGyroscope[3], float globalThetaDot[3]);
void IMUreset(void);

