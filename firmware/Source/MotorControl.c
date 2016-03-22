/**
 * @file	speed control.c
 * @brief	speed control
 */

#include "include.h"

TIM_TimeBaseInitTypeDef    	PWM_TIM_TimeBaseStructure;
TIM_OCInitTypeDef          	PWM_TIM_OCInitStructure;
GPIO_InitTypeDef           	PWM_GPIO_InitStructure;
GPIO_InitTypeDef           	MotorDir_GPIO_InitStructure;

void PWMConfig(void);
void PWMControl(int motorJ  ,int  moterDir , int motorSpeed);
void motorDirConfig(void);


void PWMControl(int motorJ  ,int  moterDir , int motorSpeed)
{
	switch(motorJ)
	{
	case MOTOR_A:
	{
		GPIO_WriteBit(MOTOR_A_DIR_BASE, MOTOR_A_DIR_PIN, moterDir);
		#ifdef TEST
		GPIO_WriteBit(LEDA_BASE, LEDA_PIN, moterDir);
		#endif
		/* pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 � 1 */
		TIM2->CCR1 = motorSpeed * (TIM_PERIOD+1) / 100 - 1; 
		break;
	}		
	case MOTOR_B:
	{
		GPIO_WriteBit(MOTOR_B_DIR_BASE, MOTOR_B_DIR_PIN, moterDir);
		#ifdef TEST
		GPIO_WriteBit(LEDB_BASE, LEDB_PIN, moterDir);
		#endif
		/* pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 � 1 */
	  TIM2->CCR2 =   motorSpeed * (TIM_PERIOD+1) / 100 - 1;  
		break;
	}
	case MOTOR_C:
	{
		GPIO_WriteBit(MOTOR_C_DIR_BASE, MOTOR_C_DIR_PIN, moterDir);
		#ifdef TEST
		GPIO_WriteBit(LEDC_BASE, LEDC_PIN, moterDir);
		#endif
		/* pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 � 1 */
		TIM4->CCR1 =   motorSpeed * (TIM_PERIOD+1) / 100 - 1;  
		break;
	}
	case MOTOR_D:
	{
		GPIO_WriteBit(MOTOR_D_DIR_BASE, MOTOR_D_DIR_PIN, moterDir);
		#ifdef TEST
		GPIO_WriteBit(LEDD_BASE, LEDD_PIN, moterDir);
		#endif
		/* pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 � 1 */
		TIM9->CCR1 =   motorSpeed * (TIM_PERIOD+1) / 100 - 1;  
		break;
	}
	}
}

void PWMConfig(void)
{ 
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
  RCC_AHB1PeriphClockCmd(	PWM_MOTOR_A_PERIPH |\
													PWM_MOTOR_B_PERIPH | \
													PWM_MOTOR_C_PERIPH | \
													PWM_MOTOR_D_PERIPH , \
													ENABLE);
  
	PWM_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  PWM_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  PWM_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  PWM_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	
	
  PWM_GPIO_InitStructure.GPIO_Pin = MOTOR_A_SPEED_PIN;
  GPIO_Init(MOTOR_A_SPEED_BASE, &PWM_GPIO_InitStructure); 
	
	PWM_GPIO_InitStructure.GPIO_Pin = MOTOR_B_SPEED_PIN;
  GPIO_Init(MOTOR_B_SPEED_BASE, &PWM_GPIO_InitStructure); 
	
	PWM_GPIO_InitStructure.GPIO_Pin = MOTOR_C_SPEED_PIN;
  GPIO_Init(MOTOR_C_SPEED_BASE, &PWM_GPIO_InitStructure); 
	
	PWM_GPIO_InitStructure.GPIO_Pin = MOTOR_D_SPEED_PIN;
  GPIO_Init(MOTOR_D_SPEED_BASE, &PWM_GPIO_InitStructure); 
  

  GPIO_PinAFConfig(MOTOR_A_SPEED_BASE, MOTOR_A_AF_PIN, GPIO_AF_TIM2);  // Motor_A_PB8
  GPIO_PinAFConfig(MOTOR_B_SPEED_BASE, MOTOR_B_AF_PIN, GPIO_AF_TIM2);  // Motor_B_PA2
  GPIO_PinAFConfig(MOTOR_C_SPEED_BASE, MOTOR_C_AF_PIN, GPIO_AF_TIM4);  // Motor_C_PA3
  GPIO_PinAFConfig(MOTOR_D_SPEED_BASE, MOTOR_D_AF_PIN, GPIO_AF_TIM9); // Motor_D_PE6

  
  /* Time base configuration - Create 1KHz PWM Pulse  */
  PWM_TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;//  Timer_tick_frequence = 1MHz
  PWM_TIM_TimeBaseStructure.TIM_Period = TIM_PERIOD;
  PWM_TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  PWM_TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &PWM_TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM2, &PWM_TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM9, &PWM_TIM_TimeBaseStructure);

  PWM_TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  PWM_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  PWM_TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  PWM_TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
  PWM_TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  PWM_TIM_OCInitStructure.TIM_Pulse = 0;
  //TIM_OCStructInit(&TIM_OCInitStructure);
  
  TIM_OC1Init(TIM4, &PWM_TIM_OCInitStructure);  
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_OC2Init(TIM2, &PWM_TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OC3Init(TIM2, &PWM_TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
//TIM_OC4Init(TIM9, &PWM_TIM_OCInitStructure);
// TIM_OC4PreloadConfig(TIM9, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
//	TIM_ARRPreloadConfig(TIM9, ENABLE);

  /* TIM1 enable counter */
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM9, ENABLE);
 // TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void motorDirConfig(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  MotorDir_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  MotorDir_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  MotorDir_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  MotorDir_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  MotorDir_GPIO_InitStructure.GPIO_Pin = MOTOR_A_DIR_PIN;
  GPIO_Init(MOTOR_A_DIR_BASE, &MotorDir_GPIO_InitStructure);
	
	MotorDir_GPIO_InitStructure.GPIO_Pin = MOTOR_B_DIR_PIN;
  GPIO_Init(MOTOR_B_DIR_BASE, &MotorDir_GPIO_InitStructure);
	
	MotorDir_GPIO_InitStructure.GPIO_Pin = MOTOR_C_DIR_PIN;
  GPIO_Init(MOTOR_C_DIR_BASE, &MotorDir_GPIO_InitStructure);
	
	MotorDir_GPIO_InitStructure.GPIO_Pin = MOTOR_D_DIR_PIN;
  GPIO_Init(MOTOR_D_DIR_BASE, &MotorDir_GPIO_InitStructure);
}
