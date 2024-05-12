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
#include <stdio.h>
#include "string.h"


#include "uart_debug.h"
#include "stm32f1_rc522.h"
#include "delay.h"
#include "PWM.h"


struct FILE
{
  int handle;
};
/* FILE is typedef'd in stdio.h. */
FILE __stdout;
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == 0){};
  return ch;
}

uint8_t Key[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t WtC[] = "Card is accpect";  // write data to card
uint8_t RtC[16];										// read data from card

uint8_t UID[5];

uint8_t UID_accpect_1[5] = {0x74, 0xBC, 0xE6, 0x03, 0x2D}; //White card
uint8_t UID_accpect_2[5] = {0xC1, 0x09, 0x98, 0x1D, 0x4D};	//Blue card

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
	
//	while(1) {
//		//USART_SendData(USART2,'H');
//		blink_led();
//		
//	}
	while(1)
	{			
//		TIM_SetCompare2(TIM2, 250);
//		delay_ms(100);
//		TIM_SetCompare2(TIM2, 750);
//		delay_ms(100);
		
		printf("Start RFID\n");
		delay_ms(100);
//		status = MI_ERR;
//		while(status != MI_OK) {	
//			status  = MFRC522_Request(PICC_REQIDL,str);  // check your card are put into yet??
//			delay_ms(100);
//			blink_led();
//		}
//		//printf("Find your ID card");
//		status = MFRC522_Anticoll(str);			// chong de the len nhau va kiem tra data doc co trung ko
//		memcpy(UID, str, 5);
//		delay_ms(100);
//		
//		if(status == MI_OK)
//		{
//			//printf("ID card number: %x, %x, %x, %x, %x", UID[0], UID[1], UID[2], UID[3], UID[4]);
//			if((UID[0]==116) && (UID[1]==188) && (UID[2]==230) && (UID[3]==3) && (UID[4]==45) )
//      {
//				check = 1;
//			}else check = 0;
//		}
//		
//		if(check == 1)
//		{
//			//printf("Correct id card");
//			MFRC522_SelectTag(str);
//			MFRC522_Auth(PCD_AUTHENT, 2, Key, UID);
//			//printf("Sucessfully");
//			
//			while(1)
//			{
//				GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//				delay_ms(100);
//				GPIO_SetBits(GPIOA, GPIO_Pin_5);
//				delay_ms(100);
//			}

//		}
		
		//MFRC522_StopCrypto1();
		//printf("RFID STOP");
	}	
}

void blink_led(void)
{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		delay_ms(500);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		delay_ms(500);
}

