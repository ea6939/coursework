/*!
@file t2_pwm.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for PWM functions.
*/

#include "t2_pwm.h"
#include "t2_display.h"
#include <stm32f4xx.h>
#include "stm32f4xx_conf.h"
#include "cmsis_os.h"

int PWM_delay = 1;
int PWM_increment = INCREMENT;

TIM_TimeBaseInitTypeDef  TIM_AlarmTimeBaseStructure; 
TIM_OCInitTypeDef  TIM_AlarmOCInitStructure; 

/*!
@brief Overheating alarm
@param
@return
@pre PWM_delay must be a positive number, GPIO D must be activated, timer must be activated
@post PWM_delay and PWM_increment updated
PWM alarm; PWM_delay defines the duration of a pulse to the onboard LED,
which in turn controls the brightness of that LED; duty cycle of pulses
is the period of the timer.
*/
void pwm_alarm_fade() {
	
	/* add fade by changing duration of LED on */
	if ((PWM_delay - PWM_increment) <= 0) PWM_increment = -INCREMENT;
	else if ((PWM_delay - PWM_increment) >= MAX_PWM) PWM_increment = INCREMENT;
	PWM_delay = PWM_delay - PWM_increment;
	TIM_SetCompare1(TIM4, PWM_delay);

}

/*!
@brief Alarm reset
@pre Timer 4, channel 1 must be configured as a PWM output to an LED
@post Duty cycle shortened to 1 cycle
Effectively turns off the overheating alarm by making the 
PWM duty cycle impercepibly short.
*/
void pwm_reset()
{
	TIM_SetCompare1(TIM4, 1); // short PWM period means almost no light
}

/*!
@brief PWM timer config for PWM alarm
@post Timer 4 ch 1 configured as PWM output
PWM timer for alarm gets a duty cycle of 40 ms, no initial duty cycle
*/
void ALARM_TIM4_Configuration(){
	 
	GPIO_InitTypeDef GPIO_InitStructure; 
  
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  
  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
    
  /* GPIOA Configuration: TIM4 CH1 (PD12) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PD12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //push-pull
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; //pullup
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  /* Connect TIM4 pins to AF2 */  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);  
	
  /* Time base configuration */
  TIM_AlarmTimeBaseStructure.TIM_Period = 10000; // precalculated
  TIM_AlarmTimeBaseStructure.TIM_Prescaler = 80; 
  TIM_AlarmTimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_AlarmTimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  
  TIM_TimeBaseInit(TIM4, &TIM_AlarmTimeBaseStructure); 
  
  /* PWM1 Mode configuration: Channel3 */
  TIM_AlarmOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_AlarmOCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_AlarmOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //CPOL polarity is high, event happens then goes to low
  
  TIM_OC1Init(TIM4, &TIM_AlarmOCInitStructure); 
  
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM4, ENABLE); 
	TIM_Cmd(TIM4, ENABLE); 
	
}
	
	

