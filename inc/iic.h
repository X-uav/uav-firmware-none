#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

//-----IIC��������-----//
#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}	// �����޸�Ϊ����ģʽ,����������
#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}	// �����޸�Ϊ50MHZ��������������üĴ����ķ�ʽ�ٶȸ���

//-----IIC��������-----// 
#define IIC_SCL_H    GPIO_SetBits(GPIOB, GPIO_Pin_6) // SCL_H
#define IIC_SCL_L    GPIO_ResetBits(GPIOB, GPIO_Pin_6)// SCL_L
#define IIC_SDA_H    GPIO_SetBits(GPIOB, GPIO_Pin_7) // SDA_H
#define IIC_SDA_L    GPIO_ResetBits(GPIOB, GPIO_Pin_7) // SDA_L 
#define READ_SDA    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)  // ����SDA

//-----IIC���в�������-----//
void IIC_Init(void);			// ��ʼ��IIC��IO��				 
void IIC_Start(void);			// ����IIC��ʼ�ź�
void IIC_Stop(void);	  		// ����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);		// IIC����һ���ֽ�
u8 IIC_Read_Byte(u8 ack);		// IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 			// IIC�ȴ�ACK�ź�
void IIC_Ack(void);				// IIC����ACK�ź�
void IIC_NAck(void);			// IIC������ACK�ź�

#endif
