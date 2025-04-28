#ifndef __I2C_H__
#define __I2C_H__
//I2C主模式相关寄存器
#define I2C_MASTER_BASE_ADR                         (0x1f800d30)

#define IM_WRITE_REG                                (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 2))
#define IM_READ_REG                                 (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 0))
#define IM_DATA_RDY_REG                             (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 5))
#define IM_START_STOP_REG                           (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 6))
#define IM_CTL_REG                                  (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 4))
#define IM_CLRIRQ_REG                               (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 3))
#define IM_BUSY_REG                                 (*(volatile unsigned long *)(I2C_MASTER_BASE_ADR + 1))

//I2C从设备相关寄存器
#define I2C_SLAVE_BASE_ADR                          (0x1f800d20)

#define IS_WRITE_REG                                (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 2))
#define IS_READ_REG                                 (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 0))
#define IS_DATA_RDY_REG                             (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 5))
#define IS_CTL_REG                                  (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 4))
#define IS_CLRIRQ_REG                               (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 3))
#define IS_ADR_REG                                  (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 7))
#define IS_BUSY_REG                                 (*(volatile unsigned long *)(I2C_SLAVE_BASE_ADR + 1))

#define IS_READ_STATE_BIT                           (0xF)

#define I2C_CLK_360KHZ                              (0 << 1)
#define I2C_CLK_180KHZ                              (1 << 1)
#define I2C_CLK_90KHZ                               (2 << 1)
#define I2C_CLK_45KHZ                               (3 << 1)

#define I2C_MASTER_ON                               (1 << 3)
#define I2C_MASTER_IRQ_ON                           (1 << 0)
#define I2C_MASTER_IRQ_OFF                          (0 << 0)


#define I2C_SLAVE_ON                                (1 << 3)
#define I2C_SLAVE_IRQ_ON                            (1 << 0)
#define I2C_SLAVE_IRQ_OFF                           (0 << 0)
#define I2C_SLAVE_ADR_MASK_1                        (0xF << 4)
#define I2C_SLAVE_ADR_MASK_0                        (0xE << 4)

#define I2C_BUS_BUSY_BIT                            (1 << 31)
#define I2C_BUS_IS_BUSY                             (1 << 31)
#define I2C_BUS_NOT_BUSY                            (0 << 31)
#define I2C_MEM_RD_BIT                              (1 << 2)
#define I2C_MEM_WT_BIT                              (1 << 3)


#define I2C_WRITE                                   (0)
#define I2C_READ                                    (1)
#define ACK                                         (0)
#define NO_ACK                                      (1)
void I2cMasterInit(unsigned int clk,unsigned int irq);
void I2cMasterStart();
unsigned char I2cMasterWriteAdr(unsigned char adr,unsigned char w_or_r_bit);
unsigned char I2cMasterWriteData(unsigned char data);
unsigned char I2cMasterRead(unsigned char ack);
void I2cMasterStop();
unsigned char ReadAck();
unsigned char ReadData();
unsigned char MemWrite(unsigned char i2c_adr,unsigned int mem_adr,unsigned int mem_data);
unsigned char MemRead(unsigned char i2c_adr,unsigned int mem_adr,unsigned int *p_receive_data);
void I2cSlaveInit(unsigned int adr_mask,unsigned int irq);
void I2cSetSlaveAdr(unsigned char adr);
unsigned int GetI2cBusState();
unsigned int I2cSlaveReadAdrReg();
void I2cSlvaeWrite(unsigned int data);
unsigned int I2cSlaveReadDateReg();
void I2cSlaveClearIrq();
#endif