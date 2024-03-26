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
void SPI_Master_Transmit(uint8_t u8Data);

void delay_ms(uint16_t ms);




//uint8_t DataTrans[7] = {1,3,9,10,15,19,90};

uint8_t DataTrans[] = {3, 7, 6, 4, 71, 23, 11, 14};
int main(void)
{
	Config_rcc();
	Config_GPIO();
	Config_timer();
	GPIO_SPI_Init();
	SPI_SCK_CLOCK();
	
	while(1)
	{
			for(int i = 0; i < 7; i++){
			SPI_Master_Transmit(DataTrans[i]);
			delay_ms(500);
			}
	}
}

void SPI_Master_Transmit(uint8_t Data){//0b10010000
	uint8_t Mask = 0x80;// 0b10000000
	uint8_t tempData;
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	delay_ms(1);
	for(int i=0; i<8; i++){
		tempData = Data & Mask;
		if(tempData){
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
			delay_ms(1);
		} else{
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
			delay_ms(1);
		}
		Data = Data << 1;
		SPI_SCK_CLOCK();
	}
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	delay_ms(1);
}


void delay_ms(uint16_t ms)	{
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 10*ms) {}
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
	TIM_InitStructure.TIM_Prescaler = 36000 - 1; 
	TIM_InitStructure.TIM_Period = 0xFFFF - 1;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
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
