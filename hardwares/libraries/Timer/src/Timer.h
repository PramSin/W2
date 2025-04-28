#ifndef __TIMER_H__
#define __TIMER_H__

#define T0_REG_BASE_ADR                             (0x1F800100)
#define T0_CTL0_REG                                 (*(volatile unsigned long *)(T0_REG_BASE_ADR + 0))
#define T0_REF_REG                                  (*(volatile unsigned long *)(T0_REG_BASE_ADR + 1))
#define T0_READ_REG                                 (*(volatile unsigned long *)(T0_REG_BASE_ADR + 2))
#define T0_CLRIRQ_REG                               (*(volatile unsigned long *)(T0_REG_BASE_ADR + 3))
#define T0_CLK_REG                                  (*(volatile unsigned long *)(T0_REG_BASE_ADR + 4))
#define T0_CLRCNT_REG                               (*(volatile unsigned long *)(T0_REG_BASE_ADR + 5))
#define T0_PWMPH_REG                                (*(volatile unsigned long *)(T0_REG_BASE_ADR + 6))
#define T0_CLRPWM_REG                               (*(volatile unsigned long *)(T0_REG_BASE_ADR + 7))

#define T1_REG_BASE_ADR                             (0x1F800800)
#define T1_CTL0_REG                                 (*(volatile unsigned long *)(T1_REG_BASE_ADR + 0))
#define T1_REF_REG                                  (*(volatile unsigned long *)(T1_REG_BASE_ADR + 1))
#define T1_READ_REG                                 (*(volatile unsigned long *)(T1_REG_BASE_ADR + 2))
#define T1_CLRIRQ_REG                               (*(volatile unsigned long *)(T1_REG_BASE_ADR + 3))
#define T1_CLK_REG                                  (*(volatile unsigned long *)(T1_REG_BASE_ADR + 4))
#define T1_CLRCNT_REG                               (*(volatile unsigned long *)(T1_REG_BASE_ADR + 5))
#define T1_PWMPH_REG                                (*(volatile unsigned long *)(T1_REG_BASE_ADR + 6))
#define T1_CLRPWM_REG                               (*(volatile unsigned long *)(T1_REG_BASE_ADR + 7))

#define T4_REG_BASE_ADR                             (0x1F800b00)
#define T4_CTL0_REG                                 (*(volatile unsigned long *)(T1_REG_BASE_ADR + 0))
#define T4_REF0_REG                                 (*(volatile unsigned long *)(T1_REG_BASE_ADR + 1))
#define T4_REF1_REG                                 (*(volatile unsigned long *)(T1_REG_BASE_ADR + 2))
#define T4_CLRIRQ_REG                               (*(volatile unsigned long *)(T1_REG_BASE_ADR + 3))
#define T4_WDTCNT_REG                               (*(volatile unsigned long *)(T1_REG_BASE_ADR + 4))
#define T4_IO2_CTL_REG                              (*(volatile unsigned long *)(T1_REG_BASE_ADR + 5))
#define T4_IO2_OUT_REG                              (*(volatile unsigned long *)(T1_REG_BASE_ADR + 6))
#define T4_EF_LOCK_REG                              (*(volatile unsigned long *)(T1_REG_BASE_ADR + 7))

#define TIMER_ECNT_BIT                              (1 << 0)
#define TIMER_BIT                                   (1 << 1)
#define TIMER_RISE_BIT                              (1 << 2)
#define TIMER_PWMM_BIT                              (1 << 3)
#define TIMER_PWM0_BIT                              (1 << 4)
#define TIMER_OCEN_BIT                              (1 << 5)
#define TIMER_PWMIRQ_BIT                            (1 << 6)
#define TIMER_IRQEN_BIT                             (1 << 7)
#define TIMER_PWM_FLAG_BIT                          (1 << 30)
#define TIMER_TC_FLAG_BIT                           (1 << 31)
/*Timer0 Lib Fxn*/
void Timer0TimerModeInit(char int_enable);
void Timer0SetCnt(unsigned short num);
unsigned int GetTimer0CntNum();
void Timer0ClearIrq();
void Timer0ClkCfg(unsigned short num);
void Timer0ClearCntNum();
unsigned char Timer0FlagIsOn();
void StopTimer0Cnt();
void RestartTimer0Cnt();
/*Timer1 Lib Fxn*/
void Timer1TimerModeInit(char int_enable);
void Timer1SetCnt(unsigned short num);
unsigned int GetTimer1CntNum();
void Timer1ClearIrq();
void Timer1ClkCfg(unsigned short num);
void Timer1ClearCntNum();
unsigned char Timer1FlagIsOn();
void StopTimer1Cnt();
void RestartTimer1Cnt();



#endif