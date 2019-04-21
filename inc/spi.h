#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"


void SPI_Configuration(void);		// ��ʼ��SPI��
u8 SPI_ReadWriteByte(u8 txData);	// SPI���߶�дһ���ֽ�

#endif
