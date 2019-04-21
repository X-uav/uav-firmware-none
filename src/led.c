#include "led.h"

/*************************************
��������void GPIO_Configuration(void)
˵����GPIO����
��ڣ���
���ڣ���
��ע����
	 - led 2/3 (PA8) �޷�����
	 - led 7/8 (PB3) �޷�����
*************************************/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //EXTI_InitTypeDef EXTI_InitStructure;		// ����EXTI�ṹ��

    //-----SPI1ʱ��ʹ��-----//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	//-----TIM3ʱ��-----//
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//-----TIM2ʱ��-----//
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//-----USART1ʱ��-----//
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    //******LED******//
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOA,  &GPIO_InitStructure); 
    GPIO_ResetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOB,  &GPIO_InitStructure); 
    GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3);

    //******BT******//
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  /* �������*/
    GPIO_Init(GPIOB,  &GPIO_InitStructure); 
    GPIO_ResetBits(GPIOB,GPIO_Pin_2);

    //******IIC******//
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;// PA11,12-->IIC
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;// �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 50MHz��תƵ��
    GPIO_Init(GPIOB, &GPIO_InitStructure);// ��ʼ��IO

    //******PWM******//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;										// �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz��תƵ��
	GPIO_Init(GPIOA, &GPIO_InitStructure);												// ��ʼ��IO
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);

    //******USART1******//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;											// PA9����Ϊ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;										// ����Ϊ�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;											// PA10����Ϊ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;								// ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-----NRF24L01-----//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_4;							// PA12,4-->NRF_CE,NRF_CSN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz��תƵ��
	GPIO_Init(GPIOA, &GPIO_InitStructure);												// ��ʼ��IO
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;   										// PA15-->NRF_IRQ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz��תƵ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 										// ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-----SPI1-----//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;				// PA5-->SCK,PA6-->MISO,PA7-->MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  									// PA5/6/7�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-----�ж��¼�������-----//
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);						// ���¼��ߺ�Pin��������	
	//EXTI_InitStructure.EXTI_Line = EXTI_Line15;											// EXTI���жϿ�ͨ
	//EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;									// ����Ϊ�жϻ����¼�
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;								// �½��ش���
	//EXTI_InitStructure.EXTI_LineCmd = ENABLE;											// ʹ��EXTI���ж�
	//EXTI_Init(&EXTI_InitStructure);
}

void LED_Front_Off(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3);
}

void LED_Front_ON(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3);
}

void LED_Tail_Off(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);
}

void LED_Tail_ON(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);
}

