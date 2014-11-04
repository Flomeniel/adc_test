#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "FC_adc_stm32f4.h"

int ConvertedValue = 0;  // affectation de la variable de travail permetant de récupérer la valeur convertie
uint32_t NB_Convert = 1; // variable de travail

int main(void){

	// Configuration de l'adc et des horloge et pin correspondante
	ADC_Clock_Configure(RCC_APB2Periph_ADC1,RCC_AHB1ENR_GPIOCEN);
	ADC_Pin_Configure(GPIOC,GPIO_Pin_0);
	ADC_Configure(ADC1,ADC_Channel_0,ADC_SampleTime_3Cycles,NB_Convert,ADC_Resolution_12b);

    while(1)
    {
    	ConvertedValue = adc_convert(ADC1);//Lecture de la valeur convertie
    }
}