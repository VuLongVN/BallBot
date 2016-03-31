/**
 * @file	PID.c
 * @brief	PID wall controller
 * @authors VuLong DuyKhanh
 */


#include "include.h"

#ifndef __PID_H
#define __PID_H


extern PID_PARAMETERS globalPID_parametersMotorA;
extern PID_PARAMETERS globalPID_parametersMotorB;
extern PID_PARAMETERS globalPID_parametersMotorC;
extern PID_PARAMETERS globalPID_parametersMotorD;

/* Set the parameters for each motor.
 * @input: localPID_Parameters (which parameters are pushed to globalParameters), localMotor.
 * @output: None,
 * @process: globalParameters[MotorJ] = localPID_Parameters.
 */
extern void PIDsetParameters(PID_PARAMETERS localPID_Parameters, int8_t localMotor);

/* Set Kp, Ki, Kd for PID_parameters.
 * @input: localPID_Parameters (which parameters are changed K parameters), localKp, localKi, localKd,
 * @output: None.
 * @process: change K parameters of localPID_Parameters to localKp, localKi, localKd,
 */
extern void PIDsetKParameters(PID_PARAMETERS localPID_Parameters, float localKp, float localKi, float localKd);

/* Get the globalPID_parameters of each motor.
 * @input: localMotor.
 * @output: globalPID_parameters[localMotor].
 * @process: return globalPID_parameters[localMotor].
 */
extern PID_PARAMETERS PIDgetParameters(int8_t localMotor);

/* PID processing.
 * @input: localMotor.
 * @output: None.
 * @process: update control signal (u).
 */
extern void PIDprocess(PID_PARAMETERS localPID_Parameters, int8_t localMotor);

/* Control signal.
 * @input: localMotor.
 * @output: float u(t).
 * @process: return control signal (u).
 */
extern float PIDcontrolSignal(PID_PARAMETERS localPID_Parameters, int8_t localMotor);

/* Reset PID parameters. 
 * @input: localMotor.
 * @output: None.
 * @process: Reset all PID parameters of localMotor.
 */
extern void PIDresetParameters(int8_t localMotor);

/* Get error (e(t) = u(t) - y(t)) 
 * @input: localMotor.
 * @output: None.
 * @process: update control signal (u).
 */
extern float PIDgetError(int8_t localMotor);
#endif /* WALLFOLLOW_PID_H_ */
