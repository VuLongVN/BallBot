#include "include.h"

void GPIOConfig(void);
volatile uint8_t PWM_motorADutyCycle = 5;

int main(void)
{
	SysTick_Config(SystemCoreClock/168);
	GPIOConfig();
	PWMConfig();
  motorDirConfig();

	#ifdef TEST
	// GPIO_WriteBit(MOTOR_A_DIR_BASE, MOTOR_A_DIR_PIN, Bit_SET);
	// GPIO_WriteBit(MOTOR_A_SPEED_BASE, MOTOR_A_SPEED_PIN, Bit_SET);
	
	#endif

	#ifdef TESTBUTTON
	initButtonOnDiscoveryBoard();
	#endif
	
  while (1)
		{
			#ifdef TESTMOTOR
			PWMControl(MOTOR_A, CLOCKWISE, PWM_motorADutyCycle);
//			PWMControl(MOTOR_B, CLOCKWISE, 50);
//			PWMControl(MOTOR_C, CLOCKWISE, 50);
//			PWMControl(MOTOR_D, CLOCKWISE, 50);
			#endif
			
			
		}
}

void GPIOConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = LEDA_PIN|LEDB_PIN|LEDC_PIN|LEDD_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LEDA_BASE, &GPIO_InitStructure);
}

