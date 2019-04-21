#include "nvic.h"

//-----外部变量声明-----//
extern __IO u8 g_ConCycT_flag;
//extern __IO u8 g_Fly_Enable;
//extern __IO s16 g_BasePWM;

//-----定时器3计数器-----//
u16 g_tim3counter = 0;

//-----//
extern u8 loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
extern volatile u16 loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt;


/***********************************
函数名：void TIM3_IRQHandler(void)
说明：TIM3中断处理函数
入口：无
出口：无
备注：用于系统定时，给出控制周期
***********************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	// 更新中断,1ms进来一次
	{
	    
		g_tim3counter++;

		if (g_tim3counter % 3 == 0)		// 3ms中断控制周期
			g_ConCycT_flag = 1;
		
        /*
           loop200HzCnt++;
		loop100HzCnt++;

		if(++loop50HzCnt * 50 >= (1000))
		{
			loop50HzCnt=0;
			loop50HzFlag=1;
		}
		if(++loop20HzCnt * 20 >=1000 )
		{
			loop20HzCnt=0;
			loop20HzFlag=1;
		}
		if(++loop10HzCnt * 10 >=1000 )
		{
			loop10HzCnt=0;
			loop10HzFlag=1;
		}
            */
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);		// 清除中断标志位
	}
}

/***************************************
函数名：void EXTI15_10_IRQHandler(void)
说明：EXTI15_10_IRQ组别中断处理函数
入口：无
出口：无
备注：用于接收NRF24L01数据
***************************************/
void EXTI15_10_IRQHandler(void)
{
    #if 0
	if (EXTI_GetITStatus(EXTI_Line15) != RESET)
  {
        
		if (NRF24L01_RxPacket(g_NRFRevData) == 0)	// 接收成功
		{
			g_NRFRevCnt++;	// 计数器++,计数器在计数,就说明遥控正在发送数据进来
            
            /*
			if (g_NRFRevData[0] == 239)	// 起飞允许
				g_Fly_Enable = 1;
			if (g_NRFRevData[0] == 223)	// 起飞失能
				g_Fly_Enable = 0;
			if (g_NRFRevData[0] == 127)	// 加油门
			{
				g_BasePWM += 20;
				if (g_BasePWM >= BASEPWM_MAX)		// 大于最大油门限制
					g_BasePWM = BASEPWM_MAX;
			}
			if (g_NRFRevData[0] == 191)	// 减油门
			{
				g_BasePWM -= 20;
				if (g_BasePWM <= 0)
					g_BasePWM = 0;
			}
			if (g_NRFRevData[0] == 253)	// 左滚
			{
				g_Exp_Roll = -8;					// -8°
				g_Exp_Pitch = 0;
			}
			if (g_NRFRevData[0] == 254)	// 右滚
			{
				g_Exp_Roll = 8;						// +8°
				g_Exp_Pitch = 0;
			}
			if (g_NRFRevData[0] == 247)	// 前倾
			{
				g_Exp_Pitch = -8;					// -8°
				g_Exp_Roll = 0;
			}
			if (g_NRFRevData[0] == 251)	// 后仰
			{
				g_Exp_Pitch = 8;					// +8°
				g_Exp_Roll = 0;
			}
			*/
				
		}
    EXTI_ClearITPendingBit(EXTI_Line15);			// 清除标志位
  }	
    #endif
}

/***********************************
函数名：void NVIC_Configuration(void)
说明：NVIC初始化
入口：无
出口：无
备注：无
************************************/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                        // 定义NVIC初始化结构体
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);             // 优先级组别1，具体参见misc.h line80
    
    //-----NRF24L01数据中断-----//
    //NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;        // IRQ中断通道-->NRF24L01,PA15
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // 抢先式优先级别
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // 副优先级别
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // 使能通道
    //NVIC_Init(&NVIC_InitStructure);                             // 初始化NVIC
    
    //-----TIM3定时中断-----//
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;             // 选中TIM3中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // 抢先式优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // 副优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


