#define KEY1_is_Pressed	!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)
#define KEY2_is_Pressed	!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)
#define KEY3_is_Pressed	!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)
#define KEY4_is_Pressed	!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)

#define KEY1_VALUE	1
#define KEY2_VALUE	2
#define KEY3_VALUE	3
#define KEY4_VALUE	'4'

char KEY_Pressed(void);

