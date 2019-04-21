#include "delay.h"

//-----˽��ȫ�ֱ���-----//
static u8  g_fac_us = 0;         //us��ʱ����
static u16 g_fac_ms = 0;        //ms��ʱ����

/****************************************************
��������void Delay_Init(void)
˵�����ӳٳ�ʼ��
��ڣ���
���ڣ���
��ע��ʹ��SysTickʱ�ӽ����ӳ٣������ʹ��8MHz�ⲿ����
*****************************************************/
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //ѡ���ⲿʱ��HCLK/8
    g_fac_us = SystemCoreClock / 8000000;                                   //ʱ�ӵ�1/8  
    g_fac_ms = (u16)g_fac_us * 1000;                                            //�ӳ�����
}   


/****************************************************
��������void Delay_us(u32 nus)
˵����us�ӳ�
��ڣ�u32 nus  �����ӳٵ�us�����ΧΪ(2^24/fac_us)
���ڣ���
��ע��ʹ��SysTickʱ�ӽ����ӳ٣������ʹ��8MHz�ⲿ����
*****************************************************/ 
void Delay_us(u32 nus)
{       
    u32 temp;            
    SysTick->LOAD = nus * g_fac_us;  
    SysTick->VAL = 0x00;                                            //��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;    //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while (temp & 0x01 && !(temp & (1 << 16)));             //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;        //�رռ�����
    SysTick->VAL = 0x00;                                                        //��ռ�����
}

/**************************************************************
��������void Delay_ms(u16 nms)
˵����ms�ӳ�
��ڣu16 nms  �����ӳٵ�ms�����ΧΪ(0xffffff*8*1000/SYSCLK)
���ڣ���
��ע��8MHzʱ������ӳ�Ϊ1864ms
***************************************************************/ 
void Delay_ms(u16 nms)
{                 
    u32 temp;          
    SysTick->LOAD = (u32)nms*g_fac_ms;                              //ʱ����أ�SysTick->LOADΪ24bit
    SysTick->VAL = 0x00;                                                //��ռ�����
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
    do
    {
        temp=SysTick->CTRL;
    }
    while (temp & 0x01 && !(temp & (1 << 16)));             //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;              //�رռ�����
    SysTick->VAL = 0x00;                                                        //��ռ�����
} 





