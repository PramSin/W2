#include "gpio.h"
#include "SYS.h"

void GpioSetPinOutput(unsigned int io_id)
{
    if( (IO_ID_0 == io_id) || (IO_ID_1 == io_id) )
    {
        CloseSysDgben();
    }
    SYS_IOCTL_REG |= io_id;
}

void GpioSetPinInput(unsigned int io_id)
{
    if( (IO_ID_0 == io_id) || (IO_ID_1 == io_id) ) 
    {
        CloseSysDgben();
    }
    SYS_IOCTL_REG &= ~(io_id);
}
unsigned int ReadPinInputValue(unsigned int io_id)
{
    unsigned int ret_val;
    ret_val = 1;
    if( 0 == (io_id & SYS_GPIO1_REG) )
    {
        ret_val = 0;
    }

    return ret_val;
}

unsigned int ReadAllPinInputValue()
{
    return SYS_GPIO1_REG;
}
void SetPinOutputHighOrLow(unsigned int io_id,char high_or_low)
{
    if(IO_OUT_HIGH == high_or_low)
    {
        SYS_GPIO0_REG |= io_id;
    }
    else
    {
        SYS_GPIO0_REG &= ~(io_id);
    }
}

unsigned int ReadPinOutputVal(unsigned int io_id)
{
    unsigned int ret_val;
    ret_val = 1;
    if( 0 == (io_id & SYS_GPIO0_REG) )
    {
        ret_val = 0;
    }

    return ret_val;
}