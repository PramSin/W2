#include "I2C.h"
#include "UART.h"
void I2cMasterInit(unsigned int clk,unsigned int irq)
{
    IM_CTL_REG = 0;
    switch (clk)
    {
        case I2C_CLK_360KHZ:
        case I2C_CLK_180KHZ:
        case I2C_CLK_90KHZ:
        case I2C_CLK_45KHZ:
            IM_CTL_REG |= clk;
            break;
    
        default:
            break;
    }
    switch (irq)
    {
        case I2C_MASTER_IRQ_ON:
        case I2C_MASTER_IRQ_OFF:
            IM_CTL_REG |= irq;
            break;
        default:
            break;
    }
    IM_CTL_REG |= I2C_MASTER_ON;
}

void I2cMasterStart()
{
    while((IM_BUSY_REG & 0x1)); //等待I2C总线空闲
    IM_START_STOP_REG = 1;      //I2C起始结束寄存器写入1
}
unsigned char ReadAck()
{
    while (!(IM_DATA_RDY_REG & 0x1));   //等待读取标志位
    while((IM_BUSY_REG & 0x1));         //等待总线空闲
    return IM_READ_REG;                 //读取寄存器数据并返回
}
unsigned char I2cMasterWriteAdr(unsigned char adr,unsigned char w_or_r_bit)
{
    while((IM_BUSY_REG & 0x1));
    IM_WRITE_REG = (adr << 1) | w_or_r_bit;
    return ReadAck();
}

unsigned char I2cMasterWriteData(unsigned char data)
{
    while((IM_BUSY_REG & 0x1));
    IM_WRITE_REG = data;
    return ReadAck();
}
unsigned char I2cMasterRead(unsigned char ack)
{
    while((IM_BUSY_REG & 0x1));
    IM_READ_REG = ack;          //产生CLK信号
    return ReadData();
}
unsigned char ReadData()
{
    while (!(IM_DATA_RDY_REG & 0x1));
    while((IM_BUSY_REG & 0x1));
    return IM_READ_REG;  
}
void I2cMasterStop()
{
    while((IM_BUSY_REG & 0x1));
    IM_START_STOP_REG = 0;
    while((IM_BUSY_REG & 0x1));
}
unsigned char MemRead(unsigned char i2c_adr,unsigned int mem_adr,unsigned int *p_receive_data)
{
  unsigned char ret_state,ack;
  I2cMasterStart();
  ack = I2cMasterWriteAdr(i2c_adr,I2C_WRITE);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  unsigned char adr_0,adr_1,adr_2,adr_3;
  unsigned char data_0,data_1,data_2,data_3;

  adr_3 = ( ( mem_adr & (0xff << 24) ) >> 24 );
  adr_2 = ( ( mem_adr & (0xff << 16) ) >> 16 );
  adr_1 = ( ( mem_adr & (0xff << 8) ) >> 8 );
  adr_0 = ( ( mem_adr & (0xff << 0) ) >> 0 );

  ack = I2cMasterWriteData(adr_0);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(adr_1);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(adr_2);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(adr_3);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  I2cMasterStop();

  I2cMasterStart();
  ack = I2cMasterWriteAdr(0x8,I2C_WRITE);
    if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(0x1);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  I2cMasterStop();

  I2cMasterStart();
  ack = I2cMasterWriteAdr(i2c_adr,I2C_READ);
    if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  data_0 = I2cMasterRead(ACK);
  data_1 = I2cMasterRead(ACK);
  data_2 = I2cMasterRead(ACK);
  data_3 = I2cMasterRead(NO_ACK);
  unsigned int ret_data;
  *p_receive_data = (data_3 << 24) | (data_2 << 16) | (data_1 << 8) | data_0;

  I2cMasterStop();

  return ret_state;
}

unsigned char MemWrite(unsigned char i2c_adr,unsigned int mem_adr,unsigned int mem_data)
{
  unsigned char ret_state,ack;
  ret_state = 0;
  I2cMasterStart();

  ack = I2cMasterWriteAdr(i2c_adr,I2C_WRITE);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  unsigned char adr_0,adr_1,adr_2,adr_3;
  unsigned char data_0,data_1,data_2,data_3;

  adr_3 = ( ( mem_adr & (0xff << 24) ) >> 24 );
  adr_2 = ( ( mem_adr & (0xff << 16) ) >> 16 );
  adr_1 = ( ( mem_adr & (0xff << 8) ) >> 8 );
  adr_0 = ( ( mem_adr & (0xff << 0) ) >> 0 );

  data_3 = ( ( mem_data & (0xff << 24) ) >> 24 );
  data_2 = ( ( mem_data & (0xff << 16) ) >> 16 );
  data_1 = ( ( mem_data & (0xff << 8) ) >> 8 );
  data_0 = ( ( mem_data & (0xff << 0) ) >> 0 );

  ack = I2cMasterWriteData(adr_0);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(adr_1);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(adr_2);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(adr_3);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  ack = I2cMasterWriteData(data_0);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(data_1);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(data_2);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }

  ack = I2cMasterWriteData(data_3);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
    ack = I2cMasterWriteData(0x2);
  if(0 != ack)
  {
    uart_puts("error\n");
    ret_state = 1;
    return ret_state;
  }
  I2cMasterStop();
  return ret_state;
}

void I2cSlaveInit(unsigned int adr_mask,unsigned int irq)
{
    IS_CTL_REG = 0;
    if( (I2C_SLAVE_ADR_MASK_1 == adr_mask) || (I2C_SLAVE_ADR_MASK_0 == adr_mask) )
    {
        IS_CTL_REG |= adr_mask;
    }
    if( (I2C_SLAVE_IRQ_ON == irq) || (I2C_SLAVE_IRQ_OFF == irq) )
    {
        IS_CTL_REG |= irq;
    }
    IS_CTL_REG |= I2C_SLAVE_ON;
}

void I2cSetSlaveAdr(unsigned char adr)
{
    IS_ADR_REG = adr;
}
unsigned int GetI2cBusState()
{
    return IS_DATA_RDY_REG; 
}
unsigned int I2cSlaveReadAdrReg()
{
    return IS_READ_REG;
}
void I2cSlvaeWrite(unsigned int data)
{
    IS_WRITE_REG = data;
}
unsigned int I2cSlaveReadDateReg()
{
    return IS_WRITE_REG;

}
void I2cSlaveClearIrq()
{
    IS_CLRIRQ_REG = 1;
}