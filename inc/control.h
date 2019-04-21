#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x.h"
#include "math.h"
#include "fusion.h"
#include "pwm.h"

//-----�������ֵ-----//
#define BASEPWM_MAX		1600	// ��������ԭ������Ϊ������Ź���PID����ֵ������PWM���ֵ���ᵼ�·�ת���ز��㣬�෭

//-----PID�������ֵ-----//
#define PITCH_I_MAX	300
#define ROLL_I_MAX	300

//-----��̬���ṹ������-----//
struct _Attitude_Error_Tag
{
 float g_Error_Pitch;		// ��ǰ���������
 float g_Error_Roll;		// ��ǰ��������
 float g_Error_Yaw;			// ��ǰƫ�������
 float g_ErrorI_Pitch;		// ��ǰ��������������
 float g_ErrorI_Roll;		// ��ǰ�������������
};

//-----��������-----//
extern __IO s16 g_Exp_Pitch;	// ͨ��ң�ظ�����΢�����ƽǶ�
extern __IO s16 g_Exp_Roll;
//-----��������-----//
void Quadrotor_Control(const float Exp_Pitch, const float Exp_Roll, const float Exp_Yaw);	// ��������ƺ���������PWM��������

#endif

