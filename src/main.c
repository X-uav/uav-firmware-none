/*************************************************************************************
* Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.
* After program start green LED (LED_E) will blink.
*
* Program has to be compiled with optimizer setting "-O0".
* Otherwise delay via while-loop will not work correctly.
*************************************************************************************/
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "iic.h"
#include "mpu6050.h"
#include "usart.h"
#include "pwm.h"
#include "spi.h"
#include "nrf24l01.h"
#include "nvic.h"
#include "pwm.h"

//-----外部变量声明-----//
extern u16 g_tim3counter;	// 定时器2计数器，用来在进入程序时的强制置0

//-----姿态角-----//
extern float g_Pitch;	// 范围-180°~+180° -->上正下负
extern float g_Roll;		// 范围-90°~+90°		-->左负右正
extern float g_Yaw;		// 范围-180°~+180° -->逆时针为正,顺时针为负


//-----系统控制周期开关变量-----//
__IO u8 g_ConCycT_flag = 0;	// 每个控制周期开始时置1,volatile类型保证中断不出错

void HardWare_Init(void)
{
    GPIO_Configuration();
    NVIC_Configuration();
    Delay_Init();
    IIC_Init();
    MPU6050_Init();
    USART_Configuration();
    TIMx_Configuration();
    SPI_Configuration();
    NRF24L01_Init();
    
}

int main(int argc, char *argv[])
{
    
    HardWare_Init();
    
    PWM_Set(100,100,100,100);

    if(!NRF24L01_Check())
    {
        printf("NRF24L01 match success.\r\n");
        NRF_Matching();
    }else
    {
        printf("NRF24L01 match failed\r\n");
    }

    LED_Tail_ON();
    LED_Front_ON();

    IMU_Calibration();	// IMU标定
	g_tim3counter = 0;
	g_ConCycT_flag = 0;
    
    
    while(1)
    {
        
        Delay_ms(100);
        
		if (g_ConCycT_flag)	// 3ms控制周期进来一次
		{
			g_ConCycT_flag = 0;

            #if 0
            ReadFromIMU();		// 读取MPU6050的值
            printf("original :accel_x = %d, accel_y = %d, accel_z = %d\r\n",g_MPU6050Data.accel_x,g_MPU6050Data.accel_y,g_MPU6050Data.accel_z);
			IMU_Filter();		// 加速度计滤波与陀螺仪标定输出
			printf("filter : accel_x_f = %d, accel_y_f = %d, accel_z_f = %d\r\n",g_MPU6050Data_Filter.accel_x_f,g_MPU6050Data_Filter.accel_y_f,g_MPU6050Data_Filter.accel_z_f);
            printf("filter :gyro_x_c = %d, gyro_y_c = %d, gyro_z_c = %d\r\n",g_MPU6050Data_Filter.gyro_x_c,g_MPU6050Data_Filter.gyro_y_c,g_MPU6050Data_Filter.gyro_z_c);
			IMUupdata(g_MPU6050Data_Filter.gyro_x_c, g_MPU6050Data_Filter.gyro_y_c, g_MPU6050Data_Filter.gyro_z_c,	// 四元数姿态更新
								g_MPU6050Data_Filter.accel_x_f * 0.0098, g_MPU6050Data_Filter.accel_y_f * 0.0098, g_MPU6050Data_Filter.accel_z_f * 0.0098);	//*0.0098将g转换为mg
            printf("g_Pitch = %f, g_Roll = %f, g_Yaw = %f\r\n",g_Pitch,g_Roll,g_Yaw);
            #endif
            Nrf_Irq();
        }	   
    }
}
