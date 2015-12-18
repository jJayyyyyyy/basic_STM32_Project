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

//用于输出给电机(驱动)
#define PWM_Ch1	GPIO_Pin_8
#define PWM_Ch2	GPIO_Pin_10
#define PWM_Ch3	GPIO_Pin_12
#define PWM_Ch4	GPIO_Pin_14
#define PWM_OUT	GPIOE


//#define SPI1_SCK	GPIO_Pin_5
//#define SPI1_MISO	GPIO_Pin_6
//#define SPI1_MOSI	GPIO_Pin_7
//#define SPI1_GPIO	GPIOA
//
//#define SPI2_SCK	GPIO_Pin_13
//#define SPI2_MISO	GPIO_Pin_14
//#define SPI2_MOSI	GPIO_Pin_15
//#define SPI2_GPIO	GPIOB

#define SPI3_SCK	GPIO_Pin_10
#define SPI3_MISO	GPIO_Pin_11
#define SPI3_MOSI	GPIO_Pin_12

void RCC_Configuration(void);
void GPIO_Configuration(void);
