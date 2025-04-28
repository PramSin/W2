#include "ADC.h"

void SdAdcInit(T_SD_ADC_CFG* p_adc_cfg)
{
    A_PGA_CTL_REG   = ((p_adc_cfg)->adc_ch) | ((p_adc_cfg)->gain) | ((p_adc_cfg)->op_ch);
    A_SD_CTL_REG    = (p_adc_cfg->avg) | \
                      (p_adc_cfg->sd_clk) | \
                      (p_adc_cfg->df_clk) | \
                      (p_adc_cfg->irq_en) | \
                      (p_adc_cfg->start);
}

void SdAdcStart()
{
    A_SD_CTL_REG |= SD_ADC_EN;
}
void SdAdcStop()
{
    A_SD_CTL_REG &= ~(SD_ADC_EN);

}
unsigned char SdAdcReadFlag()
{
    if((ADC_READ_FLAG_REG & (0x1 << 31)) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
unsigned int SdAdcReadVal()
{
    return (A_CLR_REG & 0x7fffffff);
}
void DacInit()
{
    A_DAC_CTL_REG = DAC_EN;
}
void SetDacOut(unsigned short val)
{
    A_DAC_CTL_REG &= 0x8000;
    A_DAC_CTL_REG |= val;
}
void DacClose()
{
    A_DAC_CTL_REG = 0;
}

void SarAdcInit(T_SAR_ADC_CFG* p_adc_cfg)
{
    A_SAR_CTL_REG = (p_adc_cfg->sar_clk)    | \
                    (p_adc_cfg->input_sel)  | \
                    (p_adc_cfg->pwm_trig)   | \
                    (p_adc_cfg->otr)        | \
                    (p_adc_cfg->irq_en)     | \
                    (p_adc_cfg->adc_ch)     | \
                    (p_adc_cfg->start);
}
unsigned char SarAdcReadFlag()
{
    if( 0 == (A_SAR_READ_REG & 0x8000) )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
unsigned short SarAdcReadVal()
{
    return (A_SAR_READ_REG & 0x7FFF);
}
