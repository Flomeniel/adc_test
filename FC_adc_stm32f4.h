#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void adc_configure(ADC_TypeDef* ADCx, uint32_t ADC_Chanel_x, uint32_t ADC_SampleTime_x, uint32_t GPIO_T, uint32_t GPIO_nb, uint32_t ADC_Resolution_nb);

int adc_convert();
