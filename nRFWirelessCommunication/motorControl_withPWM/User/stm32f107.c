#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "NRF24l01.h"
#include "stm32f107.h"

void NVIC_Configuration(void)
{/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
	NVIC_InitTypeDef NVIC_InitStructure;

	//CAN1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//CAN2
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

/*******************************************************************************
* Function Name  : GPIO_Configuration_for_CAN
*******************************************************************************/

void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);
  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap2_CAN1,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_CAN2,ENABLE);
  
	/* Configure CAN1 pin: RX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);  
  
 
	/* Configure CAN1 pin: TX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
		/* Configure CAN2 pin: RX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
		/* Configure CAN2 pin: TX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	    
 
	//led �ܽ�			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


/***********************************************************************
�������ƣ�TIM_Configuration(unsigned int time)
��    �ܣ���ʱ��2����
���������time����ʱʱ�䣬��λms��
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void TIM_Configuration(unsigned int time)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  TIM_DeInit(TIM2);
  TIM_TimeBaseStructure.TIM_Period=time;		 					/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
																	/* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
  TIM_TimeBaseStructure.TIM_Prescaler= (36000 - 1);				    /* ʱ��Ԥ��Ƶ��   ���磺ʱ��Ƶ��=72MHZ/(ʱ��Ԥ��Ƶ+1) */
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			/* ������Ƶ */
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		/* ���ϼ���ģʽ */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    /* �������жϱ�־ */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM2, ENABLE);											/* ����ʱ�� */
}


/***********************************************************************
�������ƣ�TIM2_IRQHandler(void)
��    �ܣ���ʱ��2�жϺ���
���������ÿ��	time��ms���ж�һ��
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void TIM2_IRQHandler(void)
{

}

void System_Setup(void)
{
     //RCC_ClocksTypeDef RCC_Clocks;

  /* Setup STM32 clock, PLL and Flash configuration) */
     SystemInit();
}
