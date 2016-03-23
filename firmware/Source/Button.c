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
	  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PA0 pin as input floating */
  GPIO_buttonInitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_buttonInitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_buttonInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_buttonInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_buttonInitStructure.GPIO_Pin = PA0_EXTI_PIN;
  GPIO_Init(GPIOB, &GPIO_buttonInitStructure);

  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI Line0 */
	/* PA0 is connected to EXTI_Line0 */
  IT_buttonInitStructure.EXTI_Line = PA0_EXTI_LINE;
	/* Interrupt mode */
  IT_buttonInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on falling edge */
  IT_buttonInitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	/* Enable interrupt */	
  IT_buttonInitStructure.EXTI_LineCmd = ENABLE;
	/* Add to EXTI */
  EXTI_Init(&IT_buttonInitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
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



