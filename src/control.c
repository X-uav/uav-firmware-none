#include "control.h"

//-----���ȷ��-----//
__IO u8 g_Fly_Enable = 0;

//-----�ٶȲ���-----//
__IO s16 g_BasePWM = 1000;		// ����PWM(����)-->��ɵ���СPWM,��һ��Ϊ1000����
static u16 g_MaxPWM = 2000;		// ���PWM-->�˶������и��������PWM

//-----PID��������-----//
//+ģʽ����P = 0.8ʱ,D = 0.8~0.9
//xģʽ����P = 2.15ʱ,D = 0.5~0.7
//20140111 P = 2.1,D = 0.4 ??
//20140112 P = 3.4,D = 0.75 ���м���,�����
//20140115 P = 2.5,D = 0.6 ���п죬û����.����PD�о���(����)
//20140118 P = 3.2,D = 0.7 ��ǶȻ��л�������,�����ϴ��¿���ƽ��
static float g_PID_Kp = 3.1f;			// PID���Ʊ���ϵ��
static float g_PID_Ki = 0.12f;			// PID���ƻ���ϵ��
static float g_PID_Kd = 0.65f;			// PID����΢��ϵ��
static float g_PID_Yaw_Kp = 8.0f;		// YAW������P����

//-----ң����̬����-----//
__IO s16 g_Exp_Pitch = 0;	// ͨ��ң�ظ�����΢�����ƽǶ�
__IO s16 g_Exp_Roll = 0;

//-----��̬���ṹ�嶨��-----//
struct _Attitude_Error_Tag g_Attitude_Error = {0,0,0};

//-----���PWM���-----//
static s16 g_motor1_PWM = 0, g_motor2_PWM = 0, g_motor3_PWM = 0, g_motor4_PWM = 0;

/************************************************************************************************
��������void Quadrotor_Control(const float Exp_Pitch, const float Exp_Roll, const float Exp_Yaw)
˵������������ƺ���������PWM��������
��ڣ�const float Exp_Pitch	����������
			const float Exp_Roll	���������
			const float Exp_Yaw		����ƫ����
���ڣ���
��ע����ǰ���ƻ�Ϊ��̬���ƻ�
������    ��Ƕȷ�������    ��    ��ͣ�Ƶ�ָʾ
************************************************************************************************/
void Quadrotor_Control(const float Exp_Pitch, const float Exp_Roll, const float Exp_Yaw)
{
    s16 outputPWM_Pitch, outputPWM_Roll, outputPWM_Yaw;

    // --- �õ���ǰϵͳ�����-->���������Ƕȼ�ȥ��ǰ�Ƕ�
	g_Attitude_Error.g_Error_Pitch = Exp_Pitch - g_Pitch;
	g_Attitude_Error.g_Error_Roll = Exp_Roll - g_Roll;
	g_Attitude_Error.g_Error_Yaw = Exp_Yaw - g_Yaw;

    // --- ���̫�󣬷�������
	if (fabs(g_Attitude_Error.g_Error_Pitch) >= 55 || fabs(g_Attitude_Error.g_Error_Roll) >= 55)
	{
		//PWM2_LED = 0;			// ��������
		PWM_Set(0, 0, 0, 0);	// ͣ��
		return ;
	}
	//PWM2_LED = 1;				// ����Ϩ��

    // --- �ȶ�ָʾ��,��ɫ.���Ƕ�ֵС��3��ʱ���ж�Ϊ�����ȶ�,�Ƶ�����
	if (fabs(g_Attitude_Error.g_Error_Pitch) <= 3 && fabs(g_Attitude_Error.g_Error_Roll) <= 3)
		//PWM4_LED = 0;
		{;;}
	else
		//PWM4_LED = 1;
		{;;}

    // --- �����������������޷�
	if (fabs(g_Attitude_Error.g_Error_Pitch) <= 20)	// ���ַ���-->����̬����С��20��ʱ�������
	{	// Pitch
		// �ۼ����
		g_Attitude_Error.g_ErrorI_Pitch += g_Attitude_Error.g_Error_Pitch;

		// �����޷�
		if (g_Attitude_Error.g_ErrorI_Pitch >= PITCH_I_MAX)
			g_Attitude_Error.g_ErrorI_Pitch = PITCH_I_MAX;
		else if (g_Attitude_Error.g_ErrorI_Pitch <= -PITCH_I_MAX)
			g_Attitude_Error.g_ErrorI_Pitch = -PITCH_I_MAX;	
	}
    if (fabs(g_Attitude_Error.g_Error_Roll) <= 20)
	{	// Roll
		// �ۼ����		
		g_Attitude_Error.g_ErrorI_Roll += g_Attitude_Error.g_Error_Roll;
		
		// �����޷�		
		if (g_Attitude_Error.g_ErrorI_Roll >= ROLL_I_MAX)
			g_Attitude_Error.g_ErrorI_Roll = ROLL_I_MAX;
		else if (g_Attitude_Error.g_ErrorI_Roll <= -ROLL_I_MAX)
			g_Attitude_Error.g_ErrorI_Roll = -ROLL_I_MAX;		
	}

    // --- PID����-->�����΢��D���㲢�Ǵ�ͳ�����ϵ�����ǰһ�ε�����ȥ��һ�ε�������
	// --- ����ֱ�����������ǵ�ֵ�����΢����,�����Ĵ���ǳ���,��Ϊ����������Ӳ����ʩ,�����Ǳ�����Ǿ���������Ч��
	outputPWM_Pitch = (s16)(g_PID_Kp * g_Attitude_Error.g_Error_Pitch + g_PID_Ki * g_Attitude_Error.g_ErrorI_Pitch - g_PID_Kd * g_MPU6050Data_Filter.gyro_x_c);
	outputPWM_Roll = (s16)(g_PID_Kp * g_Attitude_Error.g_Error_Roll + g_PID_Ki * g_Attitude_Error.g_ErrorI_Roll - g_PID_Kd * g_MPU6050Data_Filter.gyro_y_c);
	outputPWM_Yaw = (s16)(g_PID_Yaw_Kp * g_Attitude_Error.g_Error_Yaw);

    // --- ����PWM���������ĸ����-->Xģʽ����
	//�ر�ע�⣬������������ˣ���Ϊ����Ƿ���
	g_motor1_PWM = g_BasePWM + outputPWM_Pitch + outputPWM_Roll + outputPWM_Yaw;
	g_motor2_PWM = g_BasePWM - outputPWM_Pitch + outputPWM_Roll - outputPWM_Yaw;
	g_motor3_PWM = g_BasePWM - outputPWM_Pitch - outputPWM_Roll + outputPWM_Yaw;
	g_motor4_PWM = g_BasePWM + outputPWM_Pitch - outputPWM_Roll - outputPWM_Yaw;
	// --- ȥ��ƫ������
    //	g_motor1_PWM = g_BasePWM + outputPWM_Pitch + outputPWM_Roll;
    //	g_motor2_PWM = g_BasePWM - outputPWM_Pitch + outputPWM_Roll;
    //	g_motor3_PWM = g_BasePWM - outputPWM_Pitch - outputPWM_Roll;
    //	g_motor4_PWM = g_BasePWM + outputPWM_Pitch - outputPWM_Roll;
    	// --- ƫ����������
    //	g_motor1_PWM = g_BasePWM + outputPWM_Yaw;
    //	g_motor2_PWM = g_BasePWM - outputPWM_Yaw;
    //	g_motor3_PWM = g_BasePWM + outputPWM_Yaw;
    //	g_motor4_PWM = g_BasePWM - outputPWM_Yaw;
    	// --- +ģʽ�������
    //	g_motor2_PWM = g_BasePWM - outputPWM_Pitch;
    //	g_motor4_PWM = g_BasePWM + outputPWM_Pitch;
    	// --- xģʽ�������
    //	g_motor1_PWM = g_BasePWM + outputPWM_Pitch;
    //	g_motor2_PWM = g_BasePWM - outputPWM_Pitch;
    //	g_motor3_PWM = g_BasePWM - outputPWM_Pitch;
    //	g_motor4_PWM = g_BasePWM + outputPWM_Pitch;
    	// --- ���ز���
    //	g_motor1_PWM = g_BasePWM;
    //	g_motor2_PWM = g_BasePWM;
    //	g_motor3_PWM = g_BasePWM;
    //	g_motor4_PWM = g_BasePWM;

    // --- PWM��������,��Ϊû�з�ת
	if (g_motor1_PWM < 0)
		g_motor1_PWM = 0;
	if (g_motor2_PWM < 0)
		g_motor2_PWM = 0;
	if (g_motor3_PWM < 0)
		g_motor3_PWM = 0;
	if (g_motor4_PWM < 0)
		g_motor4_PWM = 0;

    // --- PWM�޷�
	if (g_motor1_PWM >= g_MaxPWM)
		g_motor1_PWM = g_MaxPWM;
	if (g_motor2_PWM >= g_MaxPWM)
		g_motor2_PWM = g_MaxPWM;
	if (g_motor3_PWM >= g_MaxPWM)
		g_motor3_PWM = g_MaxPWM;
	if (g_motor4_PWM >= g_MaxPWM)
		g_motor4_PWM = g_MaxPWM;

    
    if (g_Fly_Enable)          // �������,����PWM
        {PWM_Set(g_motor1_PWM, g_motor2_PWM, g_motor3_PWM, g_motor4_PWM);}
    else
        {PWM_Set(0, 0, 0, 0);}    // ͣ��
}
	

