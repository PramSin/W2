#include "Timer.h"

void Timer0TimerModeInit(char int_enable)
{
    if(int_enable)
    {
        T0_CTL0_REG = TIMER_BIT | TIMER_IRQEN_BIT;
    }
    else
    {
        T0_CTL0_REG = TIMER_BIT;
    }
}
void Timer0SetCnt(unsigned short num)
{
    T0_REF_REG = num;
}

unsigned int GetTimer0CntNum()
{
    return T0_READ_REG;
}

void Timer0ClearIrq()
{
    T0_CLRIRQ_REG = 1;
}
void Timer0ClkCfg(unsigned short num)
{
    T0_CLK_REG = num;
}

void Timer0ClearCntNum()
{
    T0_CLRCNT_REG = 1;
}

unsigned char Timer0FlagIsOn()
{
    unsigned char flag;
    flag = 0;
    if( (T0_CTL0_REG & TIMER_TC_FLAG_BIT) == TIMER_TC_FLAG_BIT)
    {
        flag = 1;
    }
    return flag;
}

void StopTimer0Cnt()
{
    T0_CTL0_REG &= ~(TIMER_BIT);
}

void RestartTimer0Cnt()
{
    T0_CTL0_REG |= TIMER_BIT;
}

void Timer1TimerModeInit(char int_enable)
{
    if(int_enable)
    {
        T1_CTL0_REG = TIMER_BIT | TIMER_IRQEN_BIT;
    }
    else
    {
        T1_CTL0_REG = TIMER_BIT;
    }
}
void Timer1SetCnt(unsigned short num)
{
    T1_REF_REG = num;
}

unsigned int GetTimer1CntNum()
{
    return T1_READ_REG;
}

void Timer1ClearIrq()
{
    T1_CLRIRQ_REG = 1;
}
void Timer1ClkCfg(unsigned short num)
{
    T1_CLK_REG = num;
}

void Timer1ClearCntNum()
{
    T1_CLRCNT_REG = 1;
}

unsigned char Timer1FlagIsOn()
{
    unsigned char flag;
    flag = 0;
    if( (T1_CTL0_REG & TIMER_TC_FLAG_BIT) == TIMER_TC_FLAG_BIT)
    {
        flag = 1;
    }
    return flag;
}

void StopTimer1Cnt()
{
    T1_CTL0_REG &= ~(TIMER_BIT);
}

void RestartTimer1Cnt()
{
    T1_CTL0_REG |= TIMER_BIT;
}
