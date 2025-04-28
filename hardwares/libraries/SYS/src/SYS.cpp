#include "SYS.h"

void EnableSysInterrupt()
{
    SYS_CTL0_REG |= SYS_INT_EN_BIT; 
}
void DisableSysInterrupt()
{
    SYS_CTL0_REG &= ~(SYS_INT_EN_BIT);
}

unsigned int GetSysIntFlag()
{
    return SYS_IRQ_REG;
}
void CloseSysDgben()
{
    SYS_CTL0_REG |= SYS_DBGB_BIT;
}

void MemoryWrite(unsigned int adr,unsigned int data)
{
    (*(volatile unsigned int*)(adr)) = data;
}

unsigned int MemoryRead(unsigned int adr)
{
    return (*(volatile unsigned int*)(adr));
}

void MyDelay(unsigned int cnt)
{
    while(cnt--);
}