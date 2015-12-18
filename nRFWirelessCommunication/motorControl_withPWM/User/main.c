#include "stm32f10x.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "nRF24L01.h"
#include "pwm_control.h"
#include "rcc_gpio.h"
#include "tim.h"
#include "spi.h"
#include "stm32f10x_spi.h"

void System_Init(void);

int main()
{
	unsigned char keyValue[1] = {0};

	System_Init();
	while(NRF24L01_Check())			//24L01在线检测
    {
        LED4_ON;
		//printf("没有检测到NRF24L01，请确认NRF24L01是否连接上！\n\r");
		delay_ms(700);
		LED4_OFF;
		delay_ms(500);
	}
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	RX_Mode();

	while(1){
		keyValue[0] = KEY_Pressed(); 					//读取按键值
		if(keyValue[0]){								//如果有键按下，则进入到发送模式，并将键值发送出去		
			TX_Mode();	  								//发送模式
			if(NRF24L01_TxPacket(keyValue) == TX_OK){	//如果发送成功			
				//printf("\n\r数据在发送中！");
			}
		    else{
				//printf("\n\r发送不成功，请检查接收端是否正常工作！");			    
		    }
			RX_Mode();									//发送完成后进入到接收模式
		}
		if(NRF24L01_RxPacket(keyValue) == 0){			//如果接收到按键值，则点亮相应的LED
			switch(keyValue[0]){
				case KEY1_VALUE:
					LED1_ON;
					forward();
					delay_ms(100);
					break;
				case KEY2_VALUE:
					LED2_ON;
					backward();
					delay_ms(100);
					break;
				case KEY3_VALUE:
					LED3_ON;
					delay_ms(100);
					break;
				case KEY4_VALUE:
					LED4_ON;
					delay_ms(100);				
					break;				
				default:
					break;			
			}
			//LED_by_KEY(keyValue[0]);
		}				
//		switch(keyValue[0]){
//			case KEY1_VALUE:
//				LED1_ON;
//				forward();
//				delay_ms(500);
//				break;
//			case KEY2_VALUE:
//				LED2_ON;
//				backward();
//				delay_ms(500);
//				break;
//			case KEY3_VALUE:
//				LED3_ON;
//				delay_ms(500);
//				break;
//			case KEY4_VALUE:
//				LED4_ON;
//				delay_ms(500);				
//				break;				
//			default:
//				break;			
//		}

		stopMov();
		LED1_OFF;
		LED2_OFF;
		LED3_OFF;
		LED4_OFF;		
	}
}

void System_Init(void){
	RCC_Configuration();
	GPIO_Configuration();
	TIM_Configuration();
	NVIC_Configuration();
	SPI_Configuration();
	NRF24L01_Init();
	
	if(SysTick_Config(SystemCoreClock / 1000)){
		GPIO_ResetBits(LED_OUT , GPIO_Pin_5);
		while(1);
	}
	NVIC_SetPriority(SysTick_IRQn, 0x0);
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}




