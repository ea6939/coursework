#include "t2_adc.h"

/*!
@file t2_adc.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for using ADCs, including temperature sensors
*/

/*!
@brief Reads from the ADC temperature sensor
@return sample from 
@pre ADC must be set up
Returns a sample from the ADC between 0x0000 and 0x0fff representing the fraction of 
the ADC's reference voltage (VREF, estimated at 3V) transduced by temperature sensor.
*/
uint16_t read_ADC_temp() 
{ 
	// Returns a sample from the temp sensor.
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_480Cycles); // channel 16 for temp_sensor
	ADC_SoftwareStartConv(ADC1); //Starting Conversion, waiting for it to finish, clearing the flag, reading the result
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //Could be through interrupts (Later)
	//ADC_ClearFlagStatus(ADC1, ADC_FLAG_EOC); //EOC means End Of Conversion
	ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
	return ADC_GetConversionValue(ADC1); // Result available in ADC1->DR
}

/*!
@brief set up ADC
@param sample the raw data
@return converted data
@pre data must be max 0x0FFF (because 12-bit ADC)
@post 
Activates the 12-bit ADC.
*/
void ADC_setup() 
{
	// Copied from tutorial 2.
	ADC_InitTypeDef       adc_init_s;
	ADC_CommonInitTypeDef adc_common_init_s;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Clock Gating
	adc_common_init_s.ADC_Mode = ADC_Mode_Independent;
	adc_common_init_s.ADC_Prescaler = ADC_Prescaler_Div2;
	adc_common_init_s.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adc_common_init_s.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&adc_common_init_s); //Initialization
	
	adc_init_s.ADC_Resolution  = ADC_Resolution_12b;
	adc_init_s.ADC_ScanConvMode  = DISABLE;
	adc_init_s.ADC_ContinuousConvMode  = DISABLE;
	adc_init_s.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc_init_s.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init_s.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &adc_init_s); //Initialization
	
	ADC_Cmd(ADC1, ENABLE); //Enable Module
	
	ADC_TempSensorVrefintCmd(ENABLE); /* "Set the TSVREFE bit in the ADC_CCR register to wake up the temperature sensor 
																				from power down mode" */
}

/*!
@brief Converts raw data from temp sensor
@param sample the raw data
@return data in Celsius
@pre data must be max 0x0FFF (because 12-bit ADC)
@post 
Converts ADC temp data to data in Celsius
*/
float convert_to_celsius(float sample)
{
	float vsense = VREF * ((float)sample) / ((float)0x0FFF);
	float temp_in_celsius = ((vsense - V_25) / AVG_SLOPE) + 25.0;
	return temp_in_celsius;
}
