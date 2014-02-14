#define DISPLAY_1 GPIO_Pin_0
#define DISPLAY_2 GPIO_Pin_2
#define DISPLAY_3 GPIO_Pin_4

#define SEGMENT_1 GPIO_Pin_11
#define SEGMENT_2 GPIO_Pin_1
#define SEGMENT_3 GPIO_Pin_5
#define SEGMENT_4 GPIO_Pin_12
#define SEGMENT_5 GPIO_Pin_13
#define SEGMENT_6 GPIO_Pin_7
#define SEGMENT_7 GPIO_Pin_14
#define SEGMENT_8 GPIO_Pin_8

/* Pin mappings can be changed; check Discovery Board Manual for free pins */

void seven_segment_GPIO_setup(void);
void display_number(int num);
void select_display(int select);
void clear_display(void);
void display_multidigit_number(float temp);
void delay(int n);
