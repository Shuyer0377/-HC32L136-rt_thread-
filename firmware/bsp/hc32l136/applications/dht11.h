#ifndef __DHT11_H
#define __DHT11_H 

#include "gpio.h"  // �滻ԭ����sys.h
#include "rtdef.h"

// ����GPIO�˿ں����ţ��������Ӳ�������޸ģ�
#define DHT11_PORT    GpioPortB  // ����ʹ��PA�˿�
#define DHT11_PIN     GpioPin4  // ����ʹ��PA15����

// IO�����궨�壨ʹ�����GPIO������
#define DHT11_DQ_OUT(bVal)  Gpio_WriteOutputIO(DHT11_PORT, DHT11_PIN, bVal)
#define DHT11_DQ_IN         Gpio_GetInputIO(DHT11_PORT, DHT11_PIN)

// ��������
	uint8_t DHT11_Init(void);
	rt_uint8_t DHT11_Read_Data(rt_uint8_t *temp, rt_uint8_t *humi);
	rt_uint8_t DHT11_Read_Byte(void);
	rt_uint8_t DHT11_Read_Bit(void);
	rt_uint8_t DHT11_Check(void);
	void DHT11_Rst(void);
	void Display_DHT11(void);



#endif