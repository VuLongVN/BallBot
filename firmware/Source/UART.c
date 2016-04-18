/**
 * @file	UART.c
 * @brief	UART
 * @authors VuLong DuyKhanh
 */

#include "include.h"

void USARTconfiguration(USART_TypeDef* localUSARTx, TM_USART_PinsPack_t localPinsPack, uint32_t localBaudrate);
void USARTputString(USART_TypeDef* localUSARTx, char *localChar);
uint8_t USARTgetChar(USART_TypeDef* localUSARTx);

void USARTconfiguration(USART_TypeDef* localUSARTx, TM_USART_PinsPack_t localPinsPack, uint32_t localBaudrate)
{
	TM_USART_Init(localUSARTx, localPinsPack, localBaudrate);
}

void USARTputString(USART_TypeDef* locelUSARTx, char *ch)
{
	TM_USART_Puts(locelUSARTx, ch);
}

uint8_t USARTgetChar(USART_TypeDef* locelUSARTx)
{
	return TM_USART_Getc(locelUSARTx);
}
