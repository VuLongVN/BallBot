#include "include.h"

USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

void USART_Configuration(unsigned int BaudRate);
void SendUSART(USART_TypeDef* USARTx,uint16_t ch);


int GetUSART(USART_TypeDef* USARTx);
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
  #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}



void USART_Configuration(unsigned int BaudRate)
{
	
  RCC_APB2PeriphClockCmd(UART_UART_CLK, ENABLE); 
  RCC_AHB1PeriphClockCmd(UART_GPIO_CLK, ENABLE);
  
 /*  Configure USART  as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
  GPIO_InitStructure.GPIO_Pin = UART_PIN_TX | UART_PIN_RX;
  GPIO_Init(UART_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(UART_PORT,UART_SOURCE_TX,UART_AF); 
  GPIO_PinAFConfig(UART_PORT,UART_SOURCE_RX,UART_AF); 


  
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(UART_CHANNEL, &USART_InitStructure);
  
  USART_Cmd(UART_CHANNEL, ENABLE); 
	
}


void SendUSART(USART_TypeDef* USARTx,uint16_t ch)
{
  USART_SendData(USARTx, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USARTx, USART_IT_TXE) == RESET)
  {}
}


int GetUSART(USART_TypeDef* USARTx)
{
  while (USART_GetFlagStatus(USARTx, USART_IT_RXNE) == RESET)
  {}
  return USART_ReceiveData(USARTx);
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
GETCHAR_PROTOTYPE
{
  return GetUSART(USART1);
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

