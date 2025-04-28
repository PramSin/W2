#ifndef __ADC_H__
#define __ADC_H__

#define ADC_REG_BASE_ADR                            (0x1F800600)
//sar adc
#define A_OPO_CMP_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 0))
#define A_SAR_CTL_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 1))
#define A_SAR_READ_REG                              (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 2))
#define A_CLR_REG                                   (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 3))
#define A_SAR_CS_REG                                (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 4))
#define A_DAC_CTL_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 6))
//sd adc
#define A_OPO_CMP_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 0))
#define A_SD_READ_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 2))
#define A_CLR_REG                                   (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 3))
#define A_PGA_CTL_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 5))
#define A_DAC_CTL_REG                               (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 6))
#define A_SD_CTL_REG                                (*(volatile unsigned long *)(ADC_REG_BASE_ADR + 7))

#define CMP3_ENABLE                                 (0x1 << 7)
#define CMP2_ENABLE                                 (0x1 << 6)
#define CMP1_ENABLE                                 (0x1 << 5)
#define CMP0_ENABLE                                 (0x1 << 4)
#define CMP_DISABLE                                 (0)

#define IRQ_ENABLE                                  (0x1 << 16)
#define IRQ_DISABLE                                 (0x0 << 16)

#define AVG_512TIMES                                (0x7 << 5)
#define AVG_256TIMES                                (0x6 << 5)
#define AVG_128TIMES                                (0x5 << 5)
#define AVG_64TIMES                                 (0x4 << 5)
#define AVG_32TIMES                                 (0x3 << 5)
#define AVG_16TIMES                                 (0x2 << 5)
#define AVG_8TIMES                                  (0x1 << 5)
#define NO_AVG                                      (0)

#define SD_CLK_781KHZ                               (0x3 << 3)
#define SD_CLK_1_5MHZ                               (0x2 << 3)
#define SD_CLK_6MHZ                                 (0x1 << 3)
#define SD_CLK_3MHZ                                 (0x0 << 3)

#define DF_CLK_1024                                 (0x3 << 1)
#define DF_CLK_512                                  (0x2 << 1)
#define DF_CLK_256                                  (0x1 << 1)
#define DF_CLK_128                                  (0x0 << 1)

#define ADC_16_BIT_mode                             (DF_CLK_256)                

#define SD_ADC_ENABLE                               (0x1)
#define SD_ADC_READ_READY                           (0x1 << 31)

#define SD_ADC_EN                                   (0x1)
#define SD_ADC_DIS                                  (0x0)

#define SD_ADC_IRQ_EN                               (1 << 16)
#define SD_ADC_IRQ_DIS                              (0 << 16)

#define GAIN_X1                                     (0 << 12)
#define GAIN_X2                                     (1 << 12)
#define GAIN_X4                                     (2 << 12)
#define GAIN_X9                                     (3 << 12)
#define GAIN_X15                                    (4 << 12)
#define GAIN_X24                                    (5 << 12)
#define GAIN_X32                                    (6 << 12)
#define GAIN_X49                                    (7 << 12)
#define BYPASS                                      GAIN_X1

#define SD_ADC_CH_0                                 CMP0_ENABLE
#define SD_ADC_CH_1                                 CMP1_ENABLE
#define SD_ADC_CH_2                                 CMP2_ENABLE
#define SD_ADC_CH_3                                 CMP3_ENABLE

#define SD_ADC_OP_0                                 (1 << 0)
#define SD_ADC_OP_1                                 (1 << 1)
#define SD_ADC_OP_2                                 (1 << 2)
#define SD_ADC_OP_3                                 (1 << 3)

#define ADC_READY_FLAG_REG						    A_SD_READ_REG
#define ADC_READ_VAL_REG						    A_CLR_REG
#define ADC_READ_FLAG_REG                           A_SD_READ_REG         // read only, cannot write
#define ADC_READ_VALUE_REG                          A_CLR_REG 

#define DAC_EN                                      (1 << 15);
#define DAC_DIS                                     (0 << 15);

#define DAC_NEGATIVE_SIGN                           (1 << 11)
#define DAC_POSITIVE_SIGN                           (0 << 11)

typedef struct 
{
    unsigned int op_ch;//op0-op3
    unsigned int irq_en;
    unsigned int gain;//放大倍数
    unsigned int avg;//平均次数
    unsigned int sd_clk;
    unsigned int df_clk;
    unsigned int adc_ch;//
    unsigned int start; //start模式即配置完成立即开始采样,cfg模式即仅配置ADC模块
}T_SD_ADC_CFG;

#define SAR_CLK_781KHZ                              (0x3 << 12)
#define SAR_CLK_1_5MHZ                              (0x2 << 12)
#define SAR_CLK_6MHZ                                (0x1 << 12)
#define SAR_CLK_3MHZ                                (0x0 << 12)

#define SAR_INTERNAL_INPUT                          (0x1 << 11)
#define SAR_EXTERNAL_INPUT                          (0 << 11)

#define SAR_INTERNAL_INPUT_CH7_OP3                  (0x3 << 8)
#define SAR_INTERNAL_INPUT_CH6_OP2                  (0x2 << 8)
#define SAR_INTERNAL_INPUT_CH5_OP1                  (0x1 << 8)
#define SAR_INTERNAL_INPUT_CH4_OP0                  (0x0 << 8)

#define SAR_ADC_CH0                                 (0x0 << 4)
#define SAR_ADC_CH1                                 (0x1 << 4)
#define SAR_ADC_CH2                                 (0x2 << 4)
#define SAR_ADC_CH3                                 (0x3 << 4)
#define SAR_ADC_CH4                                 (0x4 << 4)
#define SAR_ADC_CH5                                 (0x5 << 4)
#define SAR_ADC_CH6                                 (0x6 << 4)
#define SAR_ADC_CH7                                 (0x7 << 4)
#define SAR_ADC_CH8                                 (0x8 << 4)
#define SAR_ADC_CH9                                 (0x9 << 4)
#define SAR_ADC_CH10                                (0xA << 4)
#define SAR_ADC_CH11                                (0xB << 4)
#define SAR_ADC_CH12                                (0xC << 4)
#define SAR_ADC_CH13                                (0xD << 4)
#define SAR_ADC_CH14                                (0xE << 4)
#define SAR_ADC_CH15                                (0xF << 4)

#define SAR_TRIG_BY_PWM_EN                          (1 << 3)
#define SAR_TRIG_BY_PWM_DIS                         (0 << 3)

#define SAR_ONE_TIME_CONVERSION                     (1 << 2)
#define SAR_CONTINUE_CONVERSION                     (0 << 2)

#define SAR_ADC_IRQ_EN                              (1 << 1)
#define SAR_ADC_IRQ_DIS                             (0 << 1)

#define SAR_ADC_EN                                  (1)
#define SAR_ADC_DIS                                 (0)

typedef struct 
{
    unsigned int sar_clk;
    unsigned int input_sel;
    unsigned int pwm_trig;
    unsigned int otr;
    unsigned int irq_en;
    unsigned int adc_ch;//
    unsigned int start; //start模式即配置完成立即开始采样,cfg模式即仅配置ADC模块
}T_SAR_ADC_CFG;

void SdAdcInit(T_SD_ADC_CFG* p_adc_cfg);
void SdAdcStart();
void SdAdcStop();
unsigned char SdAdcReadFlag();
unsigned int SdAdcReadVal();
void DacInit();
void SetDacOut(unsigned short val);
void DacClose();
void SarAdcInit(T_SAR_ADC_CFG* p_adc_cfg);
unsigned char SarAdcReadFlag();
unsigned short SarAdcReadVal();

#endif