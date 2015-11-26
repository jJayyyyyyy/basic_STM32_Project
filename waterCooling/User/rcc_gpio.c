#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "rcc_gpio.h"

//��������RCC��GPIO

//����ϵͳʱ��
void RCC_Configuration(void){
	//����ö�����ͱ���
	ErrorStatus	HSEStartUpStatus;
	
	//��λϵͳʱ������
	RCC_DeInit();  
	
	//����HSEʱ��
	RCC_HSEConfig(RCC_HSE_ON);
	//�ȴ�HSE�����ȶ�
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	//�ж�HSE�Ƿ�����ɹ�
	if(HSEStartUpStatus == SUCCESS){
		//ѡ��HCLK(AHB)ʱ��ԴΪSYSCLK	1��Ƶ
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//ѡ��PCLK2ʱ��ԴΪHCLK(AHB)	1��Ƶ
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//ѡ��PCLK1ʱ��ԴΪHCLK(AHB)	2��Ƶ
		RCC_PCLK1Config(RCC_HCLK_Div2);
		
		//����flash��ʱ������Ϊ2
		FLASH_SetLatency(FLASH_Latency_2);
		//ʹ��Ԥȡ����
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		//ѡ�����໷��PLLʱ��ԴΪHSE 1��Ƶ����Ƶ��Ϊ9����PLL���Ƶ��Ϊ8M * 9 = 72M��
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		//ʹ��PLL
		RCC_PLLCmd(ENABLE);
		//�ȴ�PLL����ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){};

		//ѡ��PLLΪϵͳʱ��Դ�����ȴ�PLL׼����
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08){};
	}
	//4��LED��ӦPE2 PE3 PE4 PE5
	//���Ҫʹ��APB2�����ϵ�GPIOEʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
}

void GPIO_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//LED��PP,�������
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
