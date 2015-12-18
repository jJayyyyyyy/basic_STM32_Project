#ifndef __STM32F107_H
#define __STM32F107_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32_eval.h"
#include "stm3210c_eval_lcd.h"
#include "stm3210c_eval_ioe.h"


void System_Setup(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void CAN_Configuration(void);
void Can1_WriteData(unsigned int ID, unsigned char *txbuf);
void One_LED_ON(unsigned char led_num);
void delay_ms(u16 nms);

//void One_LED_ON(unsigned char led_num);
//void delay_ms(u16 nms);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10F107_H */


