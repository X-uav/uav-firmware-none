#include "led.h"

/*************************************
函数名：void GPIO_Configuration(void)
说明：GPIO配置
入口：无
出口：无
备注：无
	 - led 2/3 (PA8) 无法点亮
	 - led 7/8 (PB3) 无法点亮
*************************************/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //EXTI_InitTypeDef EXTI_InitStructure;		// 定义EXTI结构体

    //-----SPI1时钟使能-----//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	//-----TIM3时钟-----//
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//-----TIM2时钟-----//
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//-----USART1时钟-----//
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  /* 推挽输出*/
    GPIO_Init(GPIOB,  &GPIO_InitStructure); 
    GPIO_ResetBits(GPIOB,GPIO_Pin_2);

    //******IIC******//
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;// PA11,12-->IIC
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;// 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 50MHz翻转频率
    GPIO_Init(GPIOB, &GPIO_InitStructure);// 初始化IO

    //******PWM******//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;										// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz翻转频率
	GPIO_Init(GPIOA, &GPIO_InitStructure);												// 初始化IO
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);

    //******USART1******//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;											// PA9复用为发送
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;										// 复用为推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;											// PA10复用为接收
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;								// 浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-----NRF24L01-----//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_4;							// PA12,4-->NRF_CE,NRF_CSN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz翻转频率
	GPIO_Init(GPIOA, &GPIO_InitStructure);												// 初始化IO
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;   										// PA15-->NRF_IRQ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz翻转频率
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 										// 输入下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-----SPI1-----//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;				// PA5-->SCK,PA6-->MISO,PA7-->MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  									// PA5/6/7复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //-----中断事件线连接-----//
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);						// 将事件线和Pin连接起来	
	//EXTI_InitStructure.EXTI_Line = EXTI_Line15;											// EXTI线中断开通
	//EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;									// 定义为中断还是事件
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;								// 下降沿触发
	//EXTI_InitStructure.EXTI_LineCmd = ENABLE;											// 使能EXTI线中断
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

