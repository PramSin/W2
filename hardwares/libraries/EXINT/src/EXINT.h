#ifndef __EXINT_H__
#define __EXINT_H__

#define EXINT_BASE_ADR                              (0x1f800500)
#define EXINT_CTL0_REG                              (*(volatile unsigned long *)(EXINT_BASE_ADR + 0))
#define EXINT_READ_REG                              (*(volatile unsigned long *)(EXINT_BASE_ADR + 1))
#define EXINT_SET_REG                               (*(volatile unsigned long *)(EXINT_BASE_ADR + 2))
#define EXINT_CLR_REG                               (*(volatile unsigned long *)(EXINT_BASE_ADR + 3))

#define EXINT_0                                     (1 << 0)
#define EXINT_1                                     (1 << 1)
#define INT_0_BIT                                   (1 << 0)
#define INT_1_BIT                                   (1 << 1)
#define INT_0_FALL_BIT                              (0)
#define INT_1_FALL_BIT                              (0)
#define INT_0_RAIS_BIT                              (1 << 0)
#define INT_1_RAIS_BIT                              (1 << 1)

void ExintInit(char int_id,char fall_or_rais_trig);
void ClearExintAllIrq();
void ClearExintIrq(char int_id);
char GetExintIrqId();

#endif