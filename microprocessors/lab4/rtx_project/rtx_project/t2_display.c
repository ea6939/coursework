/*!
@file t2_display.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for controlling 7-segment displays
*/

#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "t2_display.h"
#include "t2_gpio.h"
#include "cmsis_os.h"

int timer = 0; 
uint16_t PrescalerValue = 0; 
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
TIM_OCInitTypeDef  TIM_OCInitStructure; 


/*!
@brief Sets up 7-segment
@post GPIO pins 0,1,2,4,5,7,8,11,12,13,14 will be set up as output pins.
Sets up a configuration of pins for a 7-segment display.
*/
void seven_segment_GPIO_setup(void)
{
	GPIO_InitTypeDef gpio_init_s;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // enable port B

	gpio_init_s.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
	gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull

	GPIO_Init(GPIOB, &gpio_init_s); // configure the pin
	
	 /* Set timer for the displays */
  //TIM_Config(); 
}

/*!
@brief Display a digit on a 7-segment
@param num digit to be displayed
@pre GPIOB pins must be set up by seven_segment_GPIO_setup()
@pre 7-segment must be set up such that SEGMENT_1 is wired to the 1 pin of a 7-segment display, etc.
@post 7-segment will display the input digit
Display a digit on a 7-segment.
*/
void display_number(int num)
{
	switch (num) {
		case 0: //123567
			
			GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_5,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		
		case 1: //36
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			break;
		
		case 2: //23457
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_5,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		
		case 3: //23467
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		
		case 4: //1346
			GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			break;
		
		case 5: //12467
			GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		
		case 6: //124567
			GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_5,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		
		case 7: //236
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			break;
		
		case 8: //1234567
			GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_5,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		
		case 9: //123467
			GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_SET);
			GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_SET);
			break;
		case -1: // 4
			GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_SET);
			break;
		
		default:
			break;
	}
}

/*!
@brief Selects one of 3 seven segment displays
@param select which display to activate
@pre GPIOB must be set up, DISPLAY_1 etc. must be wired to valid bits
@post the appropriate display will be activated
Selects one of 3 seven segment displays by sending a SET/RESET signal to the npn transistors.
*/
void select_display(int select)
{
	switch(select) {
		case 1:
			GPIO_WriteBit(GPIOB,DISPLAY_1,Bit_SET);
			GPIO_WriteBit(GPIOB,DISPLAY_2,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_3,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_4,Bit_RESET);
			break;
		
		case 2:
			GPIO_WriteBit(GPIOB,DISPLAY_1,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_2,Bit_SET);
			GPIO_WriteBit(GPIOB,DISPLAY_3,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_4,Bit_RESET);
			break;
		
		case 3:
			GPIO_WriteBit(GPIOB,DISPLAY_1,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_2,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_3,Bit_SET);
			GPIO_WriteBit(GPIOB,DISPLAY_4,Bit_RESET);
			break;
		
		case 4:
			GPIO_WriteBit(GPIOB,DISPLAY_1,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_2,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_3,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_4,Bit_SET);
			break;
		
		default:
			GPIO_WriteBit(GPIOB,DISPLAY_1,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_2,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_3,Bit_RESET);
			GPIO_WriteBit(GPIOB,DISPLAY_4,Bit_RESET);
			break;
	}
}


/*!
@brief Clears a 7-segment
@pre valid GPIOs
@post 7-segment will be blank
Blanks out a 7-segment display.
*/
void clear_display()
{
		GPIO_WriteBit(GPIOB,SEGMENT_1,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_2,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_3,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_4,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_5,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_6,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_7,Bit_RESET);
		GPIO_WriteBit(GPIOB,SEGMENT_8,Bit_RESET);
}

/*!
@brief Displays a 3 digit number
@param temp the value to be displayed
@return 
@pre temp must be a three-digit (one decimal place) number
@post the sampling frequency must be slow enough that this method and the subsequent instructions
in the main method's while-loop finish before a new SysTick interrupt is generated
(otherwise, the program won't really have the advertised sampling frequency).

Displays temperature on a 3-digit display by flashing each digit to each display in succession.
*/
void display_multidigit_number(float temp) 
{
	/* determine if negative */
	int negative = 0;
	if (temp < 0) {
		negative = 1; 
		temp = -temp;
	}
		
	/* Get three digits from temp */
	int temp_rounded = (temp * 100) / 10;
	int first_digit = temp_rounded / 100;
	int second_digit = (temp_rounded - (first_digit * 100)) / 10;
	int third_digit = (temp_rounded - (first_digit * 100) - (second_digit * 10));
	
	/* write first digit to display */

	clear_display();
	select_display(1);
	display_number(first_digit);
	osDelay(3);//while(!timer); // need delay to give the LEDs more time to light up during switching 
  timer = 0; 
	
	/* write second digit to display */
	clear_display();
	select_display(2);
	display_number(second_digit);
	GPIO_WriteBit(GPIOB,SEGMENT_8,Bit_SET); // decimal point
	osDelay(3);//while(!timer);
  timer = 0; 
	
	/* write second digit to display */
	clear_display();
	select_display(3);
	display_number(third_digit);
	osDelay(3); // while(!timer); 
  timer = 0; 
	
	/* display negative sign if necessary */
	if (negative) {
		clear_display();
		select_display(4);
		display_number(-1);
		osDelay(3); // while(!timer); // need delay to give the LEDs more time to light up during switching 
    timer = 0; 
	}
	
  clear_display(); // needed to make sure display 3 doesn't remain on during all the subsequent
                    // instructions before the next display
}

