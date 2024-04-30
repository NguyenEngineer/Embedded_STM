#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

void config_rcc(void);
void config_timer(void);
void Config_GPIO(void);
void delay_ms (uint16_t ms);

int main(void)
{
	config_rcc();
	Config_GPIO();
	config_timer();
	
	while(1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		delay_ms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		delay_ms(500);
	}
	
}

void delay_ms (uint16_t ms)
{
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < ms){}
}

void config_rcc(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
}

void config_timer(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //APB1 = 36M bo chia nho clock (chia 1,2,4)
	TIM_InitStructure.TIM_Prescaler = 36000 - 1;		// so dao dong trong 1 ms, sau khi xong 1 ms thì period tang len 1
	TIM_InitStructure.TIM_Period = 65536 - 1;    // Bo dem tu nap lai
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	//TIM_Cmd(TIM2, ENABLE);
	
}

void Config_GPIO(void) {
	GPIO_InitTypeDef GPIO_InitSTructer;
	GPIO_InitSTructer.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitSTructer.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTructer.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitSTructer);
}
