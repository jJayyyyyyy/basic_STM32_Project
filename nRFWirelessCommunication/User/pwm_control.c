#include "stm32f10x.h"
#include "pwm_control.h"

void forward(){
			//left
			IN1=1;//+占空比duty_cycle=40;
			IN2=0;
			//right
			IN3=1;//+占空比=40;
			IN4=0;
}
		
void backward(){	
			//left
			IN1=0;
			IN2=1;//+占空比=20;	//慢慢退
			//right
			IN3=0;
			IN4=1;//+占空比=20;
}
		
void leftforward(){
			//left
			IN1=0;
			IN2=0;
			//right
			IN3=1;//+占空比=40;
			IN4=0;
}
		
void rightforward(){
			//left
			IN1=1;//+占空比=40;
			IN2=0;
			//right
			IN3=0;
			IN4=0;
}
		
void leftbackward()
void rightbackward()
