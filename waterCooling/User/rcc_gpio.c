#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "rcc_gpio.h"

//自行配置RCC和GPIO

//配置系统时钟
void RCC_Configuration(void){
	//定义枚举类型变量
	ErrorStatus	HSEStartUpStatus;
	
	//复位系统时钟设置
	RCC_DeInit();  
	
	//开启HSE时钟
	RCC_HSEConfig(RCC_HSE_ON);
	//等待HSE起振并稳定
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	//判断HSE是否起振成功
	if(HSEStartUpStatus == SUCCESS){
		//选择HCLK(AHB)时钟源为SYSCLK	1分频
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//选择PCLK2时钟源为HCLK(AHB)	1分频
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//选择PCLK1时钟源为HCLK(AHB)	2分频
		RCC_PCLK1Config(RCC_HCLK_Div2);
		
		//设置flash延时周期数为2
		FLASH_SetLatency(FLASH_Latency_2);
		//使能预取缓冲
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		//选择锁相环（PLL时钟源为HSE 1分频，倍频数为9，则PLL输出频率为8M * 9 = 72M）
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		//使能PLL
		RCC_PLLCmd(ENABLE);
		//等待PLL输出稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){};

		//选择PLL为系统时钟源，并等待PLL准备好
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08){};
	}
	//4个LED对应PE2 PE3 PE4 PE5
	//因此要使能APB2总线上的GPIOE时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
}

void GPIO_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//LED用PP,推挽输出
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
