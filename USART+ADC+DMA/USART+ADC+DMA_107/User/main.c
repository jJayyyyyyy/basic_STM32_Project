#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "adc.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "rcc_gpio.h"
#include "tim.h"
#include "usart.h"
#include <stdio.h>

#define PRINTF_ON 1
#define VREF 3.3

extern __IO int Increment_High;
extern __IO int Increment_Low;

void System_Init(void);

int main(){
	__IO float ADValue = 0.00;
	__IO int duty=0;
	
	System_Init();
	while(1){
		ADValue = ADC_GetValue(VREF);
		duty = (int) ADValue * 100 / VREF;
		Increment_High = duty+5;
		Increment_Low = 120 - Increment_High;
		printf("\r\n ADValue = %.2f V\r\n", ADValue);		
		delay_ms(150);
	}
}



void System_Init(void){
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();
	ADC_Configuration();
	TIM_Configuration();
	NVIC_Configuration();
	if(SysTick_Config(SystemCoreClock / 1000)){
		GPIO_ResetBits(LED_OUT , GPIO_Pin_5);
		while(1);
	}
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;	
}

#if	PRINTF_ON
int fputc(int ch,FILE *f){
    USART_SendData(USART1,(u8) ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    return ch;
}
#endif

#if SCANF_ON
int fgetc(FILE *f){
   while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)); 
   return (USART_ReceiveData(USART1));
}
#endif

