/**
 * @file	PID.c
 * @brief	PID wall controller
 * @authors VuLong DuyKhanh
 */


#include "include.h"

#ifndef __PID_ROBOT_H
#define __PID_ROBOT_H


extern PID_PARAMETERS globalPID_parametersAxisX;
extern PID_PARAMETERS globalPID_parametersAxisY;
extern PID_PARAMETERS globalPID_parametersAxisZ;

extern double globalCalibTheta[3];
// extern double globalCalibThetaDot[3];
extern double globalErrorTheta[3];

#define	MAX_ROBOT_CONTROL_SIGNAL			(100)

/* Set the parameters for each motor.
 * @input: localPID_Parameters (which parameters are pushed to globalParameters), localAxis.
 * @output: None,
 * @process: globalParameters[AxisI] = localPID_Parameters.
 */
extern void PIDrobotSetParameters(PID_PARAMETERS localPID_Parameters, int8_t localAxis);

/* Set Kp, Ki, Kd for PID_parameters.
 * @input: localPID_Parameters (which parameters are changed K parameters), localKp, localKi, localKd,
 * @output: None.
 * @process: change K parameters of localPID_Parameters to localKp, localKi, localKd,
 */
extern void PIDrobotSetKParameters(PID_PARAMETERS localPID_Parameters, double localKp, double localKi, double localKd);

/* Get the globalPID_parameters of each motor.
 * @input: localAxis.
 * @output: globalPID_parameters[localAxis].
 * @process: return globalPID_parameters[localAxis].
 */
extern PID_PARAMETERS PIDRobotGetParameters(int8_t localAxis);

/* PID processing.
 * @input: localAxis.
 * @output: None.
 * @process: update control signal (u).
 */
extern void PIDrobotProcess(PID_PARAMETERS localPID_Parameters, int8_t localAxis);

/* Control signal.
 * @input: localAxis.
 * @output: double u(t).
 * @process: return control signal (u).
 */
extern double PIDrobotControlSignal(PID_PARAMETERS localPID_Parameters, int8_t localAxis);

/* Reset PID parameters. 
 * @input: localAxis.
 * @output: None.
 * @process: Reset all PID parameters of localAxis.
 */
extern void PIDrobotResetParameters(int8_t localAxis);

/* Get error (e(t) = u(t) - y(t)) 
 * @input: localAxis.
 * @output: None.
 * @process: update control signal (u).
 */
extern void PIDrobotGetError(void);

#endif /* WALLFOLLOW_PID_H_ */
