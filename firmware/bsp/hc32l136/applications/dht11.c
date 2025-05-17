#include "dht11.h"
#include "gpio.h"
#include "oled.h"

// ����GPIOΪ���ģʽ
void DHT11_IO_OUT(void)
{
    stc_gpio_config_t gpio_init;
    
    // ��ʼ�����ýṹ��
    DDL_ZERO_STRUCT(gpio_init);
    
    gpio_init.enDir = GpioDirOut;      // ���ģʽ
    gpio_init.enDrv = GpioDrvH;        // ����������
    gpio_init.enPuPd = GpioNoPuPd; // ��������
    gpio_init.enOD = GpioOdDisable;     // ��ֹ��©���
    
    // ��ʼ��GPIO
    Gpio_Init(DHT11_PORT, DHT11_PIN, &gpio_init);
}

// ����GPIOΪ����ģʽ
void DHT11_IO_IN(void)
{
    stc_gpio_config_t gpio_init;
    
    // ��ʼ�����ýṹ��
    DDL_ZERO_STRUCT(gpio_init);
    
    gpio_init.enDir = GpioDirIn;       // ����ģʽ
    gpio_init.enPuPd = GpioNoPuPd; // ��������
    
    // ��ʼ��GPIO
    Gpio_Init(DHT11_PORT, DHT11_PIN, &gpio_init);
}

// ��λDHT11
void DHT11_Rst(void)
{
    DHT11_IO_OUT();     // ����Ϊ���ģʽ
    DHT11_DQ_OUT(FALSE); // ����DQ
    delay1ms(20);       // ��������18ms
    DHT11_DQ_OUT(TRUE);  // �ͷ�����
    delay10us(3);       // ��������20~40us
}

// ���DHT11��Ӧ
rt_uint8_t DHT11_Check(void)
{
    rt_uint8_t retry = 0;
    DHT11_IO_IN();      // ����Ϊ����ģʽ
    
    // �ȴ�DHT11���ͣ���ʱ100us��
    while(DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    if(retry >= 100) return 1;
    
    retry = 0;
    // �ȴ�DHT11���ߣ���ʱ100us��
    while(!DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    if(retry >= 100) return 1;
    
    return 0;
}

// ��ȡһ��λ
rt_uint8_t DHT11_Read_Bit(void)
{
    rt_uint8_t retry = 0;
    
    // �ȴ��͵�ƽ��DHT11��ʼ����λ��
    while(DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    
    retry = 0;
    // �ȴ��ߵ�ƽ
    while(!DHT11_DQ_IN && (retry < 100)) {
        retry++;
        delay10us(1);
    }
    
    delay10us(4); // �ȴ�40us�����
    
    return DHT11_DQ_IN ? 1 : 0;
}

// ��ȡһ���ֽ�
rt_uint8_t DHT11_Read_Byte(void)
{
    rt_uint8_t i, dat = 0;
    
    for(i = 0; i < 8; i++) {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    
    return dat;
}

// ��ȡ��ʪ������
rt_uint8_t DHT11_Read_Data(rt_uint8_t *temp, rt_uint8_t *humi)
{
    rt_uint8_t buf[5];
    rt_uint8_t i;
    
    DHT11_Rst();
    
    if(DHT11_Check() == 0) {
        for(i = 0; i < 5; i++) {
            buf[i] = DHT11_Read_Byte();
        }
        
        // У�����֤
        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]) {
            *humi = buf[0];
            *temp = buf[2];
            return 0;
        }
    }
    
    return 1; // ��ȡʧ��
}

// ��ʼ��DHT11
rt_uint8_t DHT11_Init(void)
{
    DHT11_Rst();
    return DHT11_Check();
}


rt_uint8_t temperature,humidity;  //��ʪ�ȱ���

void Display_DHT11(void)
{
		DHT11_Read_Data(&temperature, &humidity);	//��ȡ��ʪ��ֵ
		//��ʪ��
		OLED_ShowChinese(10,45,0,16,1);//��
		OLED_ShowChinese(25,45,2,16,1);//��		  
		
		OLED_ShowNum(42,45,temperature,2,16,1); //ֵ
		OLED_ShowString(60,45,"C",16,1); //C
		
		OLED_ShowChinese(70,45,1,16,1);//ʪ
		OLED_ShowChinese(85,45,2,16,1);//��
	
		OLED_ShowNum(102,45,humidity,2,16,1);   //ֵ
		OLED_ShowString(120,45,"%",16,1);//%
	
		
}

