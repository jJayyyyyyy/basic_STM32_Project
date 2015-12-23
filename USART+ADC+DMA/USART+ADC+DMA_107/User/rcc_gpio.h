#define LED1	GPIO_Pin_2
#define LED2	GPIO_Pin_3
#define LED3	GPIO_Pin_4
#define LED4	GPIO_Pin_5
#define LED_OUT	GPIOE

#define KEY1	GPIO_Pin_6
#define KEY2	GPIO_Pin_7
#define KEY3	GPIO_Pin_8
#define KEY4	GPIO_Pin_9
#define KEY_IN	GPIOC

//PB1 ---> ADC12_IN9
#define ADC_IN9	GPIO_Pin_1
#define ADC_12	GPIOB


//#define PWM_OUT	GPIOB
//用于输出给电机

void RCC_Configuration(void);
void GPIO_Configuration(void);
