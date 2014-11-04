#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void ADC_Clock_Configure(uint32_t Clock,uint32_t GPIO_Port_Clock);
void ADC_Pin_Configure(GPIO_TypeDef* GPIO_T,uint32_t GPIO_nb);
void ADC_Configure(ADC_TypeDef* ADCx, uint32_t ADC_Chanel_x, uint32_t ADC_SampleTime_x, uint32_t nb_conv, uint32_t ADC_Resolution_nb);

int adc_convert();

