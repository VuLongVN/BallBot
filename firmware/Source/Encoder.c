/**
 * @file	Encoder.c
 * @brief	Encoder
 * @authors VuLong DuyKhanh
 */


#include "include.h"

volatile uint64_t periodEncoderPulse[4];
volatile uint64_t counterEncoderPulse[4];
volatile uint64_t previousCounterEncoderPulse[4];

extern volatile bool enableEncoderInterrupt;

int64_t NumEncoder = 0;

void encoderInit(void);
void encoderInterrupt(void); // cofigured in  stm32f4xx_it.c 
void encoderReset(void);
void readEncoder(int8_t MOTOR);


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
	counterEncoderPulse[MOTOR_A]=0;
	counterEncoderPulse[MOTOR_B]=0;
	counterEncoderPulse[MOTOR_C]=0;
	counterEncoderPulse[MOTOR_D]=0;
	//	NumEncoder = 0;   // su dung khi bo dem xung encoder bi tran 
	TIM_SetCounter(TIM3,0);
	// readEncoder();
	__enable_irq();
}

void readEncoder(int8_t MOTOR)
{
	switch (MOTOR)
	{
		case MOTOR_A:
		{
			//velocity[MOTOR_A] = (float)counterEncoderPulse[MOTOR_A] /(ENCODER_PULSES*SAMPLE_TIME_ENCODER*MICRO_S);
			counterEncoderPulse[MOTOR_A] = (TIM_GetCounter(EncoderA_TIMER)) ; 
			break;
		}
		case MOTOR_B:
		{
			//velocity[MOTOR_B] = counterEncoderPulse[MOTOR_B] /( ENCODER_PULSES *SAMPLE_TIME_ENCODER*MICRO_S) ;
			counterEncoderPulse[MOTOR_B]  =  (TIM_GetCounter(EncoderB_TIMER)) ; 
			break;
		}
		case MOTOR_C:
		{
			//velocity[MOTOR_C] = counterEncoderPulse[MOTOR_C] /( ENCODER_PULSES *SAMPLE_TIME_ENCODER*MICRO_S) ;			
			counterEncoderPulse[MOTOR_C]  = (TIM_GetCounter(EncoderC_TIMER)) ; 
			break;
		}
		case MOTOR_D:
		{		
			//velocity[MOTOR_D] = counterEncoderPulse[MOTOR_D] /( ENCODER_PULSES *SAMPLE_TIME_ENCODER*MICRO_S) ;	
			counterEncoderPulse[MOTOR_D]  =  ( TIM_GetCounter(EncoderD_TIMER)) ; 
			break;
		}
	}
}


void encoderInterrupt()
{
	enableEncoderInterrupt = false;
	//counterEncoderPulse[MOTOR_A] = abs(TIM_GetCounter(EncoderA_TIMER) - previousCounterEncoderPulse[MOTOR_A]);
	counterEncoderPulse[MOTOR_B] = abs(TIM_GetCounter(EncoderB_TIMER) - previousCounterEncoderPulse[MOTOR_B]);
	//counterEncoderPulse[MOTOR_C] = abs(TIM_GetCounter(EncoderC_TIMER) - previousCounterEncoderPulse[MOTOR_C]);
	//previousCounterEncoderPulse[MOTOR_A] = TIM_GetCounter(EncoderA_TIMER);
	previousCounterEncoderPulse[MOTOR_B] = TIM_GetCounter(EncoderB_TIMER);
	//previousCounterEncoderPulse[MOTOR_C] = TIM_GetCounter(EncoderC_TIMER);
}

