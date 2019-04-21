#include "usart.h"
#include <errno.h>
#include <sys/unistd.h>



/*************************************
��������void USART_Configuration(void)
˵����USART��ʼ��
��ڣ���
���ڣ���
��ע����
*************************************/
void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = BAUD;											// ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							// ���ݳ��ȣ��������żУ�飬���ֳ�����Ϊ9bits���μ�stm32f10x_usart.h Line63
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								// ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;									// ��żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						// ����/����ģʽ
	USART_Init(USART1, &USART_InitStructure);											// ��ʼ��USARTx
	
	//USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); 										// ʹ�ܴ���1��DMA���� 
	USART_Cmd(USART1, ENABLE);															// ʹ��USARTx
}

/*********************************
��������void Uartx_PutChar(u8 ch)
˵��������1�����ַ�
��ڣ�u8 ch  ��Ҫ���͵��ַ�
���ڣ���
��ע����
*********************************/
//void Uart1_PutChar(const u8 ch)
void Uart1_PutChar(u8 ch)

{
   USART_SendData(USART1, (u8)ch);
   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**********************************************
��������void Uartx_PutString(u8 * buf, u8 len)
˵��������x�����ַ���
��ڣ�u8* buf  �ַ�������
			u8 len �ַ�����
���ڣ���
��ע����
*********************************************/
//void Uart1_PutString(const u8 * buf, const u8 len)
void Uart1_PutString(u8 * buf, const u8 len)

{   
	u8 i;
	
	for(i = 0; i < len; i++)
		Uart1_PutChar(*buf++);
}


u8 USART_GetChar(void)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (u8)USART_ReceiveData(USART1);
}

int _read(int file, char *ptr, int len)
{
    int i;
    int num = 0;
    char ch;

    switch (file)
    {
        case STDIN_FILENO:
        {
            for (i = 0; i < len; i++)
            {
                ch = USART_GetChar();
                *ptr++ = ch;
                num++;
            }
            break;
        }
        default:
        {
            errno = EBADF;
            return -1;
        }
    }

    return num;
}

int _write(int file, char *ptr, int len)
{
    int i;

    switch (file)
    {
        case STDOUT_FILENO:
        {
            for (i = 0; i < len; i++)
            {
                Uart1_PutChar(*ptr++ & (u16)0x01FF);
            }
            break;
        }
        case STDERR_FILENO:
        {
            for (i = 0; i < len; i++)
            {
                Uart1_PutChar(*ptr++ & (u16)0x01FF);
            }
            break;
        }
        default:
        {
            errno = EBADF;
            return -1;
        }
    }

    return len;
}
