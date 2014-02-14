#include <stm32f4xx.h>

#define AVG_SLOPE 2.5 // mV per degree C
#define V_25 760 // in mV
#define VREF 3000 // in mV

void ADC_setup(void);
uint16_t read_ADC_temp(void);
float convert_to_celsius(float sample);
