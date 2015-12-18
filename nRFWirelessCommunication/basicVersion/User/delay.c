/* 参考stm32标准库V3.5的xxx，利用SysTick进行延时函数的设计
*/
#include "stm32f10x.h"
#include "delay.h"

//TODO:
//什么是__IO型变量？
static __IO uint32_t TimingDelay=0;

void delay_ms(__IO uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void delay_decrement(void){
	if(TimingDelay != 0x00){
		TimingDelay--;
	}
}
