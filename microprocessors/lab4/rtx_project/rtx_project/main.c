/*!
@file main.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Main program for starting/managing threads of LCD/temp/tilt system.
*/

#include "arm_math.h"
#include "stdio.h"

#include "stm32f4xx.h"
#include "cmsis_os.h"

#include "t2_adc.h"
#include "t2_filtering.h"
#include "t2_mems.h"
#include "t2_pwm.h"
#include "t2_servo.h"
#include "t2_button.h"
#include "t2_gpio.h"
#include "t2_lcd.h"

#ifndef HEAT_THRESHOLD
	#define HEAT_THRESHOLD 35
#endif

#ifndef ACCEL_MODE
	#define ACCEL_MODE 0
#endif

#ifndef TEMP_MODE
	#define TEMP_MODE 1
#endif

void thread_display(void const *argument);
void thread_temperature(void const *argument);
void thread_tilt(void const * argument);
void thread_overheat_alarm(void const * argument);
void thread_display_update(void const *argument);

//! Thread structure for above thread
osThreadDef(thread_display, osPriorityNormal, 1, 0);
osThreadDef(thread_temperature, osPriorityNormal, 1, 0);
osThreadDef(thread_tilt, osPriorityNormal, 1, 0);
osThreadDef(thread_overheat_alarm, osPriorityNormal, 1, 0);
osThreadDef(thread_display_update, osPriorityNormal, 1, 0);

// ID for thread
osThreadId tid_thread_display;
osThreadId tid_thread_temperature;
osThreadId tid_thread_tilt;
osThreadId tid_thread_overheat_alarm;
osThreadId tid_thread_display_update;

//global variables
float average_temp_in_celsius = 0; // global variable for the average temp in celsius
float pitch, roll = 0.0;
int overheated = 0;
int mode = ACCEL_MODE;
float displayed_value_1, displayed_value_2 = 0.0;

/*!
 @brief handler for button pushes
 */
void EXTI0_IRQHandler(void)
{
	//toggles between both modes
	if(mode == ACCEL_MODE) mode = TEMP_MODE;
	else mode = ACCEL_MODE;
	EXTI_ClearITPendingBit(EXTI_Line0);
}

/*!
 @brief handler for ADC timer interrupts
 */
void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		osSignalSet(tid_thread_temperature,0x02);
	}
}


/*!
 @brief handler for MEMS timer interrupts
 */
void TIM5_IRQHandler(void){
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		osSignalSet(tid_thread_tilt,0x01);
	}
}

/*!
 @brief Program entry point
 */
int main (void) {
	
	// Start threads
	tid_thread_display = osThreadCreate(osThread(thread_display), NULL);
	tid_thread_temperature = osThreadCreate(osThread(thread_temperature), NULL);
	tid_thread_tilt = osThreadCreate(osThread(thread_tilt), NULL);
	tid_thread_overheat_alarm = osThreadCreate(osThread(thread_overheat_alarm), NULL);
	tid_thread_display_update = osThreadCreate(osThread(thread_display_update), NULL);

	button_interrupt_setup();
	
	// The below doesn't really need to be in a loop
	while(1){
		osDelay(osWaitForever);
	}
}


/*!
@brief This thread changes what the LCD is currently displaying
when signalled by the updater thread; otherwise waits.
*/
void thread_display (void const *argument) 
{
	t2_lcd_setup();
	t2_lcd_command(LCD_FUNCTION_SET);
	t2_lcd_command(LCD_DISPLAY_ON);
	
	char string [100];
	int str_size;
	
	while(1){
		//displays the value corresponding to the correct mode (only when value changes)
		osSignalWait(0x04, osWaitForever);
		
		// clear display and move cursor to home
		t2_lcd_command(LCD_CLEAR_DISPLAY);
		t2_lcd_command(LCD_CURSOR_HOME);
		
		// display temperature
		if (mode == TEMP_MODE) {
			str_size = sprintf(string,"Temperature: %4.1f",average_temp_in_celsius);
			t2_lcd_draw_string(string,str_size);
		}
		
		// display pitch, roll
		else {
			str_size = sprintf(string,"Pitch: %4.1f",pitch);
			t2_lcd_draw_string(string,str_size);
			
			t2_lcd_command(LCD_CR); //carriage return
			
			str_size = sprintf(string,"Roll: %4.1f",roll);
			t2_lcd_draw_string(string,str_size);
			
 		}
	}
}

/*!
@brief This thread signals the display thread whenever
one of the displayed variables changes.
*/
void thread_display_update (void const *argument) 
{
	// Only let the display thread run if the numbers to be displayed have changed.
	while(1) {
		if (mode == TEMP_MODE){
			if (displayed_value_1 != average_temp_in_celsius) {
				displayed_value_1 = average_temp_in_celsius;
				osSignalSet(tid_thread_display, 0x04);
			}
		}
		
		else /*accel mode*/ {
			if (displayed_value_1 != pitch) {
				displayed_value_1 = pitch;
				osSignalSet(tid_thread_display, 0x04);
			}
			
			if (displayed_value_2 != roll) {
				displayed_value_2 = roll;
				osSignalSet(tid_thread_display, 0x04);
			}
		}
		
		osDelay(200);
	}
}

/*!
@brief This thread samples the temperature sensor, filters that 
data, and converts the filtered data to a value in Celsius
which can be displayed.
*/
void thread_temperature (void const *argument) 
{
	uint16_t samples[10];
	zero_initialize(samples,10);
	uint16_t average; // moving average of buffer samples
	float new_sample;
	
	ADC_setup();
	ADC_TIM3_Configuration();
	
	while(1) {
		/* every 40 ms take a new sample and recalculate the moving average */
		osSignalWait(0x02, osWaitForever);		// osSignalClear needed?
		new_sample = read_ADC_temp();
		shift_in_value(new_sample,samples,(&average),10);
		
		/* convert avg temp to celsius and display */
    average_temp_in_celsius = convert_to_celsius(average);
		
    /* raise alarm if overheating */ 
		if (average_temp_in_celsius > HEAT_THRESHOLD) overheated = 1;
		else overheated = 0;
		
	}
}

/*!
@brief This thread controls the overheating alarm using the
"overheated" variable.
*/
void thread_overheat_alarm (void const *argument) {
	ALARM_TIM4_Configuration();
	while(1) {
		if (overheated){
			pwm_alarm_fade();
		}
		
		else {
			pwm_reset();
		}
		
		osDelay(5);
	}
}

/*!
@brief This thread samples/filters the accelerometer
and tilts the servo motor according to the orientation.
*/
void thread_tilt (void const *argument) {
	t2_LIS3DSH_setup(); // setup accel, accel interrupts
	MEMS_TIM5_Configuration();
	servo_setup();
	
	while(1){
		// wait for 100 Hz signal
		osSignalWait(0x01, osWaitForever);
		update_orientation(); // read and filter
		pitch = get_pitch();
		roll = get_roll();
		turn_to_angle(pitch);
	}
}
