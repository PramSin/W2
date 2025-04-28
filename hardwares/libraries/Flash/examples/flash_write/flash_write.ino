#include <UART.h>
#include <FLASH.h>

void setup() {
  // put your setup code here, to run once:
  unsigned int adr,data;
  adr = 0x10001000;                             //set a flash adr
  data = FlashRead(adr);                        //read flash
  uart_puts("flash ");                          //print data
  uart_puts(xtoa(adr));
  uart_puts("->");
  uart_puts(xtoa(data));
  uart_puts("\n");
  if(0xffffffff == data)                        //flash is empty,enter if
  {
    FlashUnlock();                              //unlock internal flash
    FlashWriteWord(adr,0x12345678);             //wt data to flash
    FlashLock();                                //lock flash
    uart_puts("wt 0x12345678->");               //print
    uart_puts(xtoa(adr));
  }
  else                                          //if flash isn't empty
  {
    FlashUnlock();                              //unlock internal flash
    FlashEraseSector(adr);                      //erase sector where adr belong
    uart_puts("erase flash 0x");
    uart_puts(xtoa(adr));
    uart_puts("\n");
    FlashWriteWord(adr,0x12345678);             //after erase, write data to flash
    FlashLock();                                //lock flash
    uart_puts("wt 0x12345678->");
    uart_puts(xtoa(adr));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
