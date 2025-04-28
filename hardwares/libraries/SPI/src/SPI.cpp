#include <SPI.h>
/*********************************************************************
 * @fn      SpiClearIrq
 *
 * @brief   清除SPI中断标志位
 * 
 * @param   NULL
 *
 * @return  NULL
 */
void SpiClearIrq()
{
    SPI_CLRIRQ_REG = 1;
}

/*********************************************************************
 * @fn      SpiMasterInit
 *
 * @brief   SPI主模式初始化
 * 
 * @param   NULL
 *
 * @return  NULL
 */
void SpiMasterInit()
{
    SPI_CTL_REG = SPI_ENABLE_BIT | SPI_MASTER_EN_BIT;
    SpiClearIrq();
}

/*********************************************************************
 * @fn      SpiTxBusy
 *
 * @brief   判断当前SPI总线是否空闲
 * 
 * @param   NULL
 *
 * @return  0表示空闲,1表示繁忙0
 */
unsigned char SpiTxBusy()
{
    return SPI_BUSY_REG;
}

/*********************************************************************
 * @fn      SpiWriteByte
 *
 * @brief   SPI输出8bit数据
 * 
 * @param   NULL
 *
 * @return  0表示空闲,1表示繁忙0
 */
void SpiWriteByte(unsigned char byte)
{
    while(SPI_BUSY_REG & 0x1);
    SPI_WRITE_REG = byte;
    while(SPI_BUSY_REG & 0x1);
}

/*********************************************************************
 * @fn      SpiCsOn
 *
 * @brief   SPI cs信号输出使能
 * 
 * @param   NULL
 *
 * @return  NULL
 */
void SpiCsOn()
{
	SPI_CTL_REG |= SPI_CS_ON_BIT;
}

/*********************************************************************
 * @fn      SpiCsOff
 *
 * @brief   SPI cs信号输出关闭
 * 
 * @param   NULL
 *
 * @return  NULL
 */
void SpiCsOff()
{
	SPI_CTL_REG &= ~(SPI_CS_ON_BIT);
}


/*********************************************************************
 * @fn      SpiSlaveInit
 *
 * @brief   SPI从设备初始化
 * 
 * @param   NULL
 *
 * @return  NULL
 */
void SpiSlaveInit()
{
    // SPI_CTL_REG = SPI_ENABLE_BIT | SPI_SLAVE_EN_BIT;
    SPI_CTL_REG = SPI_ENABLE_BIT;

    SpiClearIrq();
    SPI_WRITE_REG = 0x3A;
}

void SpiSetCpolAndCpha(char cpol,char cpha)
{
    if(0 != cpol)
    {
        SPI_CTL_REG |= SPI_CPOL_BIT;
    }
    else
    {
        SPI_CTL_REG &= ~(SPI_CPOL_BIT);
    }

    if(0 != cpha)
    {
        SPI_CTL_REG |= SPI_CPHA_BIT;
    }
    else
    {
        SPI_CTL_REG &= ~(SPI_CPHA_BIT);
    }
}

void SpiMasterSetClk(unsigned char clk)
{
    clk &= SPI_CLK_SLOW;
    SPI_CTL_REG &= ~(SPI_CLK_SLOW);
    SPI_CTL_REG |= clk;
}
unsigned char SpiReceiveDataIsReady()
{
    return SPI_DATARDY_REG & 0x1;
}

unsigned char SpiReceiveData()
{
    return SPI_READ_REG;
}