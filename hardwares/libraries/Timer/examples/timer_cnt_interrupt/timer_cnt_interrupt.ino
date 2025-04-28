#include <SYS.h>
#include <UART.h>
#include <Timer.h>
extern "C"
{
  extern int g_timer0_int_flag;       //state global variable
  void user_interrupt()
  {
    if( SYS_T0_INT == (GetSysIntFlag() & SYS_T0_INT) )
    {
      //interrupt trigger by timer0 
      g_timer0_int_flag = 1;          //set timer0 interrupt flag
      Timer0ClearIrq();               //clear timer0 cnt flag
      StopTimer0Cnt();                //stop timer
    }
    //exit interrupt
  }
}
int g_timer0_int_flag;

void setup() 
{
  // put your setup code here, to run once:
  char irq_is_enable;
  irq_is_enable = 1;                  //enable irq
  g_timer0_int_flag = 0;
  EnableSysInterrupt();               //enable system interrupt
  Timer0TimerModeInit(irq_is_enable); //init Timer0 is Timer count mode
  Timer0SetCnt(0x1000);               //set Timer0 cnt num is 0x1000
  Timer0ClkCfg(0x1000);               //set Timer0 clk is 6Mhz/(1 + 0x1000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(g_timer0_int_flag)                     //if interrupt change flag = 1 enter if
  {
    g_timer0_int_flag = 0;                  //clear interrupt flag
    uart_puts("Timer0 enter interrupt\n");  //print
    Timer0ClearCntNum();                    //clear cnt num in reg
    RestartTimer0Cnt();                     //restart timer0
  }
  else
  {
    //program doesn't enter the user_interrupt
    uart_puts("------------IDLE------------\n");
  }

}
