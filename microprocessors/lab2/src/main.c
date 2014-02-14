#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "t2_display.h"
#include "t2_adc.h"
#include "t2_pwm.h"
#include "t2_gpio.h"
#include "t2_filtering.h"

#define HEAT_THRESHOLD 55 // temperature at which processor's overheating alarm should go off
#define D 10 // filter depth

/*!
@file main.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Lab 2 thermometer main program.
*/

uint32_t ticks = 0; // for SysTick
uint16_t samples[D]; // buffer depth = 5
uint16_t average; // moving average of buffer samples
float average_temp_in_celsius; // global variable for the average temp in celsius
int overheated = 0;

/*!
@brief Timed interrupt
@pre Main method must call SysTick_Config() before interrupt-driven functionality is used.
Interrupts generated at a frequency defined in main(). 
*/
void SysTick_Handler()
{
	ticks++;
}

/*!
@brief Main method for thermometer
@pre main.c must have a SysTick_Handler().
Displays the internal temperature of the processor and flashes an alarm if the processor
is overheating.
*/
int main()
{
	/* Setup for sensors/pins */
	uint16_t new_sample;
	zero_initialize(samples,D);
	ADC_setup(); // activate ADC for temperature sensor
	seven_segment_GPIO_setup(); // activate GPIO B
	onboard_LED_GPIO_setup(); // activate GPIO D for PWM alarm
	SysTick_Config(SystemCoreClock / 100); // 25 Hz * 4 for display
	
	/* Display + overheating alarm logic */
	while(1) {
		while(!ticks);
		
		/* every 40 ms (4 ticks) take a new sample and recalculate the moving average */
		if (ticks >= 4) {
			ticks = 0;
			new_sample = read_ADC_temp();
			shift_in_value(new_sample,samples,(&average),D);
		}
			
    /* convert avg temp to celsius and display */
    average_temp_in_celsius = convert_to_celsius(average);
		display_multidigit_number(average_temp_in_celsius);
		
    /* raise alarm if overheating */ 
		if (average_temp_in_celsius > HEAT_THRESHOLD) overheated = 1;
		else overheated = 0;
		if (overheated) pwm_alarm();
	}
}

