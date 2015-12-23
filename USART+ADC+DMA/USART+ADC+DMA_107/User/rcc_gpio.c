#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "rcc_gpio.h"

//����GPIO
void GPIO_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	//LED, PE2 PE3 PE4 PE5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//LED��PP,�������
	GPIO_Init(LED_OUT, &GPIO_InitStructure);

	//KEY, PC6 PC7 PC8 PC9 
	GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2 | KEY3 | KEY4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY_IN, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//ADC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


//����ϵͳʱ��
void RCC_Configuration(void){
	//����ö�����ͱ���
	ErrorStatus	HSEStartUpStatus;
	
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------*/   
  	/* RCC system reset(for debug purpose) */
	//��λϵͳʱ������
	RCC_DeInit();  
	
	/* Enable HSE */
	//����HSEʱ��
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* Wait till HSE is ready */
	//�ȴ�HSE�����ȶ�
	HSEStartUpStatus=RCC_WaitForHSEStartUp();

	//�ж�HSE�Ƿ�����ɹ�
	if(HSEStartUpStatus == SUCCESS){
		/* Enable Prefetch Buffer */
		//ʹ��Ԥȡ����
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		/* Flash 2 wait state */
		//����flash��ʱ������Ϊ2
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK */
		//HCLK(AHB)ʱ��ԴΪSYSCLK, HSE	1��Ƶ
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* PCLK2 = HCLK */
		//PCLK2ʱ��ԴΪHCLK(AHB)	1��Ƶ
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* PCLK1 = HCLK/2 */
		//PCLK1ʱ��ԴΪHCLK(AHB)	1��Ƶ
		RCC_PCLK1Config(RCC_HCLK_Div1);

	    /* Configure PLLs ***********************/
	    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
		//clоƬ��Ĭ���ⲿʱ����25M
	    //PLL2ʱ��ԴΪHSE, Ԥ��Ƶ��Ϊ5����Ƶ��Ϊ8
		//��PLL2���Ƶ��Ϊ25M/5 * 8 = 40M
		RCC_PREDIV2Config(RCC_PREDIV2_Div5);
		//��PLL2����8��Ƶ
	    RCC_PLL2Config(RCC_PLL2Mul_8);
	
	    /* Enable PLL2 */
		//ʹ��PLL2
	    RCC_PLL2Cmd(ENABLE);
	
	    /* Wait till PLL2 is ready */
		//�ȴ�PLL2����ȶ�
	    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
	    {}
	
	    /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
	    //��PLL2����5��Ԥ��Ƶ
		RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
	    //����PLL����9��Ƶ
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
		
		/* Enable PLL */
		//ʹ��PLL 
	    RCC_PLLCmd(ENABLE);
	
	    /* Wait till PLL is ready */
	    //�ȴ�PLL����ȶ�
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
	    }
	
	    /* Select PLL as system clock source */
		//ѡ��PLLΪϵͳʱ��Դ
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	    /* Wait till PLL is used as system clock source */
		//�ȴ�PLL׼����
	    while(RCC_GetSYSCLKSource() != 0x08)
	    {
	    }
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
}
