/**
 * @file	PID.c
 * @brief	PID wall controller
 * @authors VuLong DuyKhanh
 */

#include "include.h"

void PIDsetParameters(PID_PARAMETERS localPID_Parameters, int8_t localMotor);
void PIDsetKParameters(PID_PARAMETERS localPIDParameters, float localKp, float localKi, float localKd);
PID_PARAMETERS PIDgetParameters(int8_t localMotor);
void PIDprocess(PID_PARAMETERS localPIDParameters, int8_t localMotor);
float PIDcontrolSignal(PID_PARAMETERS localPID_Parameters, int8_t localMotor);
void PIDresetParameters(int8_t localMotor);
float PIDgetError(int8_t localMotor);

PID_PARAMETERS globalPID_parametersMotorA;
PID_PARAMETERS globalPID_parametersMotorB;
PID_PARAMETERS globalPID_parametersMotorC;
PID_PARAMETERS globalPID_parametersMotorD;

/*Set the parameters for each motor
 * @input: localParameters, Motor
 * @process: globalParameters[MotorJ] = localParameters
 */
void PIDsetParameters(PID_PARAMETERS localPID_Parameters, int8_t localMotor)
{
	switch (localMotor)
	{
		case MOTOR_A:
		{
			globalPID_parametersMotorA = localPID_Parameters;
			break;
		}
		case MOTOR_B:
		{
			globalPID_parametersMotorB = localPID_Parameters;
			break;
		}
		case MOTOR_C:
		{
			globalPID_parametersMotorC = localPID_Parameters;
			break;
		}
		case MOTOR_D:
		{
			globalPID_parametersMotorD = localPID_Parameters;
			break;
		}
	}
}

/* Set Kp, Ki, Kd for PID_parameters.
 * @input: localPID_Parameters (which parameters are changed K parameters), localKp, localKi, localKd,
 * @output: None.
 * @process: change K parameters of localPID_Parameters to localKp, localKi, localKd,
 */
void PIDsetKParameters(PID_PARAMETERS localPIDParameters, float localKp, float localKi, float localKd)
{
	localPIDParameters.Kp = localKp;
	localPIDParameters.Ki = localKi;
	localPIDParameters.Kd = localKd;
}

/* Get the globalPID_parameters of each motor.
 * @input: localMotor.
 * @output: globalPID_parameters[localMotor].
 * @process: return globalPID_parameters[localMotor].
 */
PID_PARAMETERS PIDgetParameters(int8_t localMotor)
{
	switch (localMotor)
	{
		case MOTOR_A:
		{
			return globalPID_parametersMotorA;
		}
		case MOTOR_B:
		{
			return globalPID_parametersMotorB;
		}
		case MOTOR_C:
		{
			return globalPID_parametersMotorC;
		}
		case MOTOR_D:
		{
			return globalPID_parametersMotorD;
		}
	}
	return globalPID_parametersMotorD;
}


void PIDprocess(PID_PARAMETERS localPIDParameters, int8_t localMotor)
{
	localPIDParameters.e__ = localPIDParameters.e_;
	localPIDParameters.e_ = localPIDParameters.e;
	localPIDParameters.e = PIDgetError(localMotor);
	localPIDParameters.u_ = localPIDParameters.u;
	localPIDParameters.u = localPIDParameters.u_ +\
													localPIDParameters.Kp*(localPIDParameters.e - localPIDParameters.e_) + \
													localPIDParameters.Ki*localPIDParameters.Ts*localPIDParameters.e + \
													(localPIDParameters.Kd/localPIDParameters.Ts)*(localPIDParameters.e - 2*localPIDParameters.e_ + localPIDParameters.e__);
	if (localPIDParameters.u > MAX_CONTROL_SIGNAL)
	{
		localPIDParameters.u = MAX_CONTROL_SIGNAL;
	}
	else if (localPIDParameters.u < -MAX_CONTROL_SIGNAL)
	{
		localPIDParameters.u = -MAX_CONTROL_SIGNAL;	
	}
}

float PIDcontrolSignal(PID_PARAMETERS localPIDParameters, int8_t localMotor)
{
	PIDprocess(localPIDParameters,localMotor);
	return localPIDParameters.u;
}

void PIDresetParameters(int8_t localMotor)
{
	switch (localMotor)
	{
		case MOTOR_A:
		{
			globalPID_parametersMotorA.e__ = 0;
			globalPID_parametersMotorA.e_ = 0;
			globalPID_parametersMotorA.e = 0;
			globalPID_parametersMotorA.u_ = 0;
			globalPID_parametersMotorA.u = 0;
		}
		case MOTOR_B:
		{
			globalPID_parametersMotorB.e__ = 0;
			globalPID_parametersMotorB.e_ = 0;
			globalPID_parametersMotorB.e = 0;
			globalPID_parametersMotorB.u_ = 0;
			globalPID_parametersMotorB.u = 0;
		}
		case MOTOR_C:
		{
			globalPID_parametersMotorC.e__ = 0;
			globalPID_parametersMotorC.e_ = 0;
			globalPID_parametersMotorC.e = 0;
			globalPID_parametersMotorC.u_ = 0;
			globalPID_parametersMotorC.u = 0;
		}
		case MOTOR_D:
		{
			globalPID_parametersMotorD.e__ = 0;
			globalPID_parametersMotorD.e_ = 0;
			globalPID_parametersMotorD.e = 0;
			globalPID_parametersMotorD.u_ = 0;
			globalPID_parametersMotorD.u = 0;
		}
	}
}

float PIDgetError(int8_t localMotor)
{

	return 0;
}


