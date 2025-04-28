#include <SYS.h>
#include <UART.h>
#include <I2C.h>


void setup() {
  // put your setup code here, to run once:
  I2cMasterInit(I2C_CLK_360KHZ,I2C_MASTER_IRQ_OFF);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int receive_data;
  unsigned int adr, data;
  adr = 0x01000010;
  data = 0x12345678;
  MemWrite(0x00,adr,data);
  uart_puts("IM wt: ");
  uart_puts("Addr=");
  uart_puts(xtoa(adr));
  uart_puts("  Data=");
  uart_puts(xtoa(data));
  uart_puts("\n");
  MyDelay(10000);
  MemRead(0x00,adr,&receive_data);
  uart_puts("IM rd: ");
  uart_puts("Addr=");
  uart_puts(xtoa(adr));
  uart_puts("  Data=");
  uart_puts(xtoa(receive_data));
  uart_puts("\n");
  MyDelay(10000);

}
