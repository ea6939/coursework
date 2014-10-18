/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _keypad_driver
#define _keypad_driver
#endif

/* GPIO pin mapping */
#define KEYPAD_GPIO_CLK RCC_AHB1Periph_GPIOD
#define KEYPAD_GPIO_PORT GPIOD

#define KEYPAD_ROW0_PIN GPIO_Pin_0
#define KEYPAD_ROW1_PIN GPIO_Pin_1
#define KEYPAD_ROW2_PIN GPIO_Pin_2
#define KEYPAD_ROW3_PIN GPIO_Pin_3

#define KEYPAD_COLUMN0_PIN GPIO_Pin_6
#define KEYPAD_COLUMN1_PIN GPIO_Pin_7
#define KEYPAD_COLUMN2_PIN GPIO_Pin_8
#define KEYPAD_COLUMN3_PIN GPIO_Pin_9 

/* Data structures for keypad rows and columns */
#define KEYPAD_ROW uint16_t
#define KEYPAD_COLUMN uint16_t
#define KEYPAD_ERROR 'E'
#define KEYPAD_SEND_COMMAND 'D'
#define NO_KEYPAD_INPUT 'N'

#define KEYPAD_ROW0 0
#define KEYPAD_ROW1 1
#define KEYPAD_ROW2 2
#define KEYPAD_ROW3 3
#define KEYPAD_NO_ROW 4

#define KEYPAD_COLUMN0 0
#define KEYPAD_COLUMN1 1
#define KEYPAD_COLUMN2 2
#define KEYPAD_COLUMN3 3
#define KEYPAD_NO_COLUMN 4

typedef enum {MODE_IN = 0, MODE_OUT = !MODE_IN} KeyPinMode;
typedef enum {WAIT_FOR_INPUT = 0, WAIT_FOR_SEND_COMMAND = 1, SENDING = 2, INPUT_ERROR = 3, SEND_ERROR = 4, WAIT_FOR_BUTTON_RELEASE = 5} UserInputState;

char g2_read_keypad(void);
KEYPAD_ROW g2_poll_rows(void);
KEYPAD_COLUMN g2_poll_columns(void);
void g2_configure_rows(KeyPinMode);
void g2_configure_columns(KeyPinMode);
void g2_keypad_init(void);
char g2_decode_char(KEYPAD_ROW,KEYPAD_COLUMN);
