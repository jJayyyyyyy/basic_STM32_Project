#include "stm32f10x.h"
#include "delay.h"
#include "led.h"


void LED_Blink(){
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;	
	delay_ms(500);

	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	delay_ms(500);
}

void LED_by_KEY(int key){
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	switch(key)
	{
		case 1:
			LED1_ON;
			break;
		case 2:
			LED2_ON;
			break;
		case 3:
			LED3_ON;
			break;
		case '4':
			LED4_ON;
			break;
		default:
			break;
	}
}
