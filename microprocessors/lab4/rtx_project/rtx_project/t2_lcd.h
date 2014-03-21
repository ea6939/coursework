void t2_lcd_setup(void);
void t2_lcd_draw_char(char, uint16_t);
void t2_lcd_draw_string(char *, int);
void t2_send_enable_pulse(void);
void t2_lcd_command(char c);

#define RS_PIN GPIO_Pin_0 // pin 4 (Register Select)
#define EN_PIN GPIO_Pin_2 // pin 6 (Enable)
#define RW_PIN GPIO_Pin_4 // pin 5 (Read/Write)
#define D0_PIN GPIO_Pin_11 // pin 7
#define D1_PIN GPIO_Pin_1 // pin 8
#define D2_PIN GPIO_Pin_5 // pin 9
#define D3_PIN GPIO_Pin_12 // pin 10
#define D4_PIN GPIO_Pin_13 // pin 11
#define D5_PIN GPIO_Pin_7 // pin 12
#define D6_PIN GPIO_Pin_14 // pin 13
#define D7_PIN GPIO_Pin_8 // pin 14

#define LCD_DISPLAY_ON 0x0c
#define LCD_FUNCTION_SET 0x38
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_CR 0xC0
#define LCD_CURSOR_HOME 0x02
