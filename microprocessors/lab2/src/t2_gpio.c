#include "t2_gpio.h"
#include <stm32f4xx.h>

/*!
@file t2_gpio.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for GPIO generic functions.
*/

/*!
@brief Onboard LED GPIO
@post GPIOD pin 12 will be usable 
Activates the onboard LEDs' GPIO.
*/
void onboard_LED_GPIO_setup(void)
{

	GPIO_InitTypeDef gpio_init_s;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // enable port D

	gpio_init_s.GPIO_Pin = GPIO_Pin_12;// Select pin 12
	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
	gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull

	GPIO_Init(GPIOD, &gpio_init_s); // configure the pin
}

