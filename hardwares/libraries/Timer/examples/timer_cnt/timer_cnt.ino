#include <UART.h>
#include <Timer.h>

void setup() 
{
  // put your setup code here, to run once:
  char irq_is_enable;
  irq_is_enable = 0;                  //diable irq
  Timer0TimerModeInit(irq_is_enable); //init Timer0 is Timer count mode
  Timer0SetCnt(0x1000);               //set Timer0 cnt num is 0x1000
  Timer0ClkCfg(1);                    //set Timer0 clk is 6Mhz/(1 + 1);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(Timer0FlagIsOn())              //read timer0 Cnt flag if flag == 1,enter if
  {
    unsigned int num;
    num = GetTimer0CntNum();        //read cnt num
    uart_puts("\nTimer 0 cnt->");
    uart_puts((char*)xtoa(num));    //use serial print num
    Timer0ClearCntNum();            //clear cnt num in reg
    Timer0ClearIrq();               //clear timer0 cnt flag
  }

}
