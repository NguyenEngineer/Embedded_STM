#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


typedef enum{
	FLOW_LED,
	CHANGE_LED_BUTTON
} State;

void Config_rcc(void);
void Config_GPIO(void);
void delay(uint32_t value);
void flow_led(uint32_t *arr);

int main()
{
	Config_rcc();
	Config_GPIO();
	
	State mode = FLOW_LED;
	uint8_t cout = 0;
	
	uint32_t val_led[3] = {0x20, 0x40, 0x80};
	while(1)
	{
		switch(mode){
			case FLOW_LED:
				if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == 1)
				{
					flow_led(val_led);
				}else mode = CHANGE_LED_BUTTON;
				break;
				
			case CHANGE_LED_BUTTON:
				if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == 1)
				{
					if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0)
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_5);
						cout = 1;
					}else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0 && cout == 1)
					{
						GPIO_ResetBits(GPIOA, GPIO_Pin_5);
						cout = 0;
					}
				}else mode = FLOW_LED; //
				break;
		}

	}
}

void flow_led(uint32_t *arr) {
	GPIO_Write(GPIOC, 0);
	for(uint8_t i = 0; i < sizeof(arr); i++) {
		GPIO_Write(GPIOC, arr[i]);
		delay(50000000);
	}
}

void delay(uint32_t value){
	for(unsigned int i = 0; i < value; i++) {}
}

void Config_rcc(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void Config_GPIO(void) {
	GPIO_InitTypeDef GPIO_InitSTructer;
	GPIO_InitSTructer.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitSTructer.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitSTructer.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitSTructer);

	//input pc13 //
	GPIO_InitSTructer.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 ;
	GPIO_InitSTructer.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitSTructer.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitSTructer);
}
