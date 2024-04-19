#include"stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"


#define SPI_GPIO 			GPIOA
#define SPI_MISO_Pin 	GPIO_Pin_8

#define SPI_MOSI_Pin 	GPIO_Pin_5
#define SPI_CS_Pin 		GPIO_Pin_6
#define SPI_SCK_Pin 	GPIO_Pin_7


int main()
{
	
	
	
}


void config_RCC(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void Config_GPIO(void) {
	
	//input PA5,6,7 --> MOSI, SCK, CS //
	GPIO_InitTypeDef GPIO_InitSTructer;
	GPIO_InitSTructer.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitSTructer.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTructer.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitSTructer);

	//input PA8 --> MISO //
	GPIO_InitSTructer.GPIO_Pin =  GPIO_Pin_8 ;
	GPIO_InitSTructer.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitSTructer.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitSTructer);
	
}