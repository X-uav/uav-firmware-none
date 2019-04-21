#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

//-----USART����-----//
#define BAUD 115200

#if 1
//-----���ͺͻ�����Size�趨�궨��-----//
#define TxBufferSize   10
#define RxBufferSize   TxBufferSize

extern __IO uint8_t TxCounter;				// ���ͼ�����
extern __IO uint8_t RxCounter;				// ���ռ�����
extern uint8_t TxBuffer[TxBufferSize];		// ���ͻ�����
extern uint8_t RxBuffer[RxBufferSize];		// ���ջ�����
#endif
//-----����-----//
extern void USART_Configuration(void);

//extern void Uart1_PutChar(const u8 ch);						// ����1�����ַ�
//extern void Uart1_PutString(const u8 * buf, const u8 len);	// ����1�����ַ���

void Uart1_PutChar(u8 ch);						// ����1�����ַ�
void Uart1_PutString(u8 * buf, const u8 len);	// ����1�����ַ���

extern u8 USART_GetChar(void);
extern int _read(int file, char *ptr, int len);
extern int _write(int file, char *ptr, int len);

#endif
