/*
* File: main.c
* Author: Duong Bao Nguyen
* Date: 4/18/2024
* Description: This file main how to use Retarget Printf
*/

#include "stm32f10x.h"
#include <stdio.h>
#include "string.h"
#include "stm32f10x_usart.h"

#define	UART_GPIO 	GPIOA
#define	UART_TX 		GPIO_Pin_9
#define	UART_RX			GPIO_Pin_10


struct FILE
{
  int handle;
};
/* FILE is typedef'd in stdio.h. */
FILE __stdout;
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint16_t) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == 0){}
  return ch;
}


void UART_Config_debug(void);


int main(void)
{
	UART_Config_debug();
	while(1)
	{			
		printf("Start RFID\n");
		//delay_ms(100);
	}
}


void UART_Config_debug(void){
	GPIO_InitTypeDef GPIOInitStruct;
	USART_InitTypeDef USARTInitStruct;
	//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	//
	GPIOInitStruct.GPIO_Pin = UART_TX;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART_GPIO, &GPIOInitStruct);
	//
	GPIOInitStruct.GPIO_Pin = UART_RX;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART_GPIO, &GPIOInitStruct);

	//Usart
	USARTInitStruct.USART_BaudRate = 9600;
	USARTInitStruct.USART_WordLength = USART_WordLength_8b;
	USARTInitStruct.USART_StopBits = USART_StopBits_1;
	USARTInitStruct.USART_Parity = USART_Parity_No;
	USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USARTInitStruct);
	USART_Cmd(USART1,ENABLE);
}
