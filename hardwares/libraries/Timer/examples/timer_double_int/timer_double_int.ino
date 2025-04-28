#include <SYS.h>
#include <UART.h>
#include <Timer.h>
extern "C"
{
  extern int g_timer0_int_flag;       //state global variable
  extern int g_timer1_int_flag;       //state global variable
  void user_interrupt()
  {
    if( SYS_T0_INT == (GetSysIntFlag() & SYS_T0_INT) )
    {
      //interrupt trigger by timer0 
      g_timer0_int_flag = 1;          //set timer0 interrupt flag
      Timer0ClearIrq();               //clear timer0 cnt flag
      StopTimer0Cnt();                //stop timer0
    }
    if( SYS_T1_INT == (GetSysIntFlag() & SYS_T1_INT) )
    {
      //interrupt trigger by timer1
      g_timer1_int_flag = 1;          //set timer1 interrupt flag
      Timer1ClearIrq();               //clear timer1 cnt flag
      StopTimer1Cnt();                //stop timer1
    }
    //exit interrupt
  }
}

int g_timer0_int_flag,g_timer1_int_flag;

void setup() 
{
  // put your setup code here, to run once:
  char irq_is_enable;
  irq_is_enable = 1;                  //enable irq
  g_timer0_int_flag = 0;              //init timer0 interrupt flag
  g_timer1_int_flag = 0;              //init timer1 interrupt flag
  EnableSysInterrupt();               //enable system interrupt
  Timer0TimerModeInit(irq_is_enable); //init Timer0 is Timer count mode
  Timer0SetCnt(0x800);                //set Timer0 cnt num is 0x800
  Timer0ClkCfg(0x1000);               //set Timer0 clk is 6Mhz/(1 + 0x1000);

  Timer1TimerModeInit(irq_is_enable); //init Timer1 is Timer count mode
  Timer1SetCnt(0x1000);               //set Timer1 cnt num is 0x1000
  Timer1ClkCfg(0x1000);               //set Timer1 clk is 6Mhz/(1 + 0x1000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if((0 == g_timer0_int_flag) && (0 == g_timer1_int_flag) )
  {
    //program doesn't enter the user_interrupt
    uart_puts("------------IDLE------------\n");
  }
  else
  {
    //program enter user_interrupt
    if (g_timer0_int_flag) 
    {
      //if timer0 flag = 1 enter if
      g_timer0_int_flag = 0;           //clear timer0 flag
      uart_puts("Timer0000000000\n");  //print
      Timer0ClearCntNum();             //clear timer0 cnt num in reg
      RestartTimer0Cnt();              //restart timer0
    } 
    if (g_timer1_int_flag) 
    {
      //if timer1 flag = 1 enter if
      g_timer1_int_flag = 0;           //clear timer1 flag
      uart_puts("Timer1111111111\n");  //print
      Timer1ClearCntNum();             //clear timer1 cnt num in reg
      RestartTimer1Cnt();              //restart timer1
    }

  }
}
