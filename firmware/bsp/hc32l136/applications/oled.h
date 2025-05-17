#ifndef __OLED_H
#define __OLED_H 


#include "rtdef.h"
#include "gpio.h"

//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() Gpio_ClrIO(GpioPortA,GpioPin8)//SCL   PA8
#define OLED_SCL_Set() Gpio_SetIO(GpioPortA,GpioPin8)

#define OLED_SDA_Clr() Gpio_ClrIO(GpioPortA,GpioPin9)//SDA   PA9
#define OLED_SDA_Set() Gpio_SetIO(GpioPortA,GpioPin9)

#define OLED_RES_Clr() Gpio_ClrIO(GpioPortA,GpioPin10)//RES   PA10
#define OLED_RES_Set() Gpio_SetIO(GpioPortA,GpioPin10)


#define OLED_DC_Clr()  Gpio_ClrIO(GpioPortA,GpioPin11)//DC    PA11
#define OLED_DC_Set()  Gpio_SetIO(GpioPortA,GpioPin11)

#define OLED_CS_Clr()  Gpio_ClrIO(GpioPortA,GpioPin4) //CS?
#define OLED_CS_Set()  Gpio_SetIO(GpioPortA,GpioPin4)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(rt_uint8_t x,rt_uint8_t y);
void OLED_ColorTurn(rt_uint8_t i);
void OLED_DisplayTurn(rt_uint8_t i);
void OLED_WR_Byte(rt_uint8_t dat,rt_uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(rt_uint8_t x,rt_uint8_t y,rt_uint8_t t);
void OLED_DrawLine(rt_uint8_t x1,rt_uint8_t y1,rt_uint8_t x2,rt_uint8_t y2,rt_uint8_t mode);
void OLED_DrawCircle(rt_uint8_t x,rt_uint8_t y,rt_uint8_t r);
void OLED_ShowChar(rt_uint8_t x,rt_uint8_t y,rt_uint8_t chr,rt_uint8_t size1,rt_uint8_t mode);
void OLED_ShowChar6x8(rt_uint8_t x,rt_uint8_t y,rt_uint8_t chr,rt_uint8_t mode);
void OLED_ShowString(rt_uint8_t x,rt_uint8_t y,rt_uint8_t *chr,rt_uint8_t size1,rt_uint8_t mode);
void OLED_ShowNum(rt_uint8_t x,rt_uint8_t y,rt_uint32_t num,rt_uint8_t len,rt_uint8_t size1,rt_uint8_t mode);
void OLED_ShowChinese(rt_uint8_t x,rt_uint8_t y,rt_uint8_t num,rt_uint8_t size1,rt_uint8_t mode);
void OLED_ScrollDisplay(rt_uint8_t num,rt_uint8_t space,rt_uint8_t mode);
void OLED_ShowPicture(rt_uint8_t x,rt_uint8_t y,rt_uint8_t sizex,rt_uint8_t sizey,rt_uint8_t BMP[],rt_uint8_t mode);
void OLED_Init(void);

#endif

