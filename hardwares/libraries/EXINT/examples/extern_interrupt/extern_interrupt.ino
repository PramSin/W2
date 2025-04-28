#include <EXINT.h>
#include <SYS.h>
#include <UART.h>

extern "C"
{
  extern int g_extern_int0_flag;       //state global variable
  extern int g_extern_int1_flag;       //state global variable
  void user_interrupt()
  {
    if( SYS_EXT_INT == (GetSysIntFlag() & SYS_EXT_INT) )
    {
      //interrupt trigger by extern interrupt
      if( INT_0_BIT == (GetExintIrqId() & INT_0_BIT) ) 
      {
        //if trigger by int0
        g_extern_int0_flag = 1;               //set int0 interrupt flag
        ClearExintIrq(EXINT_0);               //clear int0 irq
      }
      if( INT_1_BIT == (GetExintIrqId() & INT_1_BIT) )
      {
        //if trigger by int1
        g_extern_int1_flag = 1;               //set int1 interrupt flag
        ClearExintIrq(EXINT_1);               //clear int1 irq
      }
    }
    //exit interrupt
  }
}

int g_extern_int0_flag,g_extern_int1_flag;

void setup() 
{
  // put your setup code here, to run once:
  char int_id,int_trigger_type;
  int_id            = EXINT_0 | EXINT_1;                  //set exint id is int0 and int1
  int_trigger_type  = INT_0_RAIS_BIT | INT_1_FALL_BIT;    //set int0 trigger by rais edge,int1 trigger by fall edge
  g_extern_int0_flag = 0;                                 //init int0 interrupt flag
  g_extern_int1_flag = 0;                                 //init int1 interrupt flag
  EnableSysInterrupt();                                   //enable system interrupt
  ExintInit(int_id,int_trigger_type);                     //init exint
}

void loop()
{
  // put your main code here, to run repeatedly:
  if( (0 == g_extern_int0_flag) && (0 == g_extern_int1_flag) )
  {
    //program doesn't enter the user_interrupt
    uart_puts("------------IDLE------------\n");
  }
  else
  {
    //program enter the user_interrupt
    if(g_extern_int0_flag)                     
    {
      //if int0 flag = 1 enter if
      g_extern_int0_flag = 0;                  //clear int0 flag
      uart_puts("EXINT0000000000\n");          //print
    }
    if(g_extern_int1_flag)
    {
      //if int1 flag = 1 enter if
      g_extern_int1_flag = 0;                  //clear int1 flag
      uart_puts("EXINT1111111111\n");         //print
    }
  }
}
