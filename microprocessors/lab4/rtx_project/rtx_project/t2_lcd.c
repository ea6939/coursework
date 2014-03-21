/*!
@file t2_lcd.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Driver for Lumex LCD display.
*/

#include "stm32f4xx.h"
#include "t2_lcd.h"
#include "cmsis_os.h"

/*!
@brief LCD GPIO setup
@post GPIO pins 0,1,2,4,5,7,8,11,12,13,14 will be set up as output pins.
Sets up a configuration of pins for an LCD.
*/
void t2_lcd_setup()
{
	// GPIO setup
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = D0_PIN | D1_PIN | D2_PIN | D3_PIN | D4_PIN | D5_PIN | D6_PIN | D7_PIN | RS_PIN | RW_PIN | EN_PIN ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct); 			
}

/*!
@brief send LCD command
@param c 8-bit command code
@pre LCD GPIOs must be set up
@post Command sent to LCD
The bits of the command c are put on the data lines of the LCD
RS and RW are set to 0
An enable pulse sends the command
*/
void t2_lcd_command(char c)
{
		// draws 0 (zer)
	GPIO_WriteBit(GPIOB,D0_PIN,c & 0x1);
	GPIO_WriteBit(GPIOB,D1_PIN,c & 0x2);
	GPIO_WriteBit(GPIOB,D2_PIN,c & 0x4);
	GPIO_WriteBit(GPIOB,D3_PIN,c & 0x8);
	GPIO_WriteBit(GPIOB,D4_PIN,c & 0x10);
	GPIO_WriteBit(GPIOB,D5_PIN,c & 0x20);
	GPIO_WriteBit(GPIOB,D6_PIN,c & 0x40);
	GPIO_WriteBit(GPIOB,D7_PIN,c & 0x80);
	
	GPIO_WriteBit(GPIOB,RS_PIN,Bit_RESET);
	GPIO_WriteBit(GPIOB,RW_PIN,Bit_RESET);
	t2_send_enable_pulse();
	
}

/*!
@brief send LCD char
@param c 8-bit char
@pre LCD GPIOs must be set up
@post Char sent to LCD and printed there
The bits of the char c are put on the data lines of the LCD
RS and RW are set to 10
An enable pulse sends the command
*/
void t2_lcd_draw_char(char c, uint16_t pos)
{
	// draws 0 (zer)
	GPIO_WriteBit(GPIOB,D0_PIN,c & 0x1);
	GPIO_WriteBit(GPIOB,D1_PIN,c & 0x2);
	GPIO_WriteBit(GPIOB,D2_PIN,c & 0x4);
	GPIO_WriteBit(GPIOB,D3_PIN,c & 0x8);
	GPIO_WriteBit(GPIOB,D4_PIN,c & 0x10);
	GPIO_WriteBit(GPIOB,D5_PIN,c & 0x20);
	GPIO_WriteBit(GPIOB,D6_PIN,c & 0x40);
	GPIO_WriteBit(GPIOB,D7_PIN,c & 0x80);
	
	GPIO_WriteBit(GPIOB,RS_PIN,Bit_SET);
	GPIO_WriteBit(GPIOB,RW_PIN,Bit_RESET);
	t2_send_enable_pulse();
}

/*!
@brief print string on LCD
@param buffer string of chars; size number of chars
@pre LCD GPIOs must be set up
@post String sent to LCD and printed there
Each char is printed successively
*/
void t2_lcd_draw_string(char * buffer, int size)
{
	for (int i = 0; i < size; i++) {
		t2_lcd_draw_char(buffer[i], 0);
	}
}

/*!
@brief enable transfer
@pre LCD GPIOs must be set up
@post Char sent to LCD and printed there
On the falling edge of an ENABLE pulse, the LCD register latches data from the data bits
This method generates that pulse by toggling the line over a 1ms period
*/
void t2_send_enable_pulse()
{
	// Toggle EN pin (pin 6)
	GPIO_WriteBit(GPIOB,EN_PIN,Bit_SET);
	osDelay(1);
	GPIO_WriteBit(GPIOB,EN_PIN,Bit_RESET);
}
