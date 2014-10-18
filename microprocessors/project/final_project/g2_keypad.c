/*!
* 
* @file g2_keypad.c
* @author Clark Gredona 260458872
* @author Harsh Aurora 260394216
* @author Loren Lugosch 260404057
* @author Radhika Chandra 260427945
* @brief Library for keypad functionality
*/

#include "stm32f4xx_gpio.h"
#include "g2_keypad.h"


/**
  * @brief  Reads the keypad press
  * @retval The corresponding char
  */
char g2_read_keypad() { 
	uint16_t row, col;
	row = g2_poll_rows();
	
	// if any row was high, reconfigure GPIOs and find the column
	if (row != KEYPAD_NO_ROW) {
		GPIO_SetBits(GPIOD,GPIO_Pin_12); // turn on LED
		
		g2_configure_rows(MODE_OUT);
		g2_configure_columns(MODE_IN);
		
		col = g2_poll_columns();
		
		char c = g2_decode_char(row,col);
		g2_configure_rows(MODE_IN);
		g2_configure_columns(MODE_OUT);
		return c;
	}
		
	else { 
		GPIO_ResetBits(GPIOD,GPIO_Pin_12); // turn off LED
		return NO_KEYPAD_INPUT;
	}
}

/**
  * @brief  Decodes character for a particular row and column
  * @retval The corresponding char
  */	
char g2_decode_char(KEYPAD_ROW row, KEYPAD_COLUMN col)
{
	switch (row) {
		case KEYPAD_ROW0:
			switch(col) {
				case KEYPAD_COLUMN0:
					return '1';
				case KEYPAD_COLUMN1:
					return '2';
				case KEYPAD_COLUMN2:
					return '3';
				case KEYPAD_COLUMN3:
					return 'A';
				default:
					return KEYPAD_ERROR;
			}
			
		case KEYPAD_ROW1:
			switch(col) {
				case KEYPAD_COLUMN0:
					return '4';
				case KEYPAD_COLUMN1:
					return '5';
				case KEYPAD_COLUMN2:
					return '6';
				case KEYPAD_COLUMN3:
					return 'B';
				default:
					return KEYPAD_ERROR;
			}
			
		case KEYPAD_ROW2:
			switch(col) {
				case KEYPAD_COLUMN0:
					return '7';
				case KEYPAD_COLUMN1:
					return '8';
				case KEYPAD_COLUMN2:
					return '9';
				case KEYPAD_COLUMN3:
					return 'C';
				default:
					return KEYPAD_ERROR;
			}
			
		case KEYPAD_ROW3:
			switch(col) {
				case KEYPAD_COLUMN0:
					return '*';
				case KEYPAD_COLUMN1:
					return '0';
				case KEYPAD_COLUMN2:
					return '#';
				case KEYPAD_COLUMN3:
					return 'D';
				default:
					return KEYPAD_ERROR;
			}
			
		default:
			return KEYPAD_ERROR;
	}
}

/**
  * @brief  Polls which row is pressed.  Only one row can be pressed at at time
  * @retval The corresponding row
  */
KEYPAD_ROW g2_poll_rows() 
{
	uint8_t row0status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_ROW0_PIN);
	uint8_t row1status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_ROW1_PIN);
	uint8_t row2status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_ROW2_PIN);
	uint8_t row3status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_ROW3_PIN);
	
	if (row0status == Bit_RESET) return KEYPAD_ROW0;
	if (row1status == Bit_RESET) return KEYPAD_ROW1;
	if (row2status == Bit_RESET) return KEYPAD_ROW2;
	if (row3status == Bit_RESET) return KEYPAD_ROW3;
	return KEYPAD_NO_ROW;
}

/**
  * @brief  Polls which column is pressed.  Only one row can be pressed at at time
  * @retval The corresponding row
  */
KEYPAD_COLUMN g2_poll_columns() 
{
	uint8_t col0status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_COLUMN0_PIN);
	uint8_t col1status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_COLUMN1_PIN);
	uint8_t col2status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_COLUMN2_PIN);
	uint8_t col3status = GPIO_ReadInputDataBit(KEYPAD_GPIO_PORT,KEYPAD_COLUMN3_PIN);
	
	if (col0status == Bit_RESET) return KEYPAD_COLUMN0;
	if (col1status == Bit_RESET) return KEYPAD_COLUMN1;
	if (col2status == Bit_RESET) return KEYPAD_COLUMN2;
	if (col3status == Bit_RESET) return KEYPAD_COLUMN3;
	return KEYPAD_NO_COLUMN;
}

/**
  * @brief  Configures the rows given a KeyPinMode
  * @param KeyPinmode: the key pin mode.  Can be either MODE_IN or MODE_OUT corresponding to GPIO mode
  * @retval None
  */
void g2_configure_rows(KeyPinMode mode) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = KEYPAD_ROW0_PIN | KEYPAD_ROW1_PIN | KEYPAD_ROW2_PIN | KEYPAD_ROW3_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	if (mode == MODE_OUT) {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	}
	else {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	}
		
	GPIO_Init(KEYPAD_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Configures the column given a KeyPinMode
  * @param KeyPinmode: the key pin mode.  Can be either MODE_IN or MODE_OUT corresponding to GPIO mode
  * @retval None
  */
void g2_configure_columns(KeyPinMode mode) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = KEYPAD_COLUMN0_PIN | KEYPAD_COLUMN1_PIN | KEYPAD_COLUMN2_PIN | KEYPAD_COLUMN3_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	if (mode == MODE_OUT) {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	}
	else {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	}
		
	GPIO_Init(KEYPAD_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Low level init of GPIO for keypad
  * @retval None
  */
void g2_keypad_init()
{
	RCC_AHB1PeriphClockCmd(KEYPAD_GPIO_CLK, ENABLE);
	
	g2_configure_rows(MODE_IN);
	g2_configure_columns(MODE_OUT);
    
    /* setup for onboard LED which flashes when keys are pressed */
    GPIO_InitTypeDef  GPIO_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
