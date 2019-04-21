#include "iic.h"

/***************************
��������void IIC_Init(void)
˵����IIC��ʼ��
��ڣ���
���ڣ���
��ע��������ߵ�ƽ
****************************/
void IIC_Init(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_6| GPIO_Pin_7);
}


/***************************
��������void IIC_Start(void)
˵��������IIC��ʼ�ź�
��ڣ���
���ڣ���
��ע����
****************************/
void IIC_Start(void)
{
    SDA_OUT();// SDA�����
    IIC_SDA_H;
    IIC_SCL_H;
    Delay_us(4);
    IIC_SDA_L;
    //Delay_us(1);
    IIC_SCL_L;// ǯסI2C���ߣ�׼�����ͻ�������� 
}

/***************************
��������void IIC_Stop(void)
˵��������IICֹͣ�ź�
��ڣ���
���ڣ���
��ע����
****************************/
void IIC_Stop(void)
{
    SDA_OUT();// SDA�����
    IIC_SDA_L;
    Delay_us(4);
    IIC_SCL_H;
    //Delay_us(1);
    IIC_SDA_H;// ����I2C���߽����ź�
    Delay_us(5);// �ٴ�������Ҫ4.7us
}

/*****************************
��������u8 IIC_Wait_Ack(void)
˵�����ȴ�Ӧ���źŵ���
��ڣ���
���ڣ�u8    1 :����Ӧ��ʧ��
            0������Ӧ��ɹ�
��ע����
*****************************/
u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    
    SDA_IN();                   // SDA����Ϊ����  
    IIC_SDA_H;
    //Delay_us(1);       
    IIC_SCL_H;
    //Delay_us(1);     
    while (READ_SDA)            // SDAΪ�ߣ��ȴ�IIC��������
    {
        ucErrTime++;
        if (ucErrTime > 250)    // 40*250=1msδ�𸴣�IIC����ֹͣ�ź�
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_L;
    return 0;
}

/*************************
��������void IIC_Ack(void)
˵��������ACKӦ��
��ڣ���
���ڣ���
��ע����
**************************/
void IIC_Ack(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_L;
    //Delay_us(1);
    IIC_SCL_H;
    //Delay_us(1);
    IIC_SCL_L;
}

/**************************
��������void IIC_NAck(void)
˵����������ACKӦ��		
��ڣ���
���ڣ���
��ע����
***************************/
void IIC_NAck(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_H;
    //Delay_us(1);
    IIC_SCL_H;
    //Delay_us(1);
    IIC_SCL_L;
}

/*********************************
��������void IIC_Send_Byte(u8 txd)
˵����IIC����һ���ֽ�
��ڣ�u8 txd
���ڣ���
��ע����
*********************************/
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;  
    
    SDA_OUT();      
    IIC_SCL_L;      // ����ʱ�ӿ�ʼ���ݴ���
    for (t = 0; t < 8; t++)
    {              
            if ((txd&0x80) >> 7)
                IIC_SDA_H;
            else
                IIC_SDA_L;
            txd <<= 1;    
            //Delay_us(1);
            IIC_SCL_H;
            //Delay_us(1); 
            IIC_SCL_L;
    }
    IIC_Wait_Ack();
}

/********************************
��������u8 IIC_Read_Byte(u8 ack)
˵����IIC��һ���ֽ�
��ڣ�u8 ack 	ack=1������ACK
				ack=0������nACK
���ڣ�u8 		1����Ӧ��
				0����Ӧ��		
��ע�����شӻ�����Ӧ��
********************************/
u8 IIC_Read_Byte(u8 ack)
{
    u8 i, receive = 0;
    
    SDA_IN();   // SDA����Ϊ����
    for (i = 0; i < 8; i++)
    {
        IIC_SCL_L; 
        //Delay_us(1);
        IIC_SCL_H;
        receive <<= 1;
        if (READ_SDA)       // �յ�1
            receive++;
        //Delay_us(1); 
    }                  
    if (!ack)
            IIC_NAck();     // ����nACK
    else
            IIC_Ack();      // ����ACK   
    return receive;
}



