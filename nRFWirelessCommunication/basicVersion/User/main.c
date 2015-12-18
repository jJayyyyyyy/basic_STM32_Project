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

	while(NRF24L01_Check())			//24L01���߼��
    {
        LED4_ON;
		//printf("û�м�⵽NRF24L01����ȷ��NRF24L01�Ƿ������ϣ�\n\r");
		delay_ms(700);
		LED4_OFF;
		delay_ms(500);
	}
/*****Ϩ���ĸ�led��******/
	LED1_OFF;
	LED2_OFF;
	LED3_ON;
	LED4_OFF;
	RX_Mode();

	while(1){
		
		tmp_buf[0] = KEY_Pressed(); 			//��ȡ����ֵ
		if(tmp_buf[0])						//����м����£�����뵽����ģʽ��������ֵ���ͳ�ȥ
		{
			TX_Mode();	  					//����ģʽ
			if(NRF24L01_TxPacket(tmp_buf) == TX_OK)	//������ͳɹ�
			{
		    	//printf("\n\r�����ڷ����У�");
			}
		    else
			{										   	
				//printf("\n\r���Ͳ��ɹ���������ն��Ƿ�����������");			    
		    }
			RX_Mode();						//������ɺ���뵽����ģʽ
		}
		if(NRF24L01_RxPacket(tmp_buf) == 0)	//������յ�����ֵ���������Ӧ��LED
		{
			LED_by_KEY(tmp_buf[0]);		 	//����LED
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




