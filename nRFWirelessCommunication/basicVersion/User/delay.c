/* �ο�stm32��׼��V3.5��xxx������SysTick������ʱ���������
*/
#include "stm32f10x.h"
#include "delay.h"

//TODO:
//ʲô��__IO�ͱ�����
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
