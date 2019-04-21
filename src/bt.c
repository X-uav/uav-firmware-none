#include "bt.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"


void BT_PowerInit(void)
{
    BT_on();
}

char Cmdreturn[CmdreturnLength];//指令的返回结果缓存

#if 0

/********************************************
              往蓝牙写入一个指令包
********************************************/
void Uart1SendaBTCmd(const char *p)
{
  char i;
	
  for(i=0;i<CmdreturnLength;i++) 
    Cmdreturn[i] = 0;//释放指令接收缓存
    
  Delay_ms(100);//写完一条指令，延时500ms再度接收缓存
  
  for(i=0;i<strlen(p);i++) 
    Uart1_PutChar(*(p+i));  
  
  Delay_ms(100);//写完一条指令，延时500ms再度接收缓存
		
  i=0;
  while(UartBuf_Cnt(&UartRxbuf) != 0)     //当串口缓冲不为空时，将串口缓冲赋值给指令结果缓冲
    Cmdreturn[i++] = UartBuf_RD(&UartRxbuf);
}
#endif

