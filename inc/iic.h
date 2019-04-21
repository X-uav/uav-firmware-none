#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

//-----IIC方向设置-----//
#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}	// 可以修改为输入模式,上下拉均可
#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}	// 可以修改为50MHZ推挽输出，但是用寄存器的方式速度更快

//-----IIC操作函数-----// 
#define IIC_SCL_H    GPIO_SetBits(GPIOB, GPIO_Pin_6) // SCL_H
#define IIC_SCL_L    GPIO_ResetBits(GPIOB, GPIO_Pin_6)// SCL_L
#define IIC_SDA_H    GPIO_SetBits(GPIOB, GPIO_Pin_7) // SDA_H
#define IIC_SDA_L    GPIO_ResetBits(GPIOB, GPIO_Pin_7) // SDA_L 
#define READ_SDA    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)  // 输入SDA

//-----IIC所有操作函数-----//
void IIC_Init(void);			// 初始化IIC的IO口				 
void IIC_Start(void);			// 发送IIC开始信号
void IIC_Stop(void);	  		// 发送IIC停止信号
void IIC_Send_Byte(u8 txd);		// IIC发送一个字节
u8 IIC_Read_Byte(u8 ack);		// IIC读取一个字节
u8 IIC_Wait_Ack(void); 			// IIC等待ACK信号
void IIC_Ack(void);				// IIC发送ACK信号
void IIC_NAck(void);			// IIC不发送ACK信号

#endif
