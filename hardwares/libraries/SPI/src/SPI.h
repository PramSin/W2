#ifndef __SPI_H__
#define __SPI_H__

#define SPI_REG_BASE_ADR                            (0x1F800D00)
#define SPI_READ_REG                                (*(volatile unsigned long *)(SPI_REG_BASE_ADR + 0))
#define SPI_BUSY_REG                                (*(volatile unsigned long *)(SPI_REG_BASE_ADR + 1))
#define SPI_WRITE_REG                               (*(volatile unsigned long *)(SPI_REG_BASE_ADR + 2))
#define SPI_CLRIRQ_REG                              (*(volatile unsigned long *)(SPI_REG_BASE_ADR + 3))
#define SPI_CTL_REG                                 (*(volatile unsigned long *)(SPI_REG_BASE_ADR + 4))
#define SPI_DATARDY_REG                             (*(volatile unsigned long *)(SPI_REG_BASE_ADR + 5))

#define SPI_ENABLE_BIT          				    (1 << 3)
#define SPI_MASTER_EN_BIT       				    (1 << 2)
#define SPI_SLAVE_EN_BIT       				        (0 << 2)
#define SPI_CS_ON_BIT           				    (1 << 1)
#define SPI_IRQ_EN_BIT          				    (1 << 0)

#define SPI_CPOL_BIT          				        (1 << 5)
#define SPI_CPHA_BIT          				        (1 << 4)
#define SPI_CLK_FAST                                (0 << 6)
#define SPI_CLK_1_2                                 (1 << 6)
#define SPI_CLK_1_4                                 (2 << 6)
#define SPI_CLK_SLOW                                (3 << 6)

void SpiClearIrq();
void SpiMasterInit();
unsigned char SpiTxBusy();
void SpiWriteByte(unsigned char byte);
void SpiCsOn();
void SpiCsOff();
void SpiSlaveInit();
void SpiSetCpolAndCpha(char cpol,char cpha);
void SpiMasterSetClk(unsigned char clk);
unsigned char SpiReceiveDataIsReady();
unsigned char SpiReceiveData();

#endif