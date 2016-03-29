/**
 * @file	Encoder.h
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */

#include "include.h"


#define EncoderA_PIN               GPIO_Pin_3  
#define EncoderA_GPIO_PORT         GPIOB
#define EncoderA_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderA_SOURCE            GPIO_PinSource3
#define EncoderA_AF                GPIO_AF_TIM2 // CH2  -- A15CH1
#define EncoderA_MODE							 TIM_EncoderMode_TI2

#define EncoderB_PIN               GPIO_Pin_4   
#define EncoderB_GPIO_PORT         GPIOB
#define EncoderB_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderB_SOURCE            GPIO_PinSource4
#define EncoderB_AF                GPIO_AF_TIM3 // CH1 -- B5CH2
#define EncoderB_MODE							 TIM_EncoderMode_TI1

#define EncoderC_PIN               GPIO_Pin_7   
#define EncoderC_GPIO_PORT         GPIOB
#define EncoderC_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderC_SOURCE            GPIO_PinSource7
#define EncoderC_AF                GPIO_AF_TIM4 // CH2 -- B6CH1
#define EncoderC_MODE							 TIM_EncoderMode_TI2

#define EncoderD_PIN               GPIO_Pin_14 
#define EncoderD_GPIO_PORT         GPIOB
#define EncoderD_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderD_SOURCE            GPIO_PinSource14
#define EncoderD_AF                GPIO_AF_TIM12 // CH1 -- B15CH2
#define EncoderD_MODE							 TIM_EncoderMode_TI1



// determine the timers to use
#define EncoderA_TIMER              TIM2
#define EncoderA_TIMER_CLK          RCC_APB1Periph_TIM2
#define EncoderB_TIMER              TIM3
#define EncoderB_TIMER_CLK          RCC_APB1Periph_TIM3
#define EncoderC_TIMER              TIM4
#define EncoderC_TIMER_CLK          RCC_APB1Periph_TIM4
#define EncoderD_TIMER              TIM12
#define EncoderD_TIMER_CLK          RCC_APB1Periph_TIM12





#define ENCODER_PULSES 									(20)
#define OMEGA_J													(2*PI/ ENCODER_PULSES)

#define calVarphi(MOTOR)								(varphi[MOTOR] 			= (OMEGA_J*counterEncoderPulse[MOTOR]);)
#define calArc(MOTOR)										(arc[MOTOR] 				= (RADIUS_WHEELS*varphi[MOTOR]);)
#define calOmega(MOTOR)									(omega[MOTOR]				= (OMEGA_J/periodEncoderPulse[MOTOR]);)

#define calVelocity(AXIS)								(velocity[AXIS]			= (RADIUS_BALL*phi[AXIS]);)
#define calCoordinate(AXIS)							(coordinate[AXIS]		+= (SAMPLE_TIME_ENCODER*velocity[AXIS]);)



extern float varphi[3];
extern float arc[3];
extern float omega[3];

extern float phi[3];

extern int16_t	velocity[3];
extern int32_t coordinate[3];

uint32_t periodEncoderPulse(int MOTOR);
uint32_t counterEncoderPulse(int MOTOR);

extern void encoderInit(void);
extern void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
extern void encoderInterrupt(void);
extern void encoderReset(void);
extern void readEncoder(int MOTOR);


