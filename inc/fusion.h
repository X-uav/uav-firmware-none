#ifndef __FUSION_H
#define __FUSION_H

#include "stm32f10x.h"
#include "mpu6050.h"
#include "math.h"

#define ACC_FILTER_DELAY 8	// ���ٶȼ��˲�֮�󻷽�,��ǰΪ3*16=48ms

//-----��������-----//
extern float g_Pitch;		// ��̬ŷ����
extern float g_Roll;
extern float g_Yaw;


//-----��������-----//
void ReadFromIMU(void); //// ��ȡMPU6050��ֵ���������ٶȼƺ������ǣ�һ��6��ֵ
extern void IMUupdata(float gx, float gy, float gz, float ax, float ay, float az);	// IMU��Ԫ�����ںϣ�������̬��Ԫ��
extern void IMU_Filter(void);		// ���ٶȼ��˲��������Ǳ궨���

#endif
