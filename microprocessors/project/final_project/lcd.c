/**
  * @file    lcd.c
	* @author  Harsh Aurora
	* @date    20-March-2014
	* @version 1.0
	* @brief   Driver methods for LCD screen
	*
	*/

/* includes */
#include "lcd.h"

/**
  * @brief  Function to initialize the GPIO pins and sotre initial LCD screen settings
  * @param  LCD: The LCD screen LCD_TypeDef struct to update
	* @retval None
  */
void LCD_Init(LCD_DisplayTypeDef* LCD) {
	GPIO_InitTypeDef   GPIO_InitStructure;

	/* enable control pins GPIO clock */
	RCC_AHB1PeriphClockCmd(LCD_CTRL_GPIO_CLK, ENABLE);	
		
	/* enable data pins GPIO clock */
	RCC_AHB1PeriphClockCmd(LCD_DATA_GPIO_CLK, ENABLE);

	/* configure pins as output, pull down, 2MHz */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;         
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	/* initialize the control pins */ 
	GPIO_InitStructure.GPIO_Pin = LCD_CTRL_RS_PIN|LCD_CTRL_RW_PIN|LCD_CTRL_EN_PIN;             
	GPIO_Init(LCD_CTRL_GPIO_PORT, &GPIO_InitStructure);
	
	/* initialize the data pins */
	GPIO_InitStructure.GPIO_Pin = LCD_DATA_D0_PIN|LCD_DATA_D1_PIN|LCD_DATA_D2_PIN|LCD_DATA_D3_PIN|\
															  LCD_DATA_D4_PIN|LCD_DATA_D5_PIN|LCD_DATA_D6_PIN|LCD_DATA_D7_PIN;             
	GPIO_Init(LCD_DATA_GPIO_PORT, &GPIO_InitStructure);
	


  LCD_ConfigureDisplay(LCD);
	LCD_ClearDisplay(LCD);
  LCD_ReturnHome(LCD);
}

/**
  * @brief  Fucntion that sets the data pins D0-D7
	* @param  data: The value of the pins (LSB = D0) 
	* @retval None
  */
void LCD_SetDataPins(uint8_t data) {
 if (data & 0x01)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D0_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D0_PIN);
		
 if (data & 0x02)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D1_PIN);
 else
  GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D1_PIN);
		
 if (data & 0x04)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D2_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D2_PIN);
		
 if (data & 0x08)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D3_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D3_PIN);
		
 if (data & 0x10)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D4_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D4_PIN);
		
 if (data & 0x20)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D5_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D5_PIN);
		
 if (data & 0x40)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D6_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D6_PIN);
		
 if (data & 0x80)
	GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D7_PIN);
 else
	GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_D7_PIN);
}

/**
  * @brief  Function to generate a programmable delay
	* @param  microseconds: approx delay in microseconds
	* @retval None
  */
void LCD_Delay(uint16_t microseconds) {
	uint32_t i = 0;
	uint32_t iterations = (uint32_t)(microseconds<<9);
	while(i < iterations)
		i++;
}

/**
  * @brief  Sends an enable pulse to the LCD  
	* @retval None
  */
void LCD_Enable(void) {
 uint8_t hold;
 GPIO_SetBits(LCD_CTRL_GPIO_PORT, LCD_CTRL_EN_PIN);
 for(hold = 0; hold < 255; hold++); //delay hold pulse
 GPIO_ResetBits(LCD_CTRL_GPIO_PORT, LCD_CTRL_EN_PIN);
}

/**
  * @brief  Function to set the RS control pin in data mode 
	* @retval None
  */
void LCD_SetRS_DATA(void) {
	 GPIO_SetBits(LCD_CTRL_GPIO_PORT, LCD_CTRL_RS_PIN);
}


/**
  * @brief  Function to set the RS control pin in command mode
	* @retval None
  */
void LCD_SetRS_COMMAND(void) {
	 GPIO_ResetBits(LCD_CTRL_GPIO_PORT, LCD_CTRL_RS_PIN);
}


/**
  * @brief  Function to set the RW control pin in read mode 
	* @retval None
  */
void LCD_SetRW_READ(void) {
	GPIO_SetBits(LCD_CTRL_GPIO_PORT, LCD_CTRL_RW_PIN);
}


/**
  * @brief  Function to set the RW control pin in write mode 
	* @retval None
  */
void LCD_SetRW_WRITE(void) {
	GPIO_ResetBits(LCD_CTRL_GPIO_PORT, LCD_CTRL_RW_PIN);
}


/**
  * @brief  Function to clear the LCD display
	* @retval None
  */
void LCD_ClearDisplay(LCD_DisplayTypeDef* LCD) {
	uint8_t command = LCD_CMDBIT0;
  LCD->Address = (uint8_t)0x00;
	LCD_SetRS_COMMAND();
	LCD_SetDataPins(command);
	LCD_Enable();
	LCD_Delay(LCD_DELAY_LONG);
}


/**
  * @brief  Function to return the cursor to the first address 
	* @retval None
  */
void LCD_ReturnHome(LCD_DisplayTypeDef* LCD) {
	uint8_t command = LCD_CMDBIT1;
  LCD->Address = (uint8_t)0x00;
	LCD_SetRS_COMMAND();
	LCD_SetDataPins(command);
	LCD_Enable();
	LCD_Delay(LCD_DELAY_LONG);
}
/**
  */
void LCD_ConfigureSettings(LCD_SettingsTypeDef *LCD) {
  uint8_t command;
	
  command = LCD_CMDBIT2;
	if(LCD->DisplayShiftEn == LCD_ON)
		command|= LCD_CMDBIT0;
	
	if(LCD->IncrDecr == INCREASE)
		command|= LCD_CMDBIT1;
	
	LCD_SetRS_COMMAND();
	LCD_SetDataPins(command);
	LCD_Enable();
	LCD_Delay(LCD_DELAY_SHORT);
  
  command = LCD_CMDBIT4;
	if(LCD->ShiftSettings == DISPLAY_SHIFT)
		command|= LCD_CMDBIT3;
  
	if(LCD->ShiftDirection == RIGHT)
		command|= LCD_CMDBIT2;
	
	LCD_SetRS_COMMAND();
	LCD_SetDataPins(command);
	LCD_Enable();
	LCD_Delay(LCD_DELAY_SHORT);

  command = LCD_CMDBIT5;
	if(LCD->DataLength == BITS_8)
		command|= LCD_CMDBIT4;

	if(LCD->LineMode == LINES_2)
		command|= LCD_CMDBIT3;
	
	if(LCD->CharSize == CHAR_5x10)
		command|= LCD_CMDBIT2;

	LCD_SetRS_COMMAND();
	LCD_SetDataPins(command);
	LCD_Enable();
	LCD_Delay(LCD_DELAY_SHORT);
}

/**
  */
void LCD_ConfigureDisplay(LCD_DisplayTypeDef *LCD) {
  uint8_t command = LCD_CMDBIT3;
	
	if(LCD->DisplayEnable == LCD_ON)
		command|= LCD_CMDBIT2;

	if(LCD->CursorUnderline == LCD_ON)
		command|= LCD_CMDBIT1;
	
	if(LCD->CursorBlink == LCD_ON)
		command|= LCD_CMDBIT0;
	
	LCD_SetRS_COMMAND();
	LCD_SetDataPins(command);
	LCD_Enable();
	LCD_Delay(LCD_DELAY_SHORT);
}

/**
  * @brief  Sets the address of the cursor on the display
	* @param  LCD: The address to set the cursor to
	* @retval None
  */
uint8_t LCD_SetDisplayAddress(LCD_DisplayTypeDef *LCD, uint8_t address) {
	uint8_t command = LCD_CMDBIT7;
	
  if((address & LCD_ADDR_MASK) <= LCD_MAX_ADDR) {
    LCD->Address = address;
    command|= address;
    LCD_SetDataPins(command);
    LCD_SetRS_COMMAND();
    LCD_Enable();
    LCD_Delay(LCD_DELAY_SHORT);
    return 1;
  }
  return 0;
}


/**
  * @brief  Write a char to the LCD screen
	* @param  char: The char to write
	* @retval None
  */
void LCD_WriteChar(LCD_DisplayTypeDef *LCD, char c) {
  LCD_SetDataPins((uint8_t)c);
  LCD_SetRS_DATA();
  LCD_Enable();
  LCD_Delay(LCD_DELAY_SHORT);
  
  if(((LCD->Address) & LCD_ADDR_MASK) < LCD_MAX_ADDR)
    (LCD->Address)++;
  else {
    if(((LCD->Address) & LCD_LN2_ADDR) == LCD_LN2_ADDR)
      LCD_SetDisplayAddress(LCD, LCD_LN1_ADDR);
    else
      LCD_SetDisplayAddress(LCD, LCD_LN2_ADDR);
  }
}
	
/**
  * @brief  Write a string to the LCD screen
	* @param  string: The string to write
	* @retval None
  */
void LCD_WriteString(LCD_DisplayTypeDef *LCD, char* string) {
	while(*string != '\0') {
		LCD_WriteChar(LCD, *string);
		string++;
	}
}
