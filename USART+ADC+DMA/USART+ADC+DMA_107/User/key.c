#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

char KEY_Pressed(void){
	if(KEY1_is_Pressed){
		delay_ms(100);
		if(KEY1_is_Pressed) 
			return KEY1_VALUE;

	}else if(KEY2_is_Pressed){
		delay_ms(100);
		if(KEY2_is_Pressed)
			return KEY2_VALUE;

	}else if(KEY3_is_Pressed){
		delay_ms(100);
		if(KEY3_is_Pressed)
			return KEY3_VALUE;

	}else if(KEY4_is_Pressed){
		delay_ms(100);
		if(KEY4_is_Pressed)
			return KEY4_VALUE;

	}		
	return 0;
}
