#include "fusion.h"

//-----�����Ǳ궨ϵ��-----//
#define GYRO_CALIBRATION_COFF 0.015267f		// ��ϵ����MPU6050�е����������Ӧ

//-----��̬��-----//
float g_Pitch = 0.0;	// ��Χ-180��~+180�� -->�����¸�
float g_Roll = 0.0;		// ��Χ-90��~+90��		-->������
float g_Yaw = 0.0;		// ��Χ-180��~+180�� -->��ʱ��Ϊ��,˳ʱ��Ϊ��


//-----��̬������ض���-----//
#define PI 3.1415926					// Բ����
#define CNTLCYCLE 0.003f				// ��������
#define TWOKPDEF	(2.0f * 13.0f)		// 2��Kp
#define TWOKIDEF	(2.0f * 0.008)		// 2��Ki

//-----��̬��ز���-----//
__IO float g_twoKp = TWOKPDEF;													// 2��Kp
__IO float g_twoKi = TWOKIDEF;													// 2��Ki
__IO float g_q0 = 1.0f, g_q1 = 0.0f, g_q2 = 0.0f, g_q3 = 0.0f;					// ��Ԫ��
__IO float g_integralFBx = 0.0f, g_integralFBy = 0.0f, g_integralFBz = 0.0f;	// ��������ϵ�ϵĻ������


/***********************************************************
��������float invSqrt(float x)
˵�������ٿ����㷨
��ڣ���
���ڣ���
��ע��http://en.wikipedia.org/wiki/Fast_inverse_square_root
***********************************************************/
float invSqrt(float x)
{
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
	
  i = 0x5f3759df - (i>>1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
	
  return y;
}

/******************************************************
��������void ReadFromIMU(void)
˵������ȡMPU6050��ֵ���������ٶȼƺ������ǣ�һ��6��ֵ
��ڣ���
���ڣ���
��ע����
******************************************************/
void ReadFromIMU(void)
{
	Get_Accel_Data(ACCEL_XOUT_H);		//���ٶȼ�
	Get_Gyro_Data(GYRO_XOUT_H);			//������
}

/**************************************************
��������void IMU_Filter(void)
˵����IMU�˲����������ٶȼƵĻ����˲��������ǵı궨
��ڣ���
���ڣ���
��ע�����ô��ڻ����˲���������ΪACC_FILTER_DELAY
�ÿ�������3ms*ACC_FILTER_DELAY�õ��ͺ�ʱ�䳣��
����һ���ͺ��FIR�˲����������֮�󻷽�
�д��Լ��ٶȼƲ����۲��FFT�鿴Ƶ�׺����
�ͺ��ʱ�䳣��
**************************************************/
void IMU_Filter(void)
{
    s32 resultx = 0;
    static s32 s_resulttmpx[ACC_FILTER_DELAY] = {0};
    static u8 s_bufferCounterx = 0;
    static s32 s_totalx = 0;
		
	s32 resulty = 0;
    static s32 s_resulttmpy[ACC_FILTER_DELAY] = {0};
    static u8 s_bufferCountery = 0;
    static s32 s_totaly = 0;
		
	s32 resultz = 0;
    static s32 s_resulttmpz[ACC_FILTER_DELAY] = {0};
    static u8 s_bufferCounterz = 0;
    static s32 s_totalz = 0;

	// ���ٶȼ��˲�
    s_totalx -= s_resulttmpx[s_bufferCounterx];					// ���ܺ���ɾ��ͷ��Ԫ�ص�ֵ������ͷ��ָ��ְ��
    s_resulttmpx[s_bufferCounterx] = g_MPU6050Data.accel_x;		// ������ֵ�ŵ�β��ָ�봦������β��ָ��ְ��
    s_totalx += g_MPU6050Data.accel_x;		                    // �����ܺ�
                                                                   
    resultx = s_totalx / ACC_FILTER_DELAY;		                // ����ƽ��ֵ�������뵽һ���̶�������
    s_bufferCounterx++;		                        			// ����ָ��
    if (s_bufferCounterx == ACC_FILTER_DELAY)		            // ������б߽�
        s_bufferCounterx = 0;
		g_MPU6050Data_Filter.accel_x_f = resultx;
				
    s_totaly -= s_resulttmpy[s_bufferCountery];
    s_resulttmpy[s_bufferCountery] = g_MPU6050Data.accel_y;
    s_totaly += g_MPU6050Data.accel_y;

    resulty = s_totaly / ACC_FILTER_DELAY;
    s_bufferCountery++;
    if (s_bufferCountery == ACC_FILTER_DELAY)
        s_bufferCountery = 0;
		g_MPU6050Data_Filter.accel_y_f = resulty;
		
    s_totalz -= s_resulttmpz[s_bufferCounterz];
    s_resulttmpz[s_bufferCounterz] = g_MPU6050Data.accel_z;
    s_totalz += g_MPU6050Data.accel_z;

    resultz = s_totalz / ACC_FILTER_DELAY;
    s_bufferCounterz++;
    if (s_bufferCounterz == ACC_FILTER_DELAY)
        s_bufferCounterz = 0;
		g_MPU6050Data_Filter.accel_z_f = resultz;
	
		// �����Ǳ궨-->��ȥ��ʼʱ�̵�ֵ
		g_MPU6050Data_Filter.gyro_x_c = g_MPU6050Data.gyro_x - g_Gyro_xoffset;	// ��ȥ�궨��õ�ƫ��
		g_MPU6050Data_Filter.gyro_y_c = g_MPU6050Data.gyro_y - g_Gyro_yoffset;
		g_MPU6050Data_Filter.gyro_z_c = g_MPU6050Data.gyro_z - g_Gyro_zoffset;
		
		// ��������ֶ��궨,���÷ɻ�ˮƽ��ת90��,�ҵ�һ������ʹ��Yaw�պ�Ҳ��90��
		// �ò���Ҳ����ֱ�Ӳ鿴MPU6050�������ֲ��и�������������
		g_MPU6050Data_Filter.gyro_x_c *= GYRO_CALIBRATION_COFF;
		g_MPU6050Data_Filter.gyro_y_c *= GYRO_CALIBRATION_COFF;
		g_MPU6050Data_Filter.gyro_z_c *= GYRO_CALIBRATION_COFF;
}


/***************************************************************************************************
��������void IMUupdata(float gx, float gy, float gz, float ax, float ay, float az)
˵����IMU��Ԫ�����ںϣ�������̬��Ԫ��
��ڣ�float gx	������x����
			float gy	������y����
			float gz	������z����
			float ax	���ٶȼ�x����
			float ay	���ٶȼ�y����
			float az	���ٶȼ�z����
���ڣ���
��ע������˼��:������������������ٶ�̬�µ���̬,���ü��ٶȼ������нǶ�����
���ٶȼƲ���������ֱ�����ϵ��������ٶ���bϵ�е���������,����������ȫ��Ϊ��ȷֵ(�ο�ֵ)
Ϊ��������̬�������,����������һ����bϵ����ֱ�����ϵ�����
������������������,�õ����,�����������,��������Ҫ�ﵽ��Ŀ��
���Ƿ���,��nϵ��һ����ֱ�����ϵ�����[0 0 1],����һ����ת����֮�����ת����bϵ��
���ת��֮���������Ȼ����bϵ�е���ֱ�����ϵ�����,�������Ǿ��ҵ����������
���ѷ���,�Ǹ���ת�������������̬����ĺ��Ĳ���
������ͨ������������������������������ʱ��,���Ǿͼ�ӵ��޸�����ת�����ֵ,���Ǿʹﵽ�����ǵ�Ŀ��
�����ת����,�����Ƿ������Ҿ���,��������Ԫ��,������ŷ����
���ﵱȻ����Ԫ��.
��������,����ͨ����������ϵ(bϵ��nϵ)��ͬ����ֱ�����ϵ���������������ķ�ʽ����ӵ�������ת����
***************************************************************************************************/
void IMUupdata(float gx, float gy, float gz, float ax, float ay, float az)
{
	float recipNorm;				// ƽ�����ĵ���
	float halfvx, halfvy, halfvz;	// �ڵ�ǰ��������ϵ�У������������������ϵķ���
	float halfex, halfey, halfez;	// ��ǰ���ٶȼƲ�õ��������ٶ����������ϵķ����뵱ǰ��̬���������ϵ��������������,������ò���ķ�ʽ
	float qa, qb, qc;
	
	gx = gx * PI / 180;	// ת��Ϊ������
        gy = gy * PI / 180;
	gz = gz * PI / 180;
	
	// ������ٶȼƴ�����������״̬�����ܻ���������������������̬���㣬��Ϊ�������ĸ���������
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) 
	{
		// ��λ�����ٶȼ�,���������ڱ���˼��ٶȼƵ�����֮����Ҫ�޸�Kp����,��Ϊ�����һ����
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// ����ǰ��̬���������������ϵķ����������
		// ���Ƿ���������ת����ĵ�����,ע���ǵ�������ϵ(nϵ)����������ϵ(bϵ)��,��ҪŪ����.���������bϵ��nϵ,ת�ü���
		// ʼ�ռ�������ݵ��Ƿɻ�,����һ�е�����Ҫ����������ϵ�����ο�,����������Ҫ�ӵ�������ϵ��ת������������ϵ��
		halfvx = g_q1 * g_q3 - g_q0 * g_q2;
		halfvy = g_q0 * g_q1 + g_q2 * g_q3;
		halfvz = g_q0 * g_q0 - 0.5f + g_q3 * g_q3;
	
		// �����ɵ�ǰ��̬���������������ϵķ�������ٶȼƲ�õ��������������ϵķ����Ĳ�,���������ά�ռ�Ĳ��(������)�������
		// ���㹫ʽ�ɾ��������Ƶ����� ��ʽ�μ�http://en.wikipedia.org/wiki/Cross_product �е�Mnemonic����
		halfex = (ay * halfvz - az * halfvy);
		halfey = (az * halfvx - ax * halfvz);
		halfez = (ax * halfvy - ay * halfvx);

		// ���������,���ڵ�ǰ��̬����������������뵱ǰ���ٶȼƲ�õ����������Ĳ�ֵ���л����������
		if(g_twoKi > 0.0f) 
		{
			g_integralFBx += g_twoKi * halfex * CNTLCYCLE;		// Ki����
			g_integralFBy += g_twoKi * halfey * CNTLCYCLE;
			g_integralFBz += g_twoKi * halfez * CNTLCYCLE;
			gx += g_integralFBx;		// �������������������ϣ����������ǵ�ֵ
			gy += g_integralFBy;
			gz += g_integralFBz;
		}
		else	// �����л������㣬ֻ���б�������
		{
			g_integralFBx = 0.0f;
			g_integralFBy = 0.0f;
			g_integralFBz = 0.0f;
		}
		
		// ֱ��Ӧ�ñ������ڣ����������ǵ�ֵ
		gx += g_twoKp * halfex;
		gy += g_twoKp * halfey;
		gz += g_twoKp * halfez;
	}
	
	//����Ϊ��Ԫ��΢�ַ���.�������Ǻ���Ԫ���������������̬���µĺ�������
	//���㷽���ɾ��������Ƶ�����
	//	.		1      
	//	q = - * q x Omega    ʽ���������Ԫ���ĵ���,�ұߵ�x����Ԫ���˷�,Omega�������ǵ�ֵ(�����ٶ�)
	//			2
	//	 .
	//	[q0] 		[0		-wx		-wy		-wz]	[q0]
	//	 .				
	//	[q1]		[wx	  0		  wz		-wy]	[q1]
	//	 .	 =  											* 
	//	[q2]		[wy	 -wz	  0		  wx ]	[q2]
	//	 . 			
	//	[q3]		[wz 	wy	 -wx		0	 ]	[q3]
	gx *= (0.5f * CNTLCYCLE);
	gy *= (0.5f * CNTLCYCLE);
	gz *= (0.5f * CNTLCYCLE);
	qa = g_q0;
	qb = g_q1;
	qc = g_q2;
	g_q0 += (-qb * gx - qc * gy - g_q3 * gz);
	g_q1 += ( qa * gx + qc * gz - g_q3 * gy);
	g_q2 += ( qa * gy - qb * gz + g_q3 * gx);
	g_q3 += ( qa * gz + qb * gy -   qc * gx);
	
	// ��λ����Ԫ��,�������ڵ�λ����Ԫ���ڿռ���תʱ�ǲ��������,������ת�Ƕ�.�����������Դ�������������任
	recipNorm = invSqrt(g_q0 * g_q0 + g_q1 * g_q1 + g_q2 * g_q2 + g_q3 * g_q3);
	g_q0 *= recipNorm;
	g_q1 *= recipNorm;
	g_q2 *= recipNorm;
	g_q3 *= recipNorm;
	
	// ��Ԫ����ŷ����ת����ת��˳��ΪZ-Y-X,�μ�<Representing Attitude: Euler Angles, Unit Quaternions, and Rotation Vectors>.pdfһ��,P24
	// ע���ʱ��ת��˳����1-2-3����X-Y-Z���������ڻ�ͼ���㣬������������һ��ת����������Z��X������˳��û��
	g_Yaw = atan2(2 * g_q1 * g_q2 + 2 * g_q0 * g_q3, g_q1 * g_q1 + g_q0 * g_q0 - g_q3 * g_q3 - g_q2 * g_q2) * 180 / PI;	// Yaw
	g_Roll = asin(-2 * g_q1 * g_q3 + 2 * g_q0* g_q2) * 180 / PI; 														// Roll
  g_Pitch = atan2(2 * g_q2 * g_q3 + 2 * g_q0 * g_q1, -2 * g_q1 * g_q1 - 2 * g_q2* g_q2 + 1) * 180 / PI; 				// Pitch
}



