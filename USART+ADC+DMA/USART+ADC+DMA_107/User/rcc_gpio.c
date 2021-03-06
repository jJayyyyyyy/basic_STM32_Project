#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "rcc_gpio.h"

//配置GPIO
void GPIO_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	//LED, PE2 PE3 PE4 PE5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//LED用PP,推挽输出
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


//配置系统时钟
void RCC_Configuration(void){
	//定义枚举类型变量
	ErrorStatus	HSEStartUpStatus;
	
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------*/   
  	/* RCC system reset(for debug purpose) */
	//复位系统时钟设置
	RCC_DeInit();  
	
	/* Enable HSE */
	//开启HSE时钟
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* Wait till HSE is ready */
	//等待HSE起振并稳定
	HSEStartUpStatus=RCC_WaitForHSEStartUp();

	//判断HSE是否起振成功
	if(HSEStartUpStatus == SUCCESS){
		/* Enable Prefetch Buffer */
		//使能预取缓冲
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		/* Flash 2 wait state */
		//设置flash延时周期数为2
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK */
		//HCLK(AHB)时钟源为SYSCLK, HSE	1分频
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* PCLK2 = HCLK */
		//PCLK2时钟源为HCLK(AHB)	1分频
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* PCLK1 = HCLK/2 */
		//PCLK1时钟源为HCLK(AHB)	1分频
		RCC_PCLK1Config(RCC_HCLK_Div1);

	    /* Configure PLLs ***********************/
	    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
		//cl芯片，默认外部时钟是25M
	    //PLL2时钟源为HSE, 预分频数为5，倍频数为8
		//则PLL2输出频率为25M/5 * 8 = 40M
		RCC_PREDIV2Config(RCC_PREDIV2_Div5);
		//由PLL2进行8倍频
	    RCC_PLL2Config(RCC_PLL2Mul_8);
	
	    /* Enable PLL2 */
		//使能PLL2
	    RCC_PLL2Cmd(ENABLE);
	
	    /* Wait till PLL2 is ready */
		//等待PLL2输出稳定
	    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
	    {}
	
	    /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
	    //对PLL2进行5倍预分频
		RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
	    //再用PLL进行9倍频
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
		
		/* Enable PLL */
		//使能PLL 
	    RCC_PLLCmd(ENABLE);
	
	    /* Wait till PLL is ready */
	    //等待PLL输出稳定
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
	    }
	
	    /* Select PLL as system clock source */
		//选择PLL为系统时钟源
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	    /* Wait till PLL is used as system clock source */
		//等待PLL准备好
	    while(RCC_GetSYSCLKSource() != 0x08)
	    {
	    }
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
}
