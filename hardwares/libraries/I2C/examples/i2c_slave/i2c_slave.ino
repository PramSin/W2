#include <SYS.h>
#include <UART.h>
#include <I2C.h>


void setup() {
  // put your setup code here, to run once:
  I2cSlaveInit(I2C_SLAVE_ADR_MASK_1,I2C_SLAVE_IRQ_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int state;
  unsigned int i2c_bus_busy_bit,mem_wt,mem_rd;
  state = GetI2cBusState();

  i2c_bus_busy_bit = (I2C_BUS_BUSY_BIT & state);
  mem_rd = state & I2C_MEM_RD_BIT;
  mem_wt = state & I2C_MEM_WT_BIT;

  unsigned int adr,data;
  if( I2C_BUS_NOT_BUSY == i2c_bus_busy_bit )
  {
    if(mem_rd)
    {
      adr = I2cSlaveReadAdrReg();
      data = MemoryRead(adr);
      I2cSlvaeWrite(data);
      uart_puts("IS rd: ");
      uart_puts("Addr=");
      uart_puts(xtoa(adr));
      uart_puts("  Data=");
      uart_puts(xtoa(data));
      uart_puts("\n");
      I2cSlaveClearIrq();
    }
    if(mem_wt)
    {
      adr = I2cSlaveReadAdrReg();
      data = I2cSlaveReadDateReg();
      MemoryWrite(adr,data);
      uart_puts("IS wt: ");
      uart_puts("Addr=");
      uart_puts(xtoa(adr));
      uart_puts("  Data=");
      uart_puts(xtoa(data));
      uart_puts("\n");
      I2cSlaveClearIrq();
    }
  }
}
