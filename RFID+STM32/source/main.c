/*
* File: main.c
* Author: Duong Bao Nguyen
* Date: 4/18/2024
* Description: This file main file that executes the program
*/

/* PIN
SPI:  
			RST:	PIN_B8
			CS : 	PIN B9
			MISO: PIN B14
			MOSI: PIN B15
			SCK: 	PIN B13
			
UART:
			TX: PIN A9
			RX: PIN A10
			
LED: PIN A5

*/
#include "stm32f10x.h"
#include "uart_debug.h"
#include "stm32f1_rc522.h"
#include "delay.h"
#include "PWM.h"

#include "stdio.h"
#include "string.h"

uint8_t Key[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t WtC[] = "Card is accpect";  // write data to card
uint8_t RtC[16];										// read data from card

uint8_t UID[5];

uint8_t UID_accpect[5] = {0x74, 0xBC, 0xE6, 0x03, 0x2D};

uint8_t str[MAX_LEN];  // bien de luu byte data doc tu card
uint8_t status;

unsigned int check = 0;

void blink_led(void);

int main(void)
{
	UART_Config_debug();
	Tim_init();
	MFRC522_Init();
	Tim_PWMinit();
	
	
	while(1)
	{				
		TIM_SetCompare4(TIM3, 180);
		
	}	
}

void blink_led(void)
{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		delay_ms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		delay_ms(500);
}
