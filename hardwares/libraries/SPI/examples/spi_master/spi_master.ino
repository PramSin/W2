#include <UART.h>
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  SpiMasterInit();                                //init as master mode
  SpiMasterSetClk(SPI_CLK_SLOW);                  //set spi clk = sys_clk / 8
  uart_puts("SPI MASTER EXAMPLE START\n");        //print
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char data = GetChar();                 //wait for user use u0 input one ascii code
  SpiCsOn();                                      //put down spi cs pin
  SpiWriteByte(data);                             //use spi mosi pin output data
  // SpiCsOff();                                     //pull up spi cs pin
  SpiClearIrq();
  uart_puts("\nSPI MASTER SEND ->");              //print user input ascii code
  UartPutChar(data);
}
