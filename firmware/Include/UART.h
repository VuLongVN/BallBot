/**
 * @file	UART.h
 * @brief	UART
 * @authors VuLong DuyKhanh
 */


#ifndef __UART_H
#define __UART_H

#include "include.h"

#define UART_PIN_TX 						GPIO_Pin_2 
#define UART_PIN_RX 						GPIO_Pin_3
#define UART_PORT  							GPIOA
#define UART_GPIO_CLK  					RCC_AHB1Periph_GPIOA
#define UART_UART_CLK 				  RCC_APB1Periph_USART2 
#define UART_SOURCE_TX					GPIO_PinSource2
#define UART_SOURCE_RX					GPIO_PinSource3
#define UART_AF									GPIO_AF_USART2
#define UART_CHANNEL						USART2




extern void USART_Configuration(unsigned int BaudRate);
extern void SendUSART(USART_TypeDef* USARTx,uint16_t ch);

#endif /* __UART_H */
