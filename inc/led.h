#ifndef __LED_H
#define __LED_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"


void GPIO_Configuration(void);
void LED_Front_Off(void);
void LED_Front_ON(void);
void LED_Tail_Off(void);
void LED_Tail_ON(void);


#endif
