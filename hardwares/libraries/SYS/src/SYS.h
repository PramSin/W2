#ifndef __SYS_H__
#define __SYS_H__

#define SYS_CTL_BASE_ADR                            (0x1f800700)

#define SYS_CTL0_REG                               (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 0))
#define SYS_CTL1_REG                               (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 1))
#define SYS_CTL2_REG                               (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 2))
#define SYS_GDR_REG                                (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 3))
#define SYS_IOCTL_REG                              (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 4))
#define SYS_GPIO0_REG                              (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 5))
#define SYS_GPIO1_REG                              (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 6))
#define SYS_IRQ_REG                                (*(volatile unsigned long *)(SYS_CTL_BASE_ADR + 7))

#define MCLK_BIT                                    (3 << 12)
#define MCLK_48MHZ                                  (3 << 12)
#define MCLK_24MHZ                                  (2 << 12)
#define MCLK_12MHZ                                  (1 << 12)
#define MCLK_6MHZ                                   (0 << 12)

#define SYS_INT_EN_BIT                              (1 << 0)
#define SYS_DBG_EN_BIT                              (1 << 1)
#define SYS_DBGB_BIT                                (1 << 8)


#define SYS_U0_CMD_INT                              (1 << 0)
#define SYS_T0_INT                                  (1 << 1)
#define SYS_T1_INT                                  (1 << 2)
#define SYS_CCU_T0_INT                              (1 << 3)
#define SYS_DBG_INT                                 (1 << 4)
#define SYS_EXT_INT                                 (1 << 5)
#define SYS_WDT_INT                                 (1 << 6)
#define SYS_CCU_T1_INT                              (1 << 7)
#define SYS_ANA_INT                                 (1 << 8)
#define SYS_I2CM_INT                                (1 << 9)
#define SYS_DMI_INT                                 (1 << 10)
#define SYS_U0_DBG_INT                              (1 << 11)
#define SYS_U10_INT                                 (1 << 12)
#define SYS_SPI0_INT                                (1 << 13)
#define SYS_CCU_T2_INT                              (1 << 14)
#define SYS_I2CS_INT                                (1 << 15)


void EnableSysInterrupt();
void DisableSysInterrupt();
unsigned int GetSysIntFlag();
void CloseSysDgben();
void MemoryWrite(unsigned int adr,unsigned int data);
unsigned int MemoryRead(unsigned int adr);
void MyDelay(unsigned int cnt);

#endif