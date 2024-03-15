#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

void config_rcc(void);
void config_timer(void);

int main()
{

}


void config_rcc(void)
{
	RCC_AHBPeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
}

void config_timer(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //APB1 = 36M bo chia nho clock (chia 1,2,4)
	TIM_InitStructure.TIM_Prescaler = 999;
	TIM_InitStructure.TIM_Period = 9;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
}
