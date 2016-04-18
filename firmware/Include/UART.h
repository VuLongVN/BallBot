/**
 * @file	UART.h
 * @brief	UART
 * @authors VuLong DuyKhanh
 */


#ifndef __UART_H
#define __UART_H

#include "include.h"

// #define UART_PIN_TX 						GPIO_Pin_2 
// #define UART_PIN_RX 						GPIO_Pin_3
// #define UART_PORT  						GPIOA
// #define UART_GPIO_CLK  					RCC_AHB1Periph_GPIOA
// #define UART_UART_CLK 				  	RCC_APB1Periph_USART2 
// #define UART_SOURCE_TX					GPIO_PinSource2
// #define UART_SOURCE_RX					GPIO_PinSource3
// #define UART_AF									GPIO_AF_USART2


/*
* \par Pinout
*
@verbatim
						 |PINSPACK 1     |PINSPACK 2     |PINSPACK 3	
U(S)ARTX     |TX     RX      |TX     RX      |TX     RX
USART1       |PA9    PA10    |PB6    PB7     |-      -
USART2       |PA2    PA3     |@PD5  @PD6     |-      -
USART3       |PB10   PB11    |PC10   PC11    |PD8    PD9
UART4        |PA0    PA1     |PC10   PC11    |-      -
UART5        |PC12   PD2     |-      -       |-      -
USART6       |PC6    PC7     |PG14   PG9     |-      -
UART7        |PE8    PE7     |PF7    PF6     |-      -
UART8        |PE1    PE0     |-      -       |-      -
*/
#define UART_CHANNEL						UART4
#define UART_PINSPACK 					TM_USART_PinsPack_2
#define UART_BAUDRATE						9600


extern void USARTconfiguration(USART_TypeDef* localUSARTx, TM_USART_PinsPack_t localPinsPack, uint32_t localBaudrate);
extern void USARTputString(USART_TypeDef* localUSARTx, char *localChar);
extern uint8_t USARTgetChar(USART_TypeDef* localUSARTx);
//extern void testInitUART(void);

#endif /* __UART_H */
