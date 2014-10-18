/**
  * @file    lcd.h
	* @author  Harsh Aurora
	* @date    20-March-2014
	* @version 1.0
	* @brief   Function prototypes for LCD driver
	*
	*/

/* Define to prevent recursive inclusion */
#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/* LCD GPIO Pin mapping */
#define LCD_CTRL_GPIO_CLK  RCC_AHB1Periph_GPIOB
#define LCD_CTRL_GPIO_PORT GPIOB
#define LCD_CTRL_RS_PIN    GPIO_Pin_0
#define LCD_CTRL_RW_PIN    GPIO_Pin_1
#define LCD_CTRL_EN_PIN    GPIO_Pin_2

#define LCD_DATA_GPIO_CLK  RCC_AHB1Periph_GPIOE
#define LCD_DATA_GPIO_PORT GPIOE
#define LCD_DATA_D0_PIN    GPIO_Pin_7
#define LCD_DATA_D1_PIN    GPIO_Pin_8
#define LCD_DATA_D2_PIN    GPIO_Pin_9
#define LCD_DATA_D3_PIN    GPIO_Pin_10
#define LCD_DATA_D4_PIN    GPIO_Pin_11
#define LCD_DATA_D5_PIN    GPIO_Pin_12
#define LCD_DATA_D6_PIN    GPIO_Pin_13
#define LCD_DATA_D7_PIN    GPIO_Pin_14

/* Delay values */
#define LCD_DELAY_SHORT	40
#define LCD_DELAY_LONG  1500

/* Command bit enums */
#define LCD_CMDBIT0 ((uint8_t)0x01)
#define LCD_CMDBIT1 ((uint8_t)0x02)
#define LCD_CMDBIT2 ((uint8_t)0x04)
#define LCD_CMDBIT3 ((uint8_t)0x08)
#define LCD_CMDBIT4 ((uint8_t)0x10)
#define LCD_CMDBIT5 ((uint8_t)0x20)
#define LCD_CMDBIT6 ((uint8_t)0x40)
#define LCD_CMDBIT7 ((uint8_t)0x80)

#define LCD_ADDR_MASK ((uint8_t)0xBF)
#define LCD_MAX_ADDR  ((uint8_t)0x17)
#define LCD_LN1_ADDR  ((uint8_t)0x00)
#define LCD_LN2_ADDR  ((uint8_t)0x40)

/**/
typedef enum {LCD_OFF = 0, LCD_ON = !LCD_OFF} LCD_State;
typedef enum {DECREASE = 0, INCREASE = !DECREASE} LCD_IncrDecr;
typedef enum {CURSOR_SHIFT = 0, DISPLAY_SHIFT = !CURSOR_SHIFT} LCD_ShiftSettings;
typedef enum {LEFT = 0, RIGHT = !LEFT} LCD_ShiftDirection;
typedef enum {BITS_4 = 0, BITS_8 = !BITS_4} LCD_DataLength;
typedef enum {LINES_1 = 0, LINES_2 = !LINES_1} LCD_LineMode;
typedef enum {CHAR_5x7 = 0, CHAR_5x10= !CHAR_5x7} LCD_CharSize;

/**/
typedef struct {
	LCD_IncrDecr IncrDecr;
	LCD_State DisplayShiftEn;
	LCD_ShiftSettings ShiftSettings;
	LCD_ShiftDirection ShiftDirection;
	LCD_DataLength DataLength;
	LCD_LineMode LineMode;
	LCD_CharSize CharSize;
} LCD_SettingsTypeDef;

typedef struct {
  LCD_State DisplayEnable;
	LCD_State CursorUnderline;
	LCD_State CursorBlink;
  uint8_t Address;
} LCD_DisplayTypeDef;

void LCD_Init(LCD_DisplayTypeDef* LCD);
void LCD_ConfigureSettings(LCD_SettingsTypeDef* LCD);
void LCD_ConfigureDisplay(LCD_DisplayTypeDef* LCD);
void LCD_ClearDisplay(LCD_DisplayTypeDef* LCD);
void LCD_ReturnHome(LCD_DisplayTypeDef* LCD);
uint8_t LCD_SetDisplayAddress(LCD_DisplayTypeDef *LCD, uint8_t address);
void LCD_WriteChar(LCD_DisplayTypeDef *LCD, char c);
void LCD_WriteString(LCD_DisplayTypeDef *LCD, char* string);

#endif
