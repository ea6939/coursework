/*!
@file g2_servo.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Driver for servo motor.
*/

//#include "t2_pwm.h"
//#include "t2_gpio.h"
#include "g2_servo.h"
#include "stm32f4xx_gpio.h"
#include <stm32f4xx.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

TIM_TimeBaseInitTypeDef  TIM_ServoTimeBaseStructure; 
TIM_OCInitTypeDef  TIM_ServoOCInitStructure; 

uint16_t zero_dg_duty_cycle = (0.075 * (SERVO_TIMER_ARR + 1)) - 1;
uint16_t ninety_dg_duty_cycle = (0.105 * (SERVO_TIMER_ARR + 1)) - 1;
uint16_t starting_duty_cycle = 2100;

/*!
@brief PWM timer config for servo
@post Timer 2 ch 4 (roll) configured as PWM output
PWM timer for alarm gets a duty cycle of 40 ms
*/
void servo_setup(void)
{
	/* TIM Configuration */
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
    
  /* GPIOA Configuration: TIM2 CH4 (PA3) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //push-pull
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; //pullup
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Connect TIM2 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2); 

  /* Time base configuration */
  TIM_ServoTimeBaseStructure.TIM_Period = SERVO_TIMER_ARR; // precalculated
  TIM_ServoTimeBaseStructure.TIM_Prescaler = SERVO_TIMER_PRESCALER; 
  TIM_ServoTimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_ServoTimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  
  TIM_TimeBaseInit(TIM2, &TIM_ServoTimeBaseStructure); 
  
  /* PWM1 Mode configuration: Channel4 */
  TIM_ServoOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_ServoOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_ServoOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //CPOL polarity is high, event happens then goes to low
  
  TIM_OC4Init(TIM2, &TIM_ServoOCInitStructure); 
  
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	TIM_Cmd(TIM2, ENABLE); 
}

/*!
@brief PWM timer config for servo
@post Timer 2 ch 3 (pitch) configured as PWM output
PWM timer for alarm gets a duty cycle of 40 ms
*/
void servo_setup2(void)
{
	/* TIM Configuration */
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
    
  /* GPIOA Configuration: TIM2 CH4 (PA2) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //push-pull
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; //pullup
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Connect TIM2 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2); 

  /* Time base configuration */
  TIM_ServoTimeBaseStructure.TIM_Period = SERVO_TIMER_ARR; // precalculated
  TIM_ServoTimeBaseStructure.TIM_Prescaler = SERVO_TIMER_PRESCALER; 
  TIM_ServoTimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_ServoTimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  
  TIM_TimeBaseInit(TIM2, &TIM_ServoTimeBaseStructure); 
  
  /* PWM1 Mode configuration: Channel3 */
  TIM_ServoOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_ServoOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_ServoOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //CPOL polarity is high, event happens then goes to low
  
  TIM_OC3Init(TIM2, &TIM_ServoOCInitStructure); 
  
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	TIM_Cmd(TIM2, ENABLE); 
}

/*!
@brief turn servo motor to an angle
@param angle the angle to be turned to
@pre servo PWM timer must be configured
@post Servo timer duty cycle changed to angle's cycle
The servo's duty cycle will be changed to a duty cycle
which turns the motor to the given angle.
*/
void turn_to_angle2(float angle)
{
	//uint16_t servo_difference = ninety_dg_duty_cycle - zero_dg_duty_cycle;
	uint16_t servo_difference = 1000; //calculated empirically for overshoot

  angle = (int) (servo_difference * angle / 90) + zero_dg_duty_cycle;
	TIM_SetCompare3(TIM2, angle);
}


/*!
@brief turn servo motor to an angle
@param angle the angle to be turned to
@pre servo PWM timer must be configured
@post Servo timer duty cycle changed to angle's cycle
The servo's duty cycle will be changed to a duty cycle
which turns the motor to the given angle.
*/
void turn_to_angle(float angle)
{
	//uint16_t servo_difference = ninety_dg_duty_cycle - zero_dg_duty_cycle;
	uint16_t servo_difference = 1000; //calculated empirically for overshoot

  angle = (int) (servo_difference * angle / 90) + zero_dg_duty_cycle;
	TIM_SetCompare4(TIM2, angle);
}
