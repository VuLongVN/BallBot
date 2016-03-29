/**
 * @file	Button.h
 * @brief	Button
 * @authors VuLong DuyKhanh
 */


#ifndef __BUTTON_H
#define __BUTTON_H

#include "include.h"

#define PA0_EXTI_LINE 									(EXTI_Line0)
#define PA0_EXTI_PIN										(GPIO_Pin_0)
#define PA0_EXTI_BASE										(GPIOB)


extern EXTI_InitTypeDef IT_buttonInitStructure;
extern GPIO_InitTypeDef GPIO_buttonInitStructure;
extern NVIC_InitTypeDef NVIC_buttonInitStruct;

extern void initButtonOnDiscoveryBoard(void);

#endif /* __BUTTON_H */
