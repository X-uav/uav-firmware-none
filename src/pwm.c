#include "pwm.h"


/***********************************************************************************
��������void PWM_Set(const u16 pwm1, const u16 pwm2, const u16 pwm3, const u16 pwm4)
˵����PWM����
��ڣ���
���ڣ���
��ע������PWM����ֵ������ӦPWM�źŵƵ�״̬:
��PWMΪ0ʱ������
��Ϊ0ʱ������
************************************************************************************/
void PWM_Set(const u16 pwm1, const u16 pwm2, const u16 pwm3, const u16 pwm4)
{
    /*
	if (pwm1 == 0)	//û��PWM����ʱ����
		LED1 = 1;
	else
		LED1 = 0;
	if (pwm2 == 0)	//û��PWM����ʱ����
		LED2 = 1;
	else
		LED2 = 0;
	if (pwm3 == 0)	//û��PWM����ʱ����
		LED3 = 1;
	else
		LED3 = 0;
	if (pwm4 == 0)	//û��PWM����ʱ����
		LED4 = 1;
	else
		LED4 = 0;
	*/
	TIM_SetCompare1(TIM2, pwm1);
	TIM_SetCompare2(TIM2, pwm2);
	TIM_SetCompare3(TIM2, pwm3);
	TIM_SetCompare4(TIM2, pwm4);
}

