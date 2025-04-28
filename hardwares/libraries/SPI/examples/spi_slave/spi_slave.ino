#include <UART.h>
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  SpiSlaveInit();                                 //init as slave mode
  uart_puts("SPI SLAVE EXAMPLE START\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SpiReceiveDataIsReady())                     //ready receive finsh flag,if fxn return 1 enter if
  {
    //receive one byte data
    unsigned char data;
    data = SpiReceiveData();                      //read receive one byte data               
    uart_puts("\nSPI SLAVE RECEIVE->");
    UartPutChar(data);                            //print data as ascii code
  }
  // uart_puts((char*)xtoa(SpiReceiveDataIsReady()));
  // uart_puts("\n");
}
