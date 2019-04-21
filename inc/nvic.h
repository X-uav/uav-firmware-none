#ifndef __NVIC_H
#define __NVIC_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "nrf24l01.h"
#include "misc.h"

#include "led.h"
#include "delay.h"


extern void NVIC_Configuration(void);
#endif
