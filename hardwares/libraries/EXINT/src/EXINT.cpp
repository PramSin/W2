#include "EXINT.h"

void ExintInit(char int_id,char fall_or_rais_trig)
{
    int_id &= (INT_0_BIT | INT_1_BIT);
    EXINT_CTL0_REG = int_id;
    fall_or_rais_trig &= (INT_0_RAIS_BIT | INT_1_RAIS_BIT);
    EXINT_SET_REG = fall_or_rais_trig;
}

void ClearExintAllIrq()
{
    EXINT_CLR_REG = (INT_0_BIT | INT_1_BIT);
}

void ClearExintIrq(char int_id)
{
    int_id &= (INT_0_BIT | INT_1_BIT);
    EXINT_CLR_REG = int_id;
}

char GetExintIrqId()
{
    return EXINT_READ_REG;
}