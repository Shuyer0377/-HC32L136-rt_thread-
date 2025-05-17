#include "dht11.h"
#include "gpio.h"
#include "oled.h"

// 配置GPIO为输出模式
void DHT11_IO_OUT(void)
{
    stc_gpio_config_t gpio_init;
    
    // 初始化配置结构体
    DDL_ZERO_STRUCT(gpio_init);
    
    gpio_init.enDir = GpioDirOut;      // 输出模式
    gpio_init.enDrv = GpioDrvH;        // 高驱动能力
    gpio_init.enPuPd = GpioNoPuPd; // 无上下拉
    gpio_init.enOD = GpioOdDisable;     // 禁止开漏输出
    
    // 初始化GPIO
    Gpio_Init(DHT11_PORT, DHT11_PIN, &gpio_init);
}

// 配置GPIO为输入模式
void DHT11_IO_IN(void)
{
    stc_gpio_config_t gpio_init;
    
    // 初始化配置结构体
    DDL_ZERO_STRUCT(gpio_init);
    
    gpio_init.enDir = GpioDirIn;       // 输入模式
    gpio_init.enPuPd = GpioNoPuPd; // 无上下拉
    
    // 初始化GPIO
    Gpio_Init(DHT11_PORT, DHT11_PIN, &gpio_init);
}

// 复位DHT11
void DHT11_Rst(void)
{
    DHT11_IO_OUT();     // 设置为输出模式
    DHT11_DQ_OUT(FALSE); // 拉低DQ
    delay1ms(20);       // 保持至少18ms
    DHT11_DQ_OUT(TRUE);  // 释放总线
    delay10us(3);       // 主机拉高20~40us
}

// 检查DHT11响应
rt_uint8_t DHT11_Check(void)
{
    rt_uint8_t retry = 0;
    DHT11_IO_IN();      // 设置为输入模式
    
    // 等待DHT11拉低（超时100us）
    while(DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    if(retry >= 100) return 1;
    
    retry = 0;
    // 等待DHT11拉高（超时100us）
    while(!DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    if(retry >= 100) return 1;
    
    return 0;
}

// 读取一个位
rt_uint8_t DHT11_Read_Bit(void)
{
    rt_uint8_t retry = 0;
    
    // 等待低电平（DHT11开始发送位）
    while(DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    
    retry = 0;
    // 等待高电平
    while(!DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    
    delay10us(4); // 等待40us后采样
    
    return DHT11_DQ_IN ? 1 : 0;
}

// 读取一个字节
rt_uint8_t DHT11_Read_Byte(void)
{
    rt_uint8_t i, dat = 0;
    
    for(i = 0; i < 8; i++) {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    
    return dat;
}

// 读取温湿度数据
rt_uint8_t DHT11_Read_Data(rt_uint8_t *temp, rt_uint8_t *humi)
{
    rt_uint8_t buf[5];
    rt_uint8_t i;
    
    DHT11_Rst();
    
    if(DHT11_Check() == 0) {
        for(i = 0; i < 5; i++) {
            buf[i] = DHT11_Read_Byte();
        }
        
        // 校验和验证
        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]) {
            *humi = buf[0];
            *temp = buf[2];
            return 0;
        }
    }
    
    return 1; // 读取失败
}

// 初始化DHT11
rt_uint8_t DHT11_Init(void)
{
    DHT11_Rst();
    return DHT11_Check();
}


rt_uint8_t temperature,humidity;  //温湿度变量

void Display_DHT11(void)
{
		DHT11_Read_Data(&temperature, &humidity);	//读取温湿度值
		//温湿度
		OLED_ShowChinese(10,45,0,16,1);//温
		OLED_ShowChinese(25,45,2,16,1);//度		  
		
		OLED_ShowNum(42,45,temperature,2,16,1); //值
		OLED_ShowString(60,45,"C",16,1); //C
		
		OLED_ShowChinese(70,45,1,16,1);//湿
		OLED_ShowChinese(85,45,2,16,1);//度
	
		OLED_ShowNum(102,45,humidity,2,16,1);   //值
		OLED_ShowString(120,45,"%",16,1);//%
	
		
}

