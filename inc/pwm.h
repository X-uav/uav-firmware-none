#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"


//--- 最大PWM值 ---
//#define MAX_PWM 2000
#define MAX_PWM 999


//-----//
extern u8  loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
extern volatile u16 loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt;



//-----函数声明-----//
extern void PWM_Set(const u16 pwm1,const u16 pwm2,const u16 pwm3,const u16 pwm4);	// PWM设置
extern void TIMx_Configuration(void);

#endif
