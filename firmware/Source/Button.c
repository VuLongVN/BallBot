/**
 * @file	Button.c
 * @brief	Button
 * @authors VuLong DuyKhanh
 */

#include "include.h"

EXTI_InitTypeDef IT_buttonInitStructure;
GPIO_InitTypeDef GPIO_buttonInitStructure;
NVIC_InitTypeDef NVIC_buttonInitStruct;

void initButtonOnDiscoveryBoard(void)
{
	/* Enable clock for GPIOA */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable clock for SYSCFG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	/* Set pin as input */
	GPIO_buttonInitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_buttonInitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_buttonInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_buttonInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_buttonInitStructure.GPIO_Pin = PA0_EXTI_PIN;
	GPIO_Init(PA0_EXTI_BASE, &GPIO_buttonInitStructure);
	
	/* Tell system that you will use PA0 for EXTI_Line0 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	/* PA0 is connected to EXTI_Line0 */
	IT_buttonInitStructure.EXTI_Line = PA0_EXTI_LINE;
	/* Enable interrupt */
	IT_buttonInitStructure.EXTI_LineCmd = ENABLE;
	/* Interrupt mode */
	IT_buttonInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising edge */
	IT_buttonInitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	/* Add to EXTI */
	EXTI_Init(&IT_buttonInitStructure);
	
	/* Add IRQ vector to NVIC */
	/* PA0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
	NVIC_buttonInitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	/* Set priority */
	NVIC_buttonInitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	/* Set sub priority */
	NVIC_buttonInitStruct.NVIC_IRQChannelSubPriority = 0x00;
	/* Enable interrupt */
	NVIC_buttonInitStruct.NVIC_IRQChannelCmd = ENABLE;
	/* Add to NVIC */
	NVIC_Init(&NVIC_buttonInitStruct);
}

