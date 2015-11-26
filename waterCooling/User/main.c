#include "stm32f10x.h"
#include "rcc_gpio.h"

void System_Init(void);

void delay(vu32 n){
	while(--n){
	
	}	
}

int main(void)
{
	System_Init();
	while(1){
		GPIO_SetBits(GPIOE, GPIO_Pin_5);
		GPIO_SetBits(GPIOE, GPIO_Pin_4);
		GPIO_SetBits(GPIOE, GPIO_Pin_3);
		GPIO_SetBits(GPIOE, GPIO_Pin_2);
		delay(3000000);
		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		GPIO_ResetBits(GPIOE, GPIO_Pin_4);
		GPIO_ResetBits(GPIOE, GPIO_Pin_3);
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
		delay(3000000);
	}
		
	return 0;
}

void System_Init(void){
	RCC_Configuration();
	GPIO_Configuration();

}
