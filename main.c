#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "FC_adc_stm32f4.h"

int ConvertedValue = 0; //Converted value readed from ADC


int main(void){
	typedef struct ADC_TypeDef* ADCx;
	adc_configure(ADC1,ADC_Channel_0,ADC_SampleTime_3Cycles,GPIOC,GPIO_Pin_0,ADC_Resolution_12b);//Start configuration
    while(1){//loop while the board is working
     ConvertedValue = adc_convert();//Read the ADC converted value
    }
}
