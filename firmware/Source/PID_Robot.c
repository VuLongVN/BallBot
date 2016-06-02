/**
 * @file	PID.c
 * @brief	PID wall controller
 * @authors VuLong DuyKhanh
 */

#include "include.h"

PID_PARAMETERS globalPID_parametersAxisX;
PID_PARAMETERS globalPID_parametersAxisY;
PID_PARAMETERS globalPID_parametersAxisZ;

/*Set the parameters for each axis
 * @input: localParameters, axis
 * @process: globalParameters[AxisI] = localParameters
 */
void PIDrobotSetParameters(PID_PARAMETERS localPID_Parameters, int8_t localAxis)
{
	switch (localAxis)
	{
		case AXIS_X:
		{
			globalPID_parametersAxisX = localPID_Parameters;
			break;
		}
		case AXIS_Y:
		{
			globalPID_parametersAxisY = localPID_Parameters;
			break;
		}
		case AXIS_Z:
		{
			globalPID_parametersAxisZ = localPID_Parameters;
			break;
		}
	}
}

/* Set Kp, Ki, Kd for PID_parameters.
 * @input: localPID_Parameters (which parameters are changed K parameters), localKp, localKi, localKd,
 * @output: None.
 * @process: change K parameters of localPID_Parameters to localKp, localKi, localKd,
 */
void PIDrobotSetKParameters(PID_PARAMETERS localPID_Parameters, double localKp, double localKi, double localKd)
{
	localPID_Parameters.Kp = localKp;
	localPID_Parameters.Ki = localKi;
	localPID_Parameters.Kd = localKd;
}

/* Get the globalPID_parameters of each motor.
 * @input: localAxis.
 * @output: globalPID_parameters[localAxis].
 * @process: return globalPID_parameters[localAxis].
 */
PID_PARAMETERS PIDRobotGetParameters(int8_t localAxis)
{
	switch (localAxis)
	{
		case AXIS_X:
		{
			return globalPID_parametersAxisX;
		}
		case AXIS_Y:
		{
			return globalPID_parametersAxisY;
		}
		case AXIS_Z:
		{
			return globalPID_parametersAxisZ;
		}
	}
	return globalPID_parametersAxisZ;
}


void PIDrobotProcess(PID_PARAMETERS localPID_Parameters, int8_t localAxis)
{
	localPID_Parameters.e__ = localPID_Parameters.e_;
	localPID_Parameters.e_ = localPID_Parameters.e;
	localPID_Parameters.e = globalErrorTheta[localAxis];
	localPID_Parameters.u_ = localPID_Parameters.u;
	localPID_Parameters.u = localPID_Parameters.u_ +\
		localPID_Parameters.Kp*(localPID_Parameters.e - localPID_Parameters.e_) + \
		localPID_Parameters.Ki*SAMPLE_TIME_IMU*localPID_Parameters.e + \
		(localPID_Parameters.Kd/SAMPLE_TIME_IMU)*(localPID_Parameters.e - 2*localPID_Parameters.e_ + localPID_Parameters.e__);
	if (localPID_Parameters.u > MAX_ROBOT_CONTROL_SIGNAL)
	{
		localPID_Parameters.u = MAX_ROBOT_CONTROL_SIGNAL;
	}
	else if (localPID_Parameters.u < -MAX_ROBOT_CONTROL_SIGNAL)
	{
		localPID_Parameters.u = -MAX_ROBOT_CONTROL_SIGNAL;	
	}
}

double PIDrobotControlSignal(PID_PARAMETERS localPID_Parameters, int8_t localAxis)
{
	PIDrobotProcess(localPID_Parameters,localAxis);
	return localPID_Parameters.u;
}

void PIDrobotResetParameters(int8_t localAxis)
{
	switch (localAxis)
	{
		case AXIS_X:
		{
			globalPID_parametersAxisX.e__ = 0;
			globalPID_parametersAxisX.e_ = 0;
			globalPID_parametersAxisX.e = 0;
			globalPID_parametersAxisX.u_ = 0;
			globalPID_parametersAxisX.u = 0;
		}
		case AXIS_Y:
		{
			globalPID_parametersAxisY.e__ = 0;
			globalPID_parametersAxisY.e_ = 0;
			globalPID_parametersAxisY.e = 0;
			globalPID_parametersAxisY.u_ = 0;
			globalPID_parametersAxisY.u = 0;
		}
		case AXIS_Z:
		{
			globalPID_parametersAxisZ.e__ = 0;
			globalPID_parametersAxisZ.e_ = 0;
			globalPID_parametersAxisZ.e = 0;
			globalPID_parametersAxisZ.u_ = 0;
			globalPID_parametersAxisZ.u = 0;
		}
	}
}

void PIDrobotGetError(void)
{
	feedbackIMUProcess();
	globalErrorTheta[AXIS_X] = globalTheta[AXIS_X] - globalCalibTheta[AXIS_X];
	globalErrorTheta[AXIS_Y] = globalTheta[AXIS_Y] - globalCalibTheta[AXIS_Y];
	globalErrorTheta[AXIS_Z] = globalTheta[AXIS_Z] - globalCalibTheta[AXIS_Z];
}


