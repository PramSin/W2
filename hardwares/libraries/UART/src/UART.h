#ifndef __UART_H__
#define __UART_H__

#define U0_REG_BASE_ADR                             (0x1F800000)

#define U0_READ_REG                                 (*(volatile unsigned long *)(U0_REG_BASE_ADR + 0))
#define U0_BUSY_REG                                 (*(volatile unsigned long *)(U0_REG_BASE_ADR + 1))
#define U0_WRITE_REG                                (*(volatile unsigned long *)(U0_REG_BASE_ADR + 2))
#define U0_CLRIRQ_REG                               (*(volatile unsigned long *)(U0_REG_BASE_ADR + 3))
#define U0_CTL0_REG                                 (*(volatile unsigned long *)(U0_REG_BASE_ADR + 4))
#define U0_DATA_RDY_REG                             (*(volatile unsigned long *)(U0_REG_BASE_ADR + 5))
#define U0_LINBRK_REG                               (*(volatile unsigned long *)(U0_REG_BASE_ADR + 6))
#define U0_BRP_REG                                  (*(volatile unsigned long *)(U0_REG_BASE_ADR + 7))

void uart_puts(const char* str);
char *xtoa(unsigned long num);
unsigned char GetChar();
void UartPutChar(unsigned char data);

#endif