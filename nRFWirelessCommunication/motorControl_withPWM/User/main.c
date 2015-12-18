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
	while(NRF24L01_Check())			//24L01���߼��
    {
        LED4_ON;
		//printf("û�м�⵽NRF24L01����ȷ��NRF24L01�Ƿ������ϣ�\n\r");
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
		keyValue[0] = KEY_Pressed(); 					//��ȡ����ֵ
		if(keyValue[0]){								//����м����£�����뵽����ģʽ��������ֵ���ͳ�ȥ		
			TX_Mode();	  								//����ģʽ
			if(NRF24L01_TxPacket(keyValue) == TX_OK){	//������ͳɹ�			
				//printf("\n\r�����ڷ����У�");
			}
		    else{
				//printf("\n\r���Ͳ��ɹ���������ն��Ƿ�����������");			    
		    }
			RX_Mode();									//������ɺ���뵽����ģʽ
		}
		if(NRF24L01_RxPacket(keyValue) == 0){			//������յ�����ֵ���������Ӧ��LED
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




