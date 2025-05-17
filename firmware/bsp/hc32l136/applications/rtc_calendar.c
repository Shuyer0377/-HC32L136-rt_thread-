#include "rtc.h"
#include "oled.h"
#include "rtc_calendar.h"

// 全局变量存储当前时间
stc_rtc_time_t g_stcCurrentTime;

// 增强型BCD转十进制（带校验）
uint8_t Safe_BCD_To_Dec(uint8_t bcd)
{
    // 确保是合法的BCD码
    if(((bcd >> 4) > 9) || ((bcd & 0x0F) > 9)) return 0;
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// 初始化RTC
void RTC_Init_Config(void)
{
    stc_rtc_config_t stcRtcCfg;
    stc_rtc_cyc_sel_t stcCycSel;
    stc_rtc_time_t stcTimeDate;
    
    DDL_ZERO_STRUCT(stcRtcCfg);
    DDL_ZERO_STRUCT(stcCycSel);
    DDL_ZERO_STRUCT(stcTimeDate);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralRtc,TRUE);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);
    
    // 设置初始时间（注意：这里必须是合法的BCD码！）
    stcTimeDate.u8Second = 0x10;   // BCD码表示10秒
    stcTimeDate.u8Minute = 0x01;   // BCD码表示01分
    stcTimeDate.u8Hour   = 0x11;   // BCD码表示21时
    stcTimeDate.u8Day    = 0x15;   // BCD码表示27日
    stcTimeDate.u8Month  = 0x05;   // BCD码表示6月
    stcTimeDate.u8Year   = 0x25;   // BCD码表示2021年
    
    // RTC配置
    stcRtcCfg.enClkSel = RtcClk32768;
    stcRtcCfg.enAmpmSel = Rtc24h;
    stcRtcCfg.pstcCycSel = &stcCycSel;
    stcRtcCfg.pstcTimeDate = &stcTimeDate;
    
    // 周期中断配置
    stcCycSel.enCyc_sel = RtcPrads;
    stcCycSel.enPrds_sel = Rtc_1S;
    stcCycSel.u8Prdx = 0;
    
    Rtc_Init(&stcRtcCfg);
    Rtc_EnableFunc(RtcCount);
}

// 正确的显示函数
void Display_Time(void)
{
    // 读取RTC时间
    if(Ok != Rtc_ReadDateTime(&g_stcCurrentTime))
    {
        OLED_ShowString(0,50,"RTC READ ERR",8,1);
        return;
    }
    
    // 显示年（2000-2099）
    OLED_ShowChinese(32,10,3,16,1);
    OLED_ShowNum(0,10,2000 + Safe_BCD_To_Dec(g_stcCurrentTime.u8Year),4,16,1);
    
    // 显示月（1-12）
    uint8_t month = Safe_BCD_To_Dec(g_stcCurrentTime.u8Month);
    month = (month < 1 || month > 12) ? 1 : month;
    OLED_ShowChinese(72,10,4,16,1);
    OLED_ShowNum(53,10,month,2,16,1);
    
    // 显示日（1-31）
    uint8_t day = Safe_BCD_To_Dec(g_stcCurrentTime.u8Day);
    day = (day < 1 || day > 31) ? 1 : day;
    OLED_ShowChinese(112,10,5,16,1);
    OLED_ShowNum(93,10,day,2,16,1);
    
    // 显示时间
    uint8_t hour = Safe_BCD_To_Dec(g_stcCurrentTime.u8Hour);
    uint8_t minute = Safe_BCD_To_Dec(g_stcCurrentTime.u8Minute);
    uint8_t second = Safe_BCD_To_Dec(g_stcCurrentTime.u8Second);
    
    OLED_ShowNum(32,32,hour,2,12,1);
    OLED_ShowString(47,32,":",12,1);
    OLED_ShowNum(57,32,minute,2,12,1);
    OLED_ShowString(72,33,":",12,1);
    OLED_ShowNum(80,32,second,2,12,1);
    
   
}