/**
 * @file	UART.h
 * @brief	UART
 * @authors VuLong DuyKhanh
 */


#ifndef __UART_H
#define __UART_H

#include "include.h"

#define UART_PIN_TX 						GPIO_Pin_9 
#define UART_PIN_RX 						GPIO_Pin_10
#define UART_PORT  							GPIOA
#define UART_GPIO_CLK  					RCC_AHB1Periph_GPIOA
#define UART_UART_CLK 				  RCC_APB2Periph_USART1 
#define UART_SOURCE_TX					GPIO_PinSource9
#define UART_SOURCE_RX					GPIO_PinSource10
#define UART_AF									GPIO_AF_USART1




extern void USART_Configuration(unsigned int BaudRate);
extern void SendUSART(USART_TypeDef* USARTx,uint16_t ch);

#endif /* __UART_H */
