#include "t2_pwm.h"
#include "t2_display.h"
#include <stm32f4xx.h>

/*!
@file t2_pwm.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for PWM functions.
*/

int PWM_delay = 19000;
int PWM_increment = INCREMENT;

/*!
@brief Overheating alarm
@param
@return
@pre PWM_delay must be a positive number, GPIO D must be activated
@post PWM_delay and PWM_increment updated
PWM alarm; PWM_delay defines the duration of a pulse to the onboard LED,
which in turn controls the brightness of that LED; duty cycle of pulses
is 40 ms because this function is called every time we sample.
*/
void pwm_alarm()
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_SET);
	delay(PWM_delay);
	GPIO_ToggleBits(GPIOD,GPIO_Pin_12); // toggle LED
	
	/* add fade by changing duration of LED on */
	if ((PWM_delay - PWM_increment) <= 0) PWM_increment = -INCREMENT;
	else if ((PWM_delay - PWM_increment) >= MAX_PWM) PWM_increment = INCREMENT;
	PWM_delay = PWM_delay - PWM_increment;
}
