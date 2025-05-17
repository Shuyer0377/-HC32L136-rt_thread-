#ifndef __DHT11_H
#define __DHT11_H 

#include "gpio.h"  // 替换原来的sys.h
#include "rtdef.h"

// 定义GPIO端口和引脚（根据你的硬件连接修改）
#define DHT11_PORT    GpioPortB  // 假设使用PA端口
#define DHT11_PIN     GpioPin4  // 假设使用PA15引脚

// IO操作宏定义（使用你的GPIO驱动）
#define DHT11_DQ_OUT(bVal)  Gpio_WriteOutputIO(DHT11_PORT, DHT11_PIN, bVal)
#define DHT11_DQ_IN         Gpio_GetInputIO(DHT11_PORT, DHT11_PIN)

// 函数声明
	uint8_t DHT11_Init(void);
	rt_uint8_t DHT11_Read_Data(rt_uint8_t *temp, rt_uint8_t *humi);
	rt_uint8_t DHT11_Read_Byte(void);
	rt_uint8_t DHT11_Read_Bit(void);
	rt_uint8_t DHT11_Check(void);
	void DHT11_Rst(void);
	void Display_DHT11(void);



#endif