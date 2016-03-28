/**
 * @file	IMU.h
 * @brief	IMU
 * @authors VuLong DuyKhanh
 */
#ifndef __IMU_H
#define __IMU_H

#include "include.h"

/* Cua tui no viet
void IMUConfigure(void);
    //imuRuntimeConfig_t *initialImuRuntimeConfig,
   // pidProfile_t *initialPidProfile,
   // accDeadband_t *initialAccDeadband,
   // float accz_lpf_cutoff,
  //  uint16_t throttle_correction_angle
//);


void imuUpdate(void); //rollAndPitchTrims_t *accelerometerTrims);
void calculateEstimatedAltitude(uint32_t currentTime);
float calculateThrottleAngleScale(uint16_t throttle_correction_angle);
int16_t calculateThrottleAngleCorrection(uint8_t throttle_correction_value);
float calculateAccZLowPassFilterRCTimeConstant(float accz_lpf_cutoff);
int16_t imuCalculateHeading(void);//t_fp_vector *vec);
void imuResetAccelerationSum(void);
*/

/* Cua tao viet */
extern void IMUconfig(void);
extern void IMUreadAccelerometer(uint16_t localAccelerometer[3]);
extern void IMUreadGyroscope(uint16_t localGyroscope[3]);
extern void IMUacce2Theta(uint16_t localAccelerometer[3], float localTheta[3]);
extern void IMUgyro2ThetaDot(uint16_t localGyroscope[3], float localThetaDot[3]);
extern void IMUreset(void);

#endif /* __IMU_H*/

