#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#define SPI_GPIO 			GPIOA
#define SPI_MISO_Pin 	GPIO_Pin_8

#define SPI_MOSI_Pin 	GPIO_Pin_5
#define SPI_CS_Pin 		GPIO_Pin_6
#define SPI_SCK_Pin 	GPIO_Pin_7

void Config_rcc(void);
void Config_GPIO(void);
void Config_timer(void);
void GPIO_SPI_Init(void);
void SPI_SCK_CLOCK(void);

void delay_ms(uint16_t ms);

int main()
{
	Config_rcc();
	Config_GPIO();
	Config_timer();
	GPIO_SPI_Init();
	SPI_SCK_CLOCK();
	
	while(1)
	{
		
		
		
	}
}
void delay_ms(uint16_t ms)	{
	
	
}
void SPI_SCK_CLOCK(void)	{
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);
	delay_ms(4);
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	delay_ms(4);
}

void GPIO_SPI_Init(void) {
	GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_SET);
	
}

void Config_timer(void) {
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_Prescaler = 999;
	TIM_InitStructure.TIM_Period = 9;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
}


void Config_rcc(void) {
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
