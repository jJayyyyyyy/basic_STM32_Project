#include "stm32f10x.h"
#include "pwm_control.h"

extern __IO uint16_t Increment_High;
extern __IO uint16_t Increment_Low;

static __IO uint16_t directionLeft=0;
static __IO uint16_t directionRight=0;

void pwmOutput(void){	
//	switch(directionLeft){
//		case 1:
//			//ǰ��
//			break;
//		case 2:
//			//����
//			break;
//		case 3:
//			//��ת
//			break;
//		case 4:
//			//��ת
//			break;
//		default:
//			break;	
//	}	
	if(directionLeft == 1){
		//forward
		PWM_IN1_ON;
		PWM_IN2_OFF;
	}else if(directionLeft == 2){
		//backward
		PWM_IN2_ON;
		PWM_IN1_OFF;				
	}else if(directionLeft == 0){
		PWM_IN1_OFF;
		PWM_IN2_OFF;
	}

	if(directionRight == 1){
		//forward
		PWM_IN3_ON;
		PWM_IN4_OFF;				
	}else if(directionRight == 2){
		//backward
		PWM_IN4_ON;
		PWM_IN3_OFF;
	}else if(directionRight == 0){
		PWM_IN3_OFF;
		PWM_IN4_OFF;
	}
}

void forward(void){
	//ռ�ձ��ȵ����̶���
	Increment_High = 40;
	Increment_Low = 60;
	//����ֻ���趨�����߼��������ٶȴ�С
	directionLeft=1;
	directionRight=1;
	
//			//left
//			PWM_IN1_ON;//+ռ�ձ�duty_cycle=40;
//			PWM_IN2_OFF;
			//right
//			PWM_IN3=1;//+ռ�ձ�=40;
//			PWM_IN4=0;
}
		
void backward(void){
	Increment_High = 40;
	Increment_Low = 60;
	directionLeft=2;
	directionRight=2;
}

void stopMov(void){
	Increment_High = 2;
	Increment_Low = 98;
	directionLeft=0;
	directionRight=0;
}
		
//void leftforward(){
//			//left
//			IN1=0;
//			IN2=0;
//			//right
//			IN3=1;//+ռ�ձ�=40;
//			IN4=0;
//}
//		
//void rightforward(){
//			//left
//			IN1=1;//+ռ�ձ�=40;
//			IN2=0;
//			//right
//			IN3=0;
//			IN4=0;
//}
//		
//void leftbackward()
//void rightbackward()
