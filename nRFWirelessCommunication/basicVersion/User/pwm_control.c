#include "stm32f10x.h"
#include "pwm_control.h"

void forward(){
			//left
			IN1=1;//+ռ�ձ�duty_cycle=40;
			IN2=0;
			//right
			IN3=1;//+ռ�ձ�=40;
			IN4=0;
}
		
void backward(){	
			//left
			IN1=0;
			IN2=1;//+ռ�ձ�=20;	//������
			//right
			IN3=0;
			IN4=1;//+ռ�ձ�=20;
}
		
void leftforward(){
			//left
			IN1=0;
			IN2=0;
			//right
			IN3=1;//+ռ�ձ�=40;
			IN4=0;
}
		
void rightforward(){
			//left
			IN1=1;//+ռ�ձ�=40;
			IN2=0;
			//right
			IN3=0;
			IN4=0;
}
		
void leftbackward()
void rightbackward()
