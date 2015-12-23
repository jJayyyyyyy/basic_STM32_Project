/* 基于STM32F107VCT6的 USART, ADC+DMA
 * 版本 v0.2
 * by 楼基颉
 * MDK v4.22打开会乱码，需要npp之类的文本编辑器打开
*/

/*********************************************************/
1. STM32f107VCT6
		晶振25M
		通过分频器与倍频器，使系统时钟为72M		
	注：	STM32F10X_CL代表的是使用了
			STM32互联系列微处理器(芯片选型 STM32F10x Connectivity Line Flash, 256k)
			也就是STM32F105和STM32F107系列处理器	
		
2. 配置好了SysTick_Handler(), 1ms一次
		以此实现void delay_ms(__IO uint32_t nTime)，
		举例而言delay_ms(500); 便是延时500ms
	参考: stm32标准库(v3.5)
	
3.	GPIO 与相应时钟开启的格式参见 rcc_gpio.c

4.	按键参见key.c

5.	对开发板上LED操作
		LED1_ON;
		LED2_ON;
		...
		
		LED1_OFF;
		LED2_OFF;
		...
	详见led.c
	
6. TIM2 3 4是通用计时器。
		配置好了 TIM3 为 0.5s 一次中断
		配置好了 TIM2 为可以硬件模拟PWM控制小灯亮度
				可以用于输出给驱动，来控制电机，进而控制小车的运动
				已经由小灯证明PWM占空比可调(亮度可调)
				要输出给驱动，只需换<GPIO+RCC>, 并增加<控制逻辑+方便用户操作的接口(JoyStick)>
	详见 tim.c 以及 stm32f10x_it.c
/*********************************************************/	
	
	
7.USART
要看原理图! 要看原理图! 要看原理图! 重要的事说三遍，不要想当然
107这块开发板上的RS232使用的是PD5 PD6，是重映射之后的USART2。。简直坑爹。。。。
重新焊引脚
PA9 PA10，USART1，

下到板子后，总是卡在那里，把printf() 注释掉后能运行。
解决方法：
	如果使用的是MDK，请在工程属性的“Target“-》”Code Generation“中勾选”Use MicroLIB“
可以运行。

a.	首先进行RCC和GPIO的配置，注意USARTx设备所在总线。
	比如USART1在APB2上，USART2在APB1上，不要使能错了。
b.	然后USART_Configuration()，同样要注意配置你想要的USARTx，前后一致。
c.	
	//发送, 比如使用printf(), 需要增加以下代码
	int fputc(int ch,FILE *f){
		USART_SendData(USART1,(u8) ch);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		return ch;
	}

	//读取, 比如scanf(), 需要
	int fgetc(FILE *f){
	   while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)); 
	   return (USART_ReceiveData(USART1));
	}

	注释：
	fgetc 和 fgetc是c语言的标准函数（形参是标准的） FILE *f 是文件指针，具备文件系统的操作系统有用。对于简单的无文件系统的嵌入式系统无用

	以及在 <Options for Target> ---<Target>选项卡中的Code Generation一栏勾选<Use MicroLIB>，方可正确使用


8. 
有ADC的IO口也是固定的，不能随意指定。
a.	RCC+GPIO
b.	ADC_Configuration()
c.	ADC_GetConversionValue(ADC1), 得到的值是0~4096 (0x0fff)
	可以这样用
	float ADC_GetValue(float VREF){
		return (VREF * ADC_GetConversionValue(ADC1) / 0x0fff);
	}

9. TODO:	DMA与ADC结合

	
	
	
	
	
	
	
	
	
	
/*********************************************************/
附注：
1.
		设置读取FLASH时的等待周期	因为STM32内核一般工作在比较高的频率，比如72M，而FLASH工作在比较低的频率，比如24M，所以正常情况下STM32内核在读取FLASH时需要有几个等待周期
		标准库rcc中有
			#ifndef STM32F10X_CL
			/* Flash 0 wait state */
			FLASH_SetLatency(FLASH_Latency_0);
		
		根据标准库，对于CL，使用HSE 或24M时，延时0周期，36M或48M时延时1周期，
		56M或72M时延时2周期
		
		对比工程看看还需要加什么
			#include "stm32f10x_rcc.h"
			#include "stm32f10x_flash.h"
		
		高速外部时钟信号HSE(High Speed External Clock signal)
		PLL为锁相环倍频输出，其时钟输入源可选择为HSI/2、HSE或者HSE/2。倍频可选择为2~16倍，但是其输出频率最大不得超过72MHz。
		
		把时钟都设成72M，这样方便移植
		否则参照标准库的SysTick，RCC，以及由SysTick的
			if (SysTick_Config(SystemCoreClock / 1000))
		进行一步步往下查找，并修改RCC_Configuration()，包括
				RCC_PCLK1Config(RCC_HCLK_Div2);
				FLASH_SetLatency(FLASH_Latency_0);
				while(RCC_GetSYSCLKSource() != 0x04){};
				etc...				
2.
		USART串口
			USART:(Universal Synchronous/Asynchronous Receiver/Transmitter) 通用同步/异步串行接收/发送器
		
			串口使用只需要开始串口时钟，设置相应的I/O口模式，
			配置波特率、数据位长度、奇偶校验位等信息就可以使用了。
					

