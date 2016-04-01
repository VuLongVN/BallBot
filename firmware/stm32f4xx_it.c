#include "stm32f4xx_it.h"
#include "include.h"

static uint64_t IMUTick=0;
static uint64_t encoderTick=0;
static uint64_t PIDTick=0;
static uint64_t largerPIDTick=0;
static uint64_t LQGTick=0;

volatile int count;

extern volatile bool enableIMUInterrupt;
extern volatile bool enableEncoderInterrupt;
extern volatile bool enablePIDInterrupt;
extern volatile bool enableLargerPIDInterrupt;
extern volatile bool enableLQGInterrupt;

extern volatile uint8_t PWM_motorADutyCycle;
extern volatile uint8_t PWM_motorBDutyCycle;
extern volatile uint8_t PWM_motorCDutyCycle;
extern volatile uint8_t PWM_motorDDutyCycle;

extern int64_t NumEncoder;

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
{
  if (++IMUTick>=SAMPLE_TIME_IMU)
  {
    IMUTick = 0;
    enableIMUInterrupt = true;
  }
  if (++encoderTick>=SAMPLE_TIME_ENCODER)
  {
    encoderTick = 0;
    enableEncoderInterrupt = true;
  }
  if (++PIDTick>=SAMPLE_TIME_PID)
  {
    PIDTick = 0;
    enablePIDInterrupt = true;
  }
  if (++largerPIDTick>=PERIOD_TIME_PID)
  {
    largerPIDTick = 0;
    enableLargerPIDInterrupt = true;
  }
  if (++LQGTick>=PERIOD_TIME_LQG)
  {
    LQGTick = 0;
    enableLQGInterrupt = true;
  }
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0))
    {
      #ifdef TESTBUTTON
        count++;
        /* Do your stuff when PA0 is changed */
        GPIO_ToggleBits(LEDD_BASE, LEDD_PIN);
        PWM_motorADutyCycle +=5;
        if (PWM_motorADutyCycle>= 90)				PWM_motorADutyCycle = 90;
        PWM_motorBDutyCycle +=5;
        if (PWM_motorBDutyCycle>= 90)				PWM_motorBDutyCycle = 90;
      #endif
      /* Clear interrupt flag */
      EXTI_ClearITPendingBit(PA0_EXTI_LINE);
    }
}

void EXTI9_5_IRQHandler(void)
{

}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
   NumEncoder += 0xFFFFFFFF;   
   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
  }
}
