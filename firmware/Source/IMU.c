/**
 * @file	IMU.c
 * @brief	IMU
 * @authors VuLong DuyKhanh
 */
#include "include.h"

static int32_t gyro_x =0 , gyro_y = 0, gyro_z = 0, acc_x = 0, acc_y = 0, acc_z = 0;
static int32_t gyro_x_tmp =0 , gyro_y_tmp = 0, gyro_z_tmp = 0, acc_x_tmp = 0, acc_y_tmp = 0, acc_z_tmp = 0;
static int32_t gyro_x_zero, gyro_y_zero, gyro_z_zero;
static float gyro_x_rate, gyro_y_rate, gyro_z_rate;
static float acc_x_angle, acc_y_angle, acc_z_angle;


volatile int16_t gyro_value[3], accel_value[3], gyro_zero[3];
float globalGyroAngle[3], globalAccelAngle[3];
float localGyroAngle[3];
float FilteredAngle[3];

void IMUconfig(void);
void IMUreadAccelerometer(uint16_t localAccelerometer[3]);
void IMUreadGyroscope(uint16_t localGyroscope[3]);
void IMUGetAngle(void);
void IMUreset(void);

void IMUconfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;			
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			
	GPIO_Init(GPIOB, &GPIO_InitStruct);				
	  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);	// SCL
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1); // SDA
	
	//Configure I2C1 
	I2C_InitStruct.I2C_ClockSpeed = 100000; 		
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;			
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;	
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;			
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;		
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_Init(I2C1, &I2C_InitStruct);				
	
	//Enable I2C1
	I2C_Cmd(I2C1, ENABLE);

}


void IMUGetValue(void)
{
	u8 i=0;
	for(i=0; i<50; i++)
	{
		MPUgetAcceleration(accel_value);
		MPUgetRotation(gyro_value);
	
		acc_x_tmp+=(int16_t)(accel_value[AXIS_X]);
		acc_y_tmp+=(int16_t)(accel_value[AXIS_Y]);
		acc_z_tmp+=(int16_t)(accel_value[AXIS_Z]);
		gyro_x_tmp+=(int16_t)(gyro_value[AXIS_X]);
		gyro_y_tmp+=(int16_t)(gyro_value[AXIS_Y]);
		gyro_z_tmp+=(int16_t)(gyro_value[AXIS_Z]);
	}
	acc_x= acc_x_tmp/50;
	acc_y= acc_y_tmp/50;
	acc_z= acc_z_tmp/50;
	gyro_x= gyro_x_tmp/50;
	gyro_y= gyro_y_tmp/50;
	gyro_z= gyro_z_tmp/50;
	acc_x_tmp = 0;
	acc_y_tmp = 0;
	acc_z_tmp = 0;
	gyro_x_tmp = 0;
	gyro_y_tmp = 0;
	gyro_z_tmp = 0;
}

void IMUGetValueGyroOffset(void)
{
	u8 i=0;
	//gyro_x_zero=0;gyro_y_zero=0;gyro_z_zero=0;
	for(i=0;i<100;i++)
	{
			MPUgetRotation(gyro_zero); 

			gyro_x_tmp+=(int16_t)(gyro_zero[AXIS_X]);
			gyro_y_tmp+=(int16_t)(gyro_zero[AXIS_Y]);
			gyro_z_tmp+=(int16_t)(gyro_zero[AXIS_Z]);
	}
	gyro_x_zero= gyro_x_tmp/50;
	gyro_y_zero= gyro_y_tmp/50;
	gyro_z_zero= gyro_z_tmp/50;
	gyro_x_tmp = 0;
	gyro_y_tmp = 0;
	gyro_z_tmp = 0;

}

double IMUGyroXRate(void)
{
		gyro_x_rate = (float)(gyro_x - gyro_x_zero)/GYRO_SENSITIVITY;
		return gyro_x_rate;
}

double IMUGyroYRate(void)
{
		gyro_y_rate = (float)(gyro_y - gyro_y_zero)/GYRO_SENSITIVITY;
		return gyro_y_rate;
}

double IMUGyroZRate(void)
{
		gyro_z_rate = (float)(gyro_z - gyro_z_zero)/GYRO_SENSITIVITY;
		return gyro_z_rate;
}

double IMUGetXAngle(void)
{
		acc_x_angle=RAD_TO_DEGREE*atan((float)acc_x/sqrt((float)(acc_y*acc_y)+(float)(acc_z*acc_z)));
		return acc_x_angle;
}

double IMUGetYAngle(void)
{
		acc_y_angle=RAD_TO_DEGREE*atan((float)-acc_y/sqrt((float)(acc_x*acc_x)+(float)(acc_z*acc_z)));
		return acc_y_angle;
}

double IMUGetZAngle(void)
{
		acc_z_angle=RAD_TO_DEGREE*atan(sqrt((float)(acc_x*acc_x)+(float)(acc_y*acc_y))/(float)acc_z);
		return acc_z_angle;	
}

void IMUGetAngle(void) 
{
	globalGyroAngle[AXIS_X] = (float)localGyroAngle[AXIS_X] + (float)globalThetaDot[AXIS_X]* SAMPLE_TIME_IMU/1000.0 ; // unit: second;
	globalGyroAngle[AXIS_Y] = (float)localGyroAngle[AXIS_Y] + (float)globalThetaDot[AXIS_Y]* SAMPLE_TIME_IMU/1000.0 ;
	globalGyroAngle[AXIS_Z] = (float)localGyroAngle[AXIS_Z] + (float)globalThetaDot[AXIS_Z]* SAMPLE_TIME_IMU/1000.0 ;
	localGyroAngle[AXIS_X] =  FilteredAngle[AXIS_X]; // Using for Filtered GyroAngle
	localGyroAngle[AXIS_Y] =  FilteredAngle[AXIS_Y];
	localGyroAngle[AXIS_Z] =  FilteredAngle[AXIS_Z];
}


void IMUInterrupt(void) // Using for unfilter GyroAngle 
{
	localGyroAngle[AXIS_X] =  globalGyroAngle[AXIS_X];
	localGyroAngle[AXIS_Y] =  globalGyroAngle[AXIS_Y];
	localGyroAngle[AXIS_Z] =  globalGyroAngle[AXIS_Z];

}

void IMUFilter(void)
{
	float ALPHA = 0.3; // I calibed this factor =))(It is not like the fomular form: http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip)
	FilteredAngle[AXIS_X] = ALPHA*(float)globalGyroAngle[AXIS_X] + (1.0-ALPHA)*(float)globalTheta[AXIS_X];
	FilteredAngle[AXIS_Y] = ALPHA*(float)globalGyroAngle[AXIS_Y] + (1.0-ALPHA)*(float)globalTheta[AXIS_Y];
	FilteredAngle[AXIS_Z] = ALPHA*(float)globalGyroAngle[AXIS_Z] + (1.0-ALPHA)*(float)globalTheta[AXIS_Z];
}
void IMUreset(void)
{

}
