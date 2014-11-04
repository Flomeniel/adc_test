#include "FC_adc_stm32f4.h"


/* example de configuration de l'adc:
 * 	ADCx = 1 (1 à 3)
 * 	Clock = RCC_APB2Periph_ADC1 (de 1 à 3)
 * 	ADC_Chanel_x = ADC_Channel_0  (0 à 18)
 * 	ADC_SampleTime_x =ADC_SampleTime_3Cycles (3 15 28 56 84 112 144 480)
 * 	GPIO_T = GPIOC (A B C D E)
 * 	GPIO_Port_Clock = RCC_AHB1ENR_GPIOCEN (de A à I)
 * 	GPIO_nb = GPIO_Pin_0 (de 1 à 15)
 * 	nb_conv = 1 (de 1 à 12)
 * 	ADC_Resolution_nb = ADC_Resolution_12b (12 10 8 6)
 */


void ADC_Clock_Configure(uint32_t Clock,uint32_t GPIO_Port_Clock)
{
	//Configuration de l'horloge
	RCC_APB2PeriphClockCmd(Clock,ENABLE);//L'adc utilise le pérriphérique APB2 pour sont signal d'horloge on connecte donc celui-ci grace à cette commande
	RCC_AHB1PeriphClockCmd(GPIO_Port_Clock,ENABLE);//horloge du port utiliser par l'adc

}

void ADC_Pin_Configure(GPIO_TypeDef* GPIO_T,uint32_t GPIO_nb)
{
	GPIO_InitTypeDef GPIO_initStructre; //Structure d'initialisation GPIO
	//Configuration des entrées sortie
	GPIO_initStructre.GPIO_Pin = GPIO_nb; //On choisit la pin que l'on souhaite utilisé
	GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //On la configure en mode annalogique
	GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //Pas d'option pull up pull down
	GPIO_Init(GPIO_T,&GPIO_initStructre);//ont initialise la struture pour affecter le port

}

void ADC_Configure(ADC_TypeDef* ADCx, uint32_t ADC_Chanel_x, uint32_t ADC_SampleTime_x, uint32_t nb_conv, uint32_t ADC_Resolution_nb)
{

	ADC_InitTypeDef ADC_init_structure; //Structure d'initialisation ADC

	//Configuration du convertiseur analogique numérique
	ADC_DeInit();
	ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//la donnée convertie sera decaler vers la droite
	ADC_init_structure.ADC_Resolution = ADC_Resolution_nb;// la tension d'entrée es convertie en un nombre de 12bits et nous donne une valeur max de 4096
	ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //Convertion continue
	//ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// A verifier si l'on souhaite le sinchroniser avec le timer de la linescan
	ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//Aucun trigger de conversion
	ADC_init_structure.ADC_NbrOfConversion = nb_conv;//I think this one is clear :p
	ADC_init_structure.ADC_ScanConvMode = DISABLE; //On scane un seul canal
	ADC_Init(ADCx,&ADC_init_structure);//ont initialise la structure avec les parramétre précedents

	//On active l'adc que l'on a choisit void adc_configure(ADC_TypeDef* "ADCx",...)
	ADC_Cmd(ADCx,ENABLE);

	//On choisit le canal à convertir
	ADC_RegularChannelConfig(ADCx,ADC_Chanel_x,1,ADC_SampleTime_x);
}

int adc_convert(ADC_TypeDef* ADCx)
{
	ADC_SoftwareStartConv(ADCx);//Debut de la conversion
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC)); //On boucle tant que la conversion n'est pas terminée
	return ADC_GetConversionValue(ADCx); //Retour de la valeur obtenu
}
