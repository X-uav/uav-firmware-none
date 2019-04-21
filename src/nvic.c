#include "nvic.h"

//-----�ⲿ��������-----//
extern __IO u8 g_ConCycT_flag;
//extern __IO u8 g_Fly_Enable;
//extern __IO s16 g_BasePWM;

//-----��ʱ��3������-----//
u16 g_tim3counter = 0;

//-----//
extern u8 loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
extern volatile u16 loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt;


/***********************************
��������void TIM3_IRQHandler(void)
˵����TIM3�жϴ�����
��ڣ���
���ڣ���
��ע������ϵͳ��ʱ��������������
***********************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	// �����ж�,1ms����һ��
	{
	    
		g_tim3counter++;

		if (g_tim3counter % 3 == 0)		// 3ms�жϿ�������
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
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);		// ����жϱ�־λ
	}
}

/***************************************
��������void EXTI15_10_IRQHandler(void)
˵����EXTI15_10_IRQ����жϴ�����
��ڣ���
���ڣ���
��ע�����ڽ���NRF24L01����
***************************************/
void EXTI15_10_IRQHandler(void)
{
    #if 0
	if (EXTI_GetITStatus(EXTI_Line15) != RESET)
  {
        
		if (NRF24L01_RxPacket(g_NRFRevData) == 0)	// ���ճɹ�
		{
			g_NRFRevCnt++;	// ������++,�������ڼ���,��˵��ң�����ڷ������ݽ���
            
            /*
			if (g_NRFRevData[0] == 239)	// �������
				g_Fly_Enable = 1;
			if (g_NRFRevData[0] == 223)	// ���ʧ��
				g_Fly_Enable = 0;
			if (g_NRFRevData[0] == 127)	// ������
			{
				g_BasePWM += 20;
				if (g_BasePWM >= BASEPWM_MAX)		// ���������������
					g_BasePWM = BASEPWM_MAX;
			}
			if (g_NRFRevData[0] == 191)	// ������
			{
				g_BasePWM -= 20;
				if (g_BasePWM <= 0)
					g_BasePWM = 0;
			}
			if (g_NRFRevData[0] == 253)	// ���
			{
				g_Exp_Roll = -8;					// -8��
				g_Exp_Pitch = 0;
			}
			if (g_NRFRevData[0] == 254)	// �ҹ�
			{
				g_Exp_Roll = 8;						// +8��
				g_Exp_Pitch = 0;
			}
			if (g_NRFRevData[0] == 247)	// ǰ��
			{
				g_Exp_Pitch = -8;					// -8��
				g_Exp_Roll = 0;
			}
			if (g_NRFRevData[0] == 251)	// ����
			{
				g_Exp_Pitch = 8;					// +8��
				g_Exp_Roll = 0;
			}
			*/
				
		}
    EXTI_ClearITPendingBit(EXTI_Line15);			// �����־λ
  }	
    #endif
}

/***********************************
��������void NVIC_Configuration(void)
˵����NVIC��ʼ��
��ڣ���
���ڣ���
��ע����
************************************/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                        // ����NVIC��ʼ���ṹ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);             // ���ȼ����1������μ�misc.h line80
    
    //-----NRF24L01�����ж�-----//
    //NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;        // IRQ�ж�ͨ��-->NRF24L01,PA15
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ����ʽ���ȼ���
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // �����ȼ���
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ��ͨ��
    //NVIC_Init(&NVIC_InitStructure);                             // ��ʼ��NVIC
    
    //-----TIM3��ʱ�ж�-----//
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;             // ѡ��TIM3�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ����ʽ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


