#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f10x.h"
#include "iic.h"
#include "delay.h"
#include "fusion.h"

//-----MPU6050�Ĵ���-----//
#define	SMPLRT_DIV			0x19	// �����ǲ�����,����ֵ:0x07(125Hz)
#define	MPU6050_CONFIG		0x1A	// ��ͨ�˲�Ƶ��,����ֵ:0x06(5Hz)
#define	GYRO_CONFIG			0x1B	// �������Լ켰������Χ,����ֵ:0x18(���Լ�,2000deg/s)
#define	ACCEL_CONFIG		0x1C	// ���ٶȼ��Լ졢������Χ����ͨ�˲�Ƶ��,����ֵ:0x00(���Լ�,2g,5Hz)
#define	ACCEL_XOUT_H		0x3B
#define	ACCEL_XOUT_L		0x3C
#define	ACCEL_YOUT_H		0x3D
#define	ACCEL_YOUT_L		0x3E
#define	ACCEL_ZOUT_H		0x3F
#define	ACCEL_ZOUT_L		0x40
#define	TEMP_OUT_H			0x41
#define	TEMP_OUT_L			0x42
#define	GYRO_XOUT_H			0x43
#define	GYRO_XOUT_L			0x44	
#define	GYRO_YOUT_H			0x45
#define	GYRO_YOUT_L			0x46
#define	GYRO_ZOUT_H			0x47
#define	GYRO_ZOUT_L			0x48
#define	PWR_MGMT_1			0x6B	// ��Դ����,����ֵ:0x00(��������)


//-----MPU6050�豸��ַ-----//
#define	MPU6050_DEVICE	0xD0		// IICд��ʱ�ĵ�ַ�Ĵ���,+1Ϊ��ȡ,AD0�ӵ�

//-----�ṹ���������-----//
struct MPU6050_tag	// IMUֱ�Ӳ���ֵ
{
	s16 accel_x;	// ���ٶȼ�x
	s16 accel_y;	// ���ٶȼ�y
	s16 accel_z;	// ���ٶȼ�z
	s16 gyro_x;		// ������x
	s16 gyro_y;		// ������y
	s16 gyro_z;		// ������z
};

struct MPU6050Filter_tag			// IMU�˲����ֵ
{
	s16 accel_x_f;	// ���ٶȼ�x�˲����ֵ
	s16 accel_y_f;	// ���ٶȼ�y�˲����ֵ
	s16 accel_z_f;	// ���ٶȼ�z�˲����ֵ
	s16 gyro_x_c;	// �����Ǳ궨���ֵ
	s16 gyro_y_c;	// �����Ǳ궨���ֵ
	s16 gyro_z_c;	// �����Ǳ궨���ֵ
};

extern struct MPU6050_tag g_MPU6050Data;				// IMUֱ�Ӳ���ֵ
extern struct MPU6050Filter_tag g_MPU6050Data_Filter;	// IMU�˲���Ľṹ��
extern s32 g_Gyro_xoffset;								// IMU�궨������
extern s32 g_Gyro_yoffset;
extern s32 g_Gyro_zoffset;


//-----��������-----//
extern void MPU6050_Init(void);							// ��ʼ��MPU6050
extern void MPU6050_WirteByte(u8 reg, u8 data);			// MPU6050����д�ֽ�
extern u8 MPU6050_ReadByte(u8 reg);						// MPU6050���ζ��ֽ�
extern void	Get_Accel_Data(u8 reg);						// �õ�MPU6050���ٶȼ�����
extern void	Get_Gyro_Data(u8 reg);						// �õ�MPU6050����������
extern void IMU_Calibration(void);						// MPU6050�궨



#endif
