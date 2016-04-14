/**
 * @file	IMU.h
 * @brief	IMU
 * @authors VuLong DuyKhanh
 */
#ifndef __IMU_H
#define __IMU_H

#define GYRO_SENSITIVITY 			(65.5f)
#define ACCEL_SENSITIVITY 			(16384)

extern void IMUconfig(void);
extern void IMUGetValue(void);
extern void IMUGetValueGyroOffset(void);

extern double IMUGyroXRate(void);
extern double IMUGyroYRate(void);
extern double IMUGyroZRate(void);
extern double IMUGetXAngle(void);
extern double IMUGetYAngle(void);
extern double IMUGetZAngle(void);

extern void IMUreset(void);

#endif /* __IMU_H*/

