/**
 * @file	Encoder.h
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */

#include "include.h"

/******* TIM2 -- PA15_CH1 -- PB3_CH2 *********************************/
#define EncoderA_CH1_PIN               GPIO_Pin_15  
#define EncoderA_CH1_GPIO_PORT         GPIOA
#define EncoderA_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define EncoderA_CH1_SOURCE            GPIO_PinSource15
#define EncoderA_CH1_AF                GPIO_AF_TIM2 // CH2  -- A15CH1
  

#define EncoderA_CH2_PIN               GPIO_Pin_3  
#define EncoderA_CH2_GPIO_PORT         GPIOB
#define EncoderA_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderA_CH2_SOURCE            GPIO_PinSource3
#define EncoderA_CH2_AF                GPIO_AF_TIM2 //  


/**********************************************************************/
/******* TIM3 -- PB4_CH1 -- PB5_CH2 ***********************************/

#define EncoderB_CH1_PIN               GPIO_Pin_4   
#define EncoderB_CH1_GPIO_PORT         GPIOB
#define EncoderB_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderB_CH1_SOURCE            GPIO_PinSource4
#define EncoderB_CH1_AF                GPIO_AF_TIM3 


#define EncoderB_CH2_PIN               GPIO_Pin_5   
#define EncoderB_CH2_GPIO_PORT         GPIOB
#define EncoderB_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderB_CH2_SOURCE            GPIO_PinSource5
#define EncoderB_CH2_AF                GPIO_AF_TIM3 


/**********************************************************************/
/******* TIM4 -- PB6_CH1 -- PB7_CH2 ***********************************/

#define EncoderC_CH1_PIN               GPIO_Pin_6   
#define EncoderC_CH1_GPIO_PORT         GPIOB
#define EncoderC_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderC_CH1_SOURCE            GPIO_PinSource6
#define EncoderC_CH1_AF                GPIO_AF_TIM4 


#define EncoderC_CH2_PIN               GPIO_Pin_7   
#define EncoderC_CH2_GPIO_PORT         GPIOB
#define EncoderC_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderC_CH2_SOURCE            GPIO_PinSource7
#define EncoderC_CH2_AF                GPIO_AF_TIM4


/***********************************************************************/
/******* TIM12 -- PB14_CH1 -- PB15_CH2 ***********************************/

#define EncoderD_CH1_PIN               GPIO_Pin_14 
#define EncoderD_CH1_GPIO_PORT         GPIOB
#define EncoderD_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderD_CH1_SOURCE            GPIO_PinSource14
#define EncoderD_CH1_AF                GPIO_AF_TIM12 


#define EncoderD_CH2_PIN               GPIO_Pin_15 
#define EncoderD_CH2_GPIO_PORT         GPIOB
#define EncoderD_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define EncoderD_CH2_SOURCE            GPIO_PinSource15
#define EncoderD_CH2_AF                GPIO_AF_TIM12 


/***********************************************************************/
#define EncoderA_MODE							 TIM_EncoderMode_TI12 
#define EncoderB_MODE							 TIM_EncoderMode_TI12
#define EncoderC_MODE							 TIM_EncoderMode_TI12
#define EncoderD_MODE							 TIM_EncoderMode_TI12


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

extern float velocity[3];
extern int32_t coordinate[3];

uint32_t periodEncoderPulse(int MOTOR);


extern void encoderInit(void);
extern void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
extern void encoderInterrupt(void);
extern void encoderReset(void);
extern void readEncoder(int MOTOR);


