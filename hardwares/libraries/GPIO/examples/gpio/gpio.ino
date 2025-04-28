#include <UART.h>
#include <GPIO.h>
/*user should use line connect io[0] and io[1]*/
void setup() 
{
  // put your setup code here, to run once:
  GpioSetPinOutput(IO_ID_0);                              //set io[0] as output
  GpioSetPinInput(IO_ID_1);                               //set io[1] as input
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  int i;
  for(i = 0;i < 50;i++)
  {
    if(i < 25)  
    {
      SetPinOutputHighOrLow(IO_ID_0,IO_OUT_HIGH);       //set io[0] output high
    }
    else
    {
      SetPinOutputHighOrLow(IO_ID_0,IO_OUT_LOW);        //set io[0] output low
    }
    uart_puts("\nIO_0 OUT->");
    uart_puts((char*)xtoa(ReadPinInputValue(IO_ID_1))); //read io[1] input value
  }
}
