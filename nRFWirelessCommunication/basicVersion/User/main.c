#include "stm32f10x.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "nRF24L01.h"
#include "rcc_gpio.h"
#include "tim.h"
#include "spi.h"
#include "stm32f10x_spi.h"

void System_Init(void);

int main()
{
	unsigned char tmp_buf[1] = {0};

	System_Init();
	
	LED1_ON;

	while(NRF24L01_Check())			//24L01在线检测
    {
        LED4_ON;
		//printf("没有检测到NRF24L01，请确认NRF24L01是否连接上！\n\r");
		delay_ms(700);
		LED4_OFF;
		delay_ms(500);
	}
/*****熄灭四个led灯******/
	LED1_OFF;
	LED2_OFF;
	LED3_ON;
	LED4_OFF;
	RX_Mode();

	while(1){
		
		tmp_buf[0] = KEY_Pressed(); 			//读取按键值
		if(tmp_buf[0])						//如果有键按下，则进入到发送模式，并将键值发送出去
		{
			TX_Mode();	  					//发送模式
			if(NRF24L01_TxPacket(tmp_buf) == TX_OK)	//如果发送成功
			{
		    	//printf("\n\r数据在发送中！");
			}
		    else
			{										   	
				//printf("\n\r发送不成功，请检查接收端是否正常工作！");			    
		    }
			RX_Mode();						//发送完成后进入到接收模式
		}
		if(NRF24L01_RxPacket(tmp_buf) == 0)	//如果接收到按键值，则点亮相应的LED
		{
			LED_by_KEY(tmp_buf[0]);		 	//点亮LED
		}

//		//for key_test		
//		if(KEY_Pressed()){
//			LED1_ON;
//			delay_ms(500);
//			LED1_OFF;
//			delay_ms(500);	
//		}
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




