#include "FC_adc_stm32f4.h"


/* example de configuration de l'adc:
 * 	ADCx = 1 (1 à 3)
 * 	ADC_Chanel_x = ADC_Channel_0  (0 à 18)
 * 	ADC_SampleTime_x =ADC_SampleTime_3Cycles (3 15 28 56 84 112 144 480)
 * 	GPIO_T = GPIOC (A B C D E)
 * 	GPIO_nb = GPIO_Pin_0 (1 à 15)
 * 	ADC_Resolution_nb = ADC_Resolution_12b (12 10 8 6)
 */

void adc_configure(ADC_TypeDef* ADCx, uint32_t ADC_Chanel_x, uint32_t ADC_SampleTime_x, uint32_t GPIO_T, uint32_t GPIO_nb, uint32_t ADC_Resolution_nb){




 ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration
 GPIO_InitTypeDef GPIO_initStructre; //Structure for analog input pin
 //Clock configuration
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//The ADC1 is connected the APB2 peripheral bus thus we will use its clock source
 RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);//Clock for the ADC port!! Do not forget about this one ;)
 //Analog pin configuration
 GPIO_initStructre.GPIO_Pin = GPIO_nb;//The channel 10 is connected to PC0
 GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PC0 pin is configured in analog mode
 GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down
 GPIO_Init(GPIO_T,&GPIO_initStructre);//Affecting the port with the initialization structure configuration
 //ADC structure configuration
 ADC_DeInit();
 ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right
 ADC_init_structure.ADC_Resolution = ADC_Resolution_nb;//Input voltage is converted into a 12bit number giving a maximum value of 4096
 ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once
 ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
 ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion
 ADC_init_structure.ADC_NbrOfConversion = 1;//I think this one is clear :p
 ADC_init_structure.ADC_ScanConvMode = DISABLE;//The scan is configured in one channel
 ADC_Init(ADCx,&ADC_init_structure);//Initialize ADC with the previous configuration
 //Enable ADC conversion
 ADC_Cmd(ADCx,ENABLE);
 //Select the channel to be read from
 ADC_RegularChannelConfig(ADCx,ADC_Chanel_x,1,ADC_SampleTime_x);
}
int adc_convert(){
 ADC_SoftwareStartConv(ADCx);//Start the conversion
 while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));//Processing the conversion
 return ADC_GetConversionValue(ADCx); //Return the converted data
}
