#include "bt.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"


void BT_PowerInit(void)
{
    BT_on();
}

char Cmdreturn[CmdreturnLength];//ָ��ķ��ؽ������

#if 0

/********************************************
              ������д��һ��ָ���
********************************************/
void Uart1SendaBTCmd(const char *p)
{
  char i;
	
  for(i=0;i<CmdreturnLength;i++) 
    Cmdreturn[i] = 0;//�ͷ�ָ����ջ���
    
  Delay_ms(100);//д��һ��ָ���ʱ500ms�ٶȽ��ջ���
  
  for(i=0;i<strlen(p);i++) 
    Uart1_PutChar(*(p+i));  
  
  Delay_ms(100);//д��һ��ָ���ʱ500ms�ٶȽ��ջ���
		
  i=0;
  while(UartBuf_Cnt(&UartRxbuf) != 0)     //�����ڻ��岻Ϊ��ʱ�������ڻ��帳ֵ��ָ��������
    Cmdreturn[i++] = UartBuf_RD(&UartRxbuf);
}
#endif

