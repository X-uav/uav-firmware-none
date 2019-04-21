#ifndef __BT_H
#define __BT_H

#include "stm32f10x_gpio.h"

#define BT_on()      {GPIO_SetBits(GPIOB, GPIO_Pin_2);}
#define BT_off()     {GPIO_ResetBits(GPIOB, GPIO_Pin_2);}//宏定义蓝牙开关

#define CmdreturnLength 20

#define BThavewrote        0xa5
#define BTneedwrite        0x5a

#define BT_NAMEmax  10
#define BT_PINmax   10

typedef struct
{
    u8 Name[BT_NAMEmax];
    u32 Baud;
    u8 PinCode[BT_PINmax];
}BTtype;

void BT_PowerInit(void);   //蓝牙透传电源初始化


#endif
