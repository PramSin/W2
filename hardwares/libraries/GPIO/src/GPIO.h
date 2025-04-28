#ifndef __GPIO_H__
#define __GPIO_H__
#define IO_IN                           (0)
#define IO_OUT                          (1)

#define IO_OUT_HIGH                     (1)
#define IO_OUT_LOW                      (0)

#define IO_ID_0                         (1 << 0)
#define IO_ID_1                         (1 << 1)
#define IO_ID_2                         (1 << 2)
#define IO_ID_3                         (1 << 3)
#define IO_ID_4                         (1 << 4)
#define IO_ID_5                         (1 << 5)
#define IO_ID_6                         (1 << 6)
#define IO_ID_7                         (1 << 7)
#define IO_ID_8                         (1 << 8)
#define IO_ID_9                         (1 << 9)
#define IO_ID_10                        (1 << 10)
#define IO_ID_11                        (1 << 11)
#define IO_ID_12                        (1 << 12)
#define IO_ID_13                        (1 << 13)
#define IO_ID_14                        (1 << 14)
#define IO_ID_15                        (1 << 15)
#define IO_ID_16                        (1 << 16)
#define IO_ID_17                        (1 << 17)
#define IO_ID_18                        (1 << 18)
#define IO_ID_19                        (1 << 19)
#define IO_ID_20                        (1 << 20)
#define IO_ID_21                        (1 << 21)
#define IO_ID_22                        (1 << 22)
#define IO_ID_23                        (1 << 23)
#define IO_ID_24                        (1 << 24)
#define IO_ID_25                        (1 << 25)
#define IO_ID_26                        (1 << 26)
#define IO_ID_27                        (1 << 27)
#define IO_ID_28                        (1 << 28)
#define IO_ID_29                        (1 << 29)
#define IO_ID_30                        (1 << 30)
#define IO_ID_31                        (1 << 31)

void GpioSetPinOutput(unsigned int io_id);
void GpioSetPinInput(unsigned int io_id);
unsigned int ReadPinInputValue(unsigned int io_id);
unsigned int ReadAllPinInputValue();
void SetPinOutputHighOrLow(unsigned int io_id,char high_or_low);
unsigned int ReadPinOutputVal(unsigned int io_id);

#endif