/**
 * @file	MotorControl.h
 * @brief	Motor Control
 * @authors VuLong DuyKhanh
 */

#ifndef __SPEEDCONTROL_H
#define __SPEEDCONTROL_H

#include "include.h"

extern TIM_TimeBaseInitTypeDef    	PWM_TimeBaseStructure;
extern TIM_OCInitTypeDef          	PWM_OCInitStructure;
extern GPIO_InitTypeDef           	PWM_GPIOInitStructure;
extern GPIO_InitTypeDef           	GPIO_MotorDirInitStructure;

#define MOTOR_A_DIR_PIN			(GPIO_Pin_4)			// Pin PA4
#define MOTOR_B_DIR_PIN			(GPIO_Pin_1)			// Pin PA1
#define MOTOR_C_DIR_PIN			(GPIO_Pin_9)			// Pin PB9
#define MOTOR_D_DIR_PIN			(GPIO_Pin_4)			// Pin PE4

#define MOTOR_A_DIR_BASE		(GPIOA)						// Pin PA4
#define MOTOR_B_DIR_BASE		(GPIOA)						// Pin PA1
#define MOTOR_C_DIR_BASE		(GPIOB)						// Pin PB9
#define MOTOR_D_DIR_BASE		(GPIOE)						// Pin PE4

#define CLOCKWISE						(1)
#define COUNTER_CLOCKWISE		(0)

#define MOTOR_A_SPEED_PIN		(GPIO_Pin_2)			// Pin PA2
#define MOTOR_B_SPEED_PIN		(GPIO_Pin_3)			// Pin PA3
#define MOTOR_C_SPEED_PIN		(GPIO_Pin_8)			// Pin PB8
#define MOTOR_D_SPEED_PIN		(GPIO_Pin_6)			// Pin PE6

#define MOTOR_A_SPEED_BASE	(GPIOA)						// Pin PA2
#define MOTOR_B_SPEED_BASE	(GPIOA)						// Pin PA3
#define MOTOR_C_SPEED_BASE	(GPIOB)						// Pin PB8
#define MOTOR_D_SPEED_BASE	(GPIOE)						// Pin PE6
	
#define PWM_MOTOR_A_PERIPH	(RCC_AHB1Periph_GPIOA)		// Pin PA2
#define PWM_MOTOR_B_PERIPH	(RCC_AHB1Periph_GPIOA)		// Pin PA3
#define PWM_MOTOR_C_PERIPH	(RCC_AHB1Periph_GPIOB)		// Pin PB8
#define PWM_MOTOR_D_PERIPH	(RCC_AHB1Periph_GPIOE)		// Pin PE6

#define MOTOR_A_AF_PIN			(GPIO_PinSource2)
#define MOTOR_B_AF_PIN			(GPIO_PinSource3)
#define MOTOR_C_AF_PIN			(GPIO_PinSource8)
#define MOTOR_D_AF_PIN			(GPIO_PinSource6)

#define MOTOR_A_AF_TIM			(GPIO_AF_TIM2)
#define MOTOR_B_AF_TIM			(GPIO_AF_TIM2)
#define MOTOR_C_AF_TIM			(GPIO_AF_TIM4)
#define MOTOR_D_AF_TIM			(GPIO_AF_TIM9)

#define LEDA_PIN 						(GPIO_Pin_12)			// Pin PD12
#define LEDB_PIN 						(GPIO_Pin_13)			// Pin PD13
#define LEDC_PIN 						(GPIO_Pin_14)			// Pin PD14
#define LEDD_PIN 						(GPIO_Pin_15)			// Pin PD15

#define LEDA_BASE 					(GPIOD)
#define LEDB_BASE 					(GPIOD)
#define LEDC_BASE 					(GPIOD)
#define LEDD_BASE 					(GPIOD)

extern TIM_TimeBaseInitTypeDef    	PWM_TimeBaseStructure;
extern TIM_OCInitTypeDef          	PWM_OCInitStructure;
extern GPIO_InitTypeDef           	PWM_GPIOInitStructure;
extern GPIO_InitTypeDef           	GPIO_MotorDirInitStructure;

extern void PWMConfig(void);
/**
	* @function PWMControl(int motorJ  ,int  moterDir , int motorSpeed)
  * @brief  	Control Motor A, B, C or D       
  * @param 		motorJ  : PWM pin where x can be 	A ( connected to Pin PA2)
																								B ( connected to Pin PA3)
																								C ( connected to Pin PB8)
																								D ( connected to Pin PE6)
	* @param 		moterDir : Direction of Motor can be 	1 Clock-wise     ( Affected to Pin PA0 , PA1 or PB9 or PE4)
																										0 AntiClock-wise
  * @param 		motorSpeed : DutyCycle of PWM Pulse (max = 1000)
  * @retval 	None
  */
extern void PWMControl(int motorJ  ,int  moterDir , int motorSpeed);
extern void motorDirConfig(void);
#endif /* __SPEED_CONTROL_H*/
