#include <UART.h>
#include <ADC.h>

/*
* This example just use for W2R chip
* In this example user should connect A0<->DAC
*/
T_SAR_ADC_CFG sar_adc_cfg;
void setup() 
{
  //configure sd adc
  sar_adc_cfg.sar_clk   = SAR_CLK_1_5MHZ;           //Set SAR sample clk
  sar_adc_cfg.otr       = SAR_CONTINUE_CONVERSION;  //Set ADC continue sample,or sample once
  sar_adc_cfg.adc_ch    = SAR_ADC_CH0;              //W2s can be set ch0-ch15,
  sar_adc_cfg.start     = SAR_ADC_EN;               //start sample after sample
  sar_adc_cfg.irq_en    = SAR_ADC_IRQ_DIS;          //disable adc mode irq

  SarAdcInit(&sar_adc_cfg);                         //init adc
  DacInit();                                        //init dac
}

void loop() 
{
  // put your main code here, to run repeatedly:
  unsigned int i;
  for(i = 0; i < 512;)
  {
    SetDacOut(DAC_NEGATIVE_SIGN | i);               //set dac output valtage
    if (SarAdcReadFlag())                           //adc sample end
    {
      uart_puts("\nSAR ADC READ->");
      uart_puts(xtoa(SarAdcReadVal()));             //print sample value
      i++;                                          //change next time dac value
    }
  }
}
