#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "adc.h"

void ADC_Configuration(void){
	ADC_InitTypeDef	ADC_InitStructure;

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1,&ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,1,ADC_SampleTime_55Cycles5);
    ADC_Cmd(ADC1,ENABLE);
    ADC_ResetCalibration(ADC1);
    
	while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    
	while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

float ADC_GetValue(float VREF){
	return (VREF * ADC_GetConversionValue(ADC1) / 0x0fff);
}
