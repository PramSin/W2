#include <UART.h>
#include <ADC.h>

/*
* This example just use for w2s chip
* In this example user should connect A0<->V15 and A1 <-> DAC
*/
T_SD_ADC_CFG sd_adc_cfg;
void setup() 
{
  //configure sd adc
  sd_adc_cfg.gain   = GAIN_X1;          //Set the internal circuit not to amplify
  sd_adc_cfg.avg    = AVG_64TIMES;      //set adc mode sample 64 data to average
  sd_adc_cfg.sd_clk = SD_CLK_1_5MHZ;    //set adc sample clk
  sd_adc_cfg.df_clk = DF_CLK_128;       //Set ADC sample accuracy,can be set 128/256/512/1024
  sd_adc_cfg.adc_ch = SD_ADC_CH_0;      //W2s can be set ch0-ch3,
  sd_adc_cfg.start  = SD_ADC_EN;        //start sample after sample
  sd_adc_cfg.irq_en = SD_ADC_IRQ_DIS;   //disable adc mode irq
  sd_adc_cfg.op_ch  = SD_ADC_OP_0;      //w2s can be set op0-op3

  SdAdcInit(&sd_adc_cfg);               //init adc
  DacInit();                            //init dac
}

void loop() 
{
  // put your main code here, to run repeatedly:
  unsigned int i;
  for(i = 0; i < 512;)
  {
    SetDacOut(DAC_POSITIVE_SIGN | i);    //set dac output valtage
    if (SdAdcReadFlag())                 //adc sample end
    {
      uart_puts("\nSD ADC READ->");
      uart_puts(xtoa(SdAdcReadVal()));  //print sample value
      i++;                              //change next time dac value
    }
  }
}
