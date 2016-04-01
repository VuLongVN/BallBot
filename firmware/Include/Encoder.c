/**
 * @file	Encoder.c
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */


#include "include.h"

float varphi[3];
float arc[3];
float omega[3];

float phi[3];
float	velocity[3];

int32_t coordinate[3];

volatile int64_t CountEncoderA;
volatile int64_t CountEncoderB;
volatile int64_t CountEncoderC;
volatile int64_t CountEncoderD;

volatile int64_t OldCountEncoderA;
volatile int64_t OldCountEncoderB;
volatile int64_t OldCountEncoderC;
volatile int64_t OldCountEncoderD;

uint16_t counterEncoderPulse[3];
int64_t NumEncoder = 0;
uint16_t encoderResolution = 20;

void encoderInit(void);
void encoder2PhiOfBall(float localArc[3], float localPhi[3]);
void encoderInterrupt(void); // cofigured in  stm32f4xx_it.c 
void encoderReset(void);
void readEncoder(int MOTOR);


void encoderInit()
{	
	TIM_TimeBaseInitTypeDef    	Encoder_TimeBaseStructure;
	GPIO_InitTypeDef           	Encoder_GPIOInitStructure;
	NVIC_InitTypeDef 						Encoder_NVIC_InitStructure;
	TIM_ICInitTypeDef						Encoder_TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(EncoderA_TIMER_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(EncoderB_TIMER_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(EncoderC_TIMER_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(EncoderD_TIMER_CLK, ENABLE);
	
  RCC_AHB1PeriphClockCmd(EncoderA_CH1_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd(EncoderA_CH2_GPIO_CLK, ENABLE); 
  RCC_AHB1PeriphClockCmd(EncoderB_CH1_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd(EncoderB_CH2_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(EncoderC_CH1_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd(EncoderC_CH2_GPIO_CLK, ENABLE);	
  RCC_AHB1PeriphClockCmd(EncoderD_CH1_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd(EncoderD_CH2_GPIO_CLK, ENABLE);
  
  Encoder_GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF;
  Encoder_GPIOInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  Encoder_GPIOInitStructure.GPIO_OType = GPIO_OType_PP;
  Encoder_GPIOInitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &Encoder_GPIOInitStructure); 
  
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderA_CH1_PIN ;
  GPIO_PinAFConfig(EncoderA_CH1_GPIO_PORT, EncoderA_CH1_SOURCE, EncoderA_CH1_AF);
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderA_CH2_PIN ;
  GPIO_PinAFConfig(EncoderA_CH2_GPIO_PORT, EncoderA_CH2_SOURCE, EncoderA_CH2_AF);
	
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderB_CH1_PIN ;
  GPIO_PinAFConfig(EncoderB_CH1_GPIO_PORT, EncoderB_CH1_SOURCE, EncoderB_CH1_AF);
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderB_CH2_PIN ;
  GPIO_PinAFConfig(EncoderB_CH2_GPIO_PORT, EncoderB_CH2_SOURCE, EncoderB_CH2_AF);
	
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderC_CH1_PIN ;
  GPIO_PinAFConfig(EncoderC_CH1_GPIO_PORT, EncoderC_CH1_SOURCE, EncoderC_CH1_AF);
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderB_CH2_PIN ;
  GPIO_PinAFConfig(EncoderC_CH2_GPIO_PORT, EncoderC_CH2_SOURCE, EncoderC_CH2_AF);

	
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderD_CH1_PIN ;
  GPIO_PinAFConfig(EncoderD_CH1_GPIO_PORT, EncoderD_CH1_SOURCE, EncoderD_CH1_AF);
	Encoder_GPIOInitStructure.GPIO_Pin = EncoderD_CH2_PIN ;
  GPIO_PinAFConfig(EncoderD_CH2_GPIO_PORT, EncoderD_CH2_SOURCE, EncoderD_CH2_AF);
	
	
  /* Time base configuration */
  Encoder_TimeBaseStructure.TIM_Prescaler = 1;   
  Encoder_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;
  Encoder_TimeBaseStructure.TIM_ClockDivision = 0;
	
  TIM_TimeBaseInit(EncoderA_TIMER, &Encoder_TimeBaseStructure);
  TIM_ARRPreloadConfig(EncoderA_TIMER, ENABLE);
	TIM_EncoderInterfaceConfig(EncoderA_TIMER, EncoderA_MODE, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // TIM_EncoderMode_TI1 la dem TIMER 1 va dung TIMER 2 de tham chieu 
	TIM_TimeBaseInit(EncoderA_TIMER, &Encoder_TimeBaseStructure);
	
  TIM_TimeBaseInit(EncoderB_TIMER, &Encoder_TimeBaseStructure);
  TIM_ARRPreloadConfig(EncoderB_TIMER, ENABLE);
	TIM_EncoderInterfaceConfig(EncoderB_TIMER, EncoderB_MODE, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_TimeBaseInit(EncoderB_TIMER, &Encoder_TimeBaseStructure);
		
  TIM_TimeBaseInit(EncoderC_TIMER, &Encoder_TimeBaseStructure);
  TIM_ARRPreloadConfig(EncoderC_TIMER, ENABLE);
	TIM_EncoderInterfaceConfig(EncoderC_TIMER, EncoderC_MODE, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_TimeBaseInit(EncoderC_TIMER, &Encoder_TimeBaseStructure);
		
  TIM_TimeBaseInit(EncoderD_TIMER, &Encoder_TimeBaseStructure);
  TIM_ARRPreloadConfig(EncoderD_TIMER, ENABLE);
	TIM_EncoderInterfaceConfig(EncoderD_TIMER, EncoderD_MODE, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_TimeBaseInit(EncoderD_TIMER, &Encoder_TimeBaseStructure);
 
  
	Encoder_TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
	Encoder_TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
	Encoder_TIM_ICInitStructure.TIM_ICFilter= 0xF;
	Encoder_TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3, &Encoder_TIM_ICInitStructure);
	
	/*
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  Encoder_NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  Encoder_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  Encoder_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  Encoder_NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&Encoder_NVIC_InitStructure);  
 */
 
  TIM_ITConfig(EncoderA_TIMER, TIM_IT_Update, ENABLE);
	TIM_ITConfig(EncoderB_TIMER, TIM_IT_Update, ENABLE);
	TIM_ITConfig(EncoderC_TIMER, TIM_IT_Update, ENABLE);
	TIM_ITConfig(EncoderD_TIMER, TIM_IT_Update, ENABLE);
  TIM_Cmd(EncoderA_TIMER, ENABLE);
	TIM_Cmd(EncoderB_TIMER, ENABLE);
	TIM_Cmd(EncoderC_TIMER, ENABLE);
	TIM_Cmd(EncoderD_TIMER, ENABLE);
	encoderReset();
}

void encoderReset(void)
{
  __disable_irq();
	CountEncoderA=0;
	CountEncoderB=0;
	CountEncoderC=0;
	CountEncoderD=0;
//	NumEncoder = 0;   // su dung khi bo dem xung encoder bi tran 
	TIM_SetCounter(TIM3,0);
 // readEncoder();
  __enable_irq();
}

void readEncoder(int MOTOR)
{
	switch (MOTOR)
	{
		case MOTOR_A:
		{
		velocity[0] = (float)counterEncoderPulse[0] /(encoderResolution * 0.2 ) ; // 0.2 = Sample Time 
		CountEncoderA = ( TIM_GetCounter(EncoderA_TIMER)) ; 
			break;
		}
		case MOTOR_B:
		{
		velocity[1] = counterEncoderPulse[1] /( encoderResolution * 0.2) ;
		CountEncoderA =  ( TIM_GetCounter(EncoderB_TIMER)) ; 
			break;
		}
		case MOTOR_C:
		{
		velocity[2] = counterEncoderPulse[2] /( encoderResolution * 0.2) ;			
		CountEncoderC = ( TIM_GetCounter(EncoderC_TIMER)) ; 
			break;
		}
		case MOTOR_D:
		{		
		CountEncoderD =  ( TIM_GetCounter(EncoderD_TIMER)) ; 
			break;
		}
	}
}

void encoderInterrupt()
{
	counterEncoderPulse[0] = abs( TIM_GetCounter(EncoderA_TIMER) - OldCountEncoderA ) ;
	counterEncoderPulse[1] = abs( TIM_GetCounter(EncoderB_TIMER) - OldCountEncoderB )  ;
	counterEncoderPulse[2] = abs( TIM_GetCounter(EncoderC_TIMER) - OldCountEncoderC ) ;
	OldCountEncoderA = TIM_GetCounter(EncoderA_TIMER);
	OldCountEncoderB = TIM_GetCounter(EncoderB_TIMER);
	OldCountEncoderC = TIM_GetCounter(EncoderC_TIMER);
}


