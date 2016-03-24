#include "stm32f4xx_it.h"
#include "include.h"
volatile int count;
extern volatile uint8_t PWM_motorADutyCycle;

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

void DebugMon_Handler(void)
{}

void SVC_Handler(void)
{}

void PendSV_Handler(void)
{}

void SysTick_Handler(void)
{}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
		if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0))
	{
		count++;
		/* Do your stuff when PA0 is changed */
    GPIO_ToggleBits(LEDD_BASE,LEDD_PIN);
		PWM_motorADutyCycle +=5;
		if (PWM_motorADutyCycle>= 100)
			PWM_motorADutyCycle = 100;
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(PA0_EXTI_LINE);
	}
}

void EXTI9_5_IRQHandler(void)
{

}
