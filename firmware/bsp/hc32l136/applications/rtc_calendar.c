#include "rtc.h"
#include "oled.h"
#include "rtc_calendar.h"

// ȫ�ֱ����洢��ǰʱ��
stc_rtc_time_t g_stcCurrentTime;

// ��ǿ��BCDתʮ���ƣ���У�飩
uint8_t Safe_BCD_To_Dec(uint8_t bcd)
{
    // ȷ���ǺϷ���BCD��
    if(((bcd >> 4) > 9) || ((bcd & 0x0F) > 9)) return 0;
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// ��ʼ��RTC
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
    
    // ���ó�ʼʱ�䣨ע�⣺��������ǺϷ���BCD�룡��
    stcTimeDate.u8Second = 0x10;   // BCD���ʾ10��
    stcTimeDate.u8Minute = 0x01;   // BCD���ʾ01��
    stcTimeDate.u8Hour   = 0x11;   // BCD���ʾ21ʱ
    stcTimeDate.u8Day    = 0x15;   // BCD���ʾ27��
    stcTimeDate.u8Month  = 0x05;   // BCD���ʾ6��
    stcTimeDate.u8Year   = 0x25;   // BCD���ʾ2021��
    
    // RTC����
    stcRtcCfg.enClkSel = RtcClk32768;
    stcRtcCfg.enAmpmSel = Rtc24h;
    stcRtcCfg.pstcCycSel = &stcCycSel;
    stcRtcCfg.pstcTimeDate = &stcTimeDate;
    
    // �����ж�����
    stcCycSel.enCyc_sel = RtcPrads;
    stcCycSel.enPrds_sel = Rtc_1S;
    stcCycSel.u8Prdx = 0;
    
    Rtc_Init(&stcRtcCfg);
    Rtc_EnableFunc(RtcCount);
}

// ��ȷ����ʾ����
void Display_Time(void)
{
    // ��ȡRTCʱ��
    if(Ok != Rtc_ReadDateTime(&g_stcCurrentTime))
    {
        OLED_ShowString(0,50,"RTC READ ERR",8,1);
        return;
    }
    
    // ��ʾ�꣨2000-2099��
    OLED_ShowChinese(32,10,3,16,1);
    OLED_ShowNum(0,10,2000 + Safe_BCD_To_Dec(g_stcCurrentTime.u8Year),4,16,1);
    
    // ��ʾ�£�1-12��
    uint8_t month = Safe_BCD_To_Dec(g_stcCurrentTime.u8Month);
    month = (month < 1 || month > 12) ? 1 : month;
    OLED_ShowChinese(72,10,4,16,1);
    OLED_ShowNum(53,10,month,2,16,1);
    
    // ��ʾ�գ�1-31��
    uint8_t day = Safe_BCD_To_Dec(g_stcCurrentTime.u8Day);
    day = (day < 1 || day > 31) ? 1 : day;
    OLED_ShowChinese(112,10,5,16,1);
    OLED_ShowNum(93,10,day,2,16,1);
    
    // ��ʾʱ��
    uint8_t hour = Safe_BCD_To_Dec(g_stcCurrentTime.u8Hour);
    uint8_t minute = Safe_BCD_To_Dec(g_stcCurrentTime.u8Minute);
    uint8_t second = Safe_BCD_To_Dec(g_stcCurrentTime.u8Second);
    
    OLED_ShowNum(32,32,hour,2,12,1);
    OLED_ShowString(47,32,":",12,1);
    OLED_ShowNum(57,32,minute,2,12,1);
    OLED_ShowString(72,33,":",12,1);
    OLED_ShowNum(80,32,second,2,12,1);
    
   
}