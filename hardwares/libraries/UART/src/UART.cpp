#include "UART.h"
void uart_puts(const char* str);

void uart_puts(const char* str)
{
  while(1)
  {     
      if('\0' == *str)
     {
        return;
     }
     while(1 == U0_BUSY_REG);
     U0_WRITE_REG = *str;
     *str++;
  }
}

char *xtoa(unsigned long num)
{
    static char buf[9];
    register unsigned char i, j, digit;

    buf[8] = 0;
    for (i = 7; i >= 0; --i)    
    {
        digit = num & 0xf;
        buf[i] = digit + (digit < 10 ? '0' : 'A' - 10);
        num >>= 4;
        if (num == 0) {
            break;
        }
    }

    if (i > 0) {
        j=i;
        digit= 8-j;
        for (i= 0; i <= digit; i++) {
            buf[i]= buf[i+j];
        }
    }
	
    return buf;
}
unsigned char GetChar()
{
    while(!U0_DATA_RDY_REG);
    return U0_READ_REG;
}

void UartPutChar(unsigned char data)
{
    while(1 == U0_BUSY_REG);
    U0_WRITE_REG = data;
}