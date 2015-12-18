//用于输出给电机(驱动)
#define PWM_Ch1	GPIO_Pin_8
#define PWM_Ch2	GPIO_Pin_10
#define PWM_Ch3	GPIO_Pin_12
#define PWM_Ch4	GPIO_Pin_14
#define PWM_OUT	GPIOE

#define PWM_IN1_ON	GPIO_WriteBit(PWM_OUT, PWM_Ch1, (BitAction)(1 - GPIO_ReadOutputDataBit(PWM_OUT, PWM_Ch1)))
#define PWM_IN2_ON	GPIO_WriteBit(PWM_OUT, PWM_Ch2, (BitAction)(1 - GPIO_ReadOutputDataBit(PWM_OUT, PWM_Ch2)))
#define PWM_IN3_ON	GPIO_WriteBit(PWM_OUT, PWM_Ch3, (BitAction)(1 - GPIO_ReadOutputDataBit(PWM_OUT, PWM_Ch3)))
#define PWM_IN4_ON	GPIO_WriteBit(PWM_OUT, PWM_Ch4, (BitAction)(1 - GPIO_ReadOutputDataBit(PWM_OUT, PWM_Ch4)))

#define PWM_IN1_OFF	GPIO_ResetBits(PWM_OUT , PWM_Ch1)
#define PWM_IN2_OFF	GPIO_ResetBits(PWM_OUT , PWM_Ch2)
#define PWM_IN3_OFF	GPIO_ResetBits(PWM_OUT , PWM_Ch3)
#define PWM_IN4_OFF	GPIO_ResetBits(PWM_OUT , PWM_Ch4)


void pwmOutput(void);
void forward(void);
void backward(void);
void stopMov(void);
