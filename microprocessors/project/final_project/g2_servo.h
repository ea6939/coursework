#define SERVO_TIMER_ARR 19999 // 20000 - 1 
#define SERVO_TIMER_PRESCALER 83 // 70 - 1 (divide bus freq by prescaler to get 1MHz)
#define TIMER_BUS_FREQUENCY 84000000 // 84 Mhz

void servo_TIM_Config(void);
void servo_setup(void);
void servo_setup2(void);
void turn_to_angle(float angle);
void turn_to_angle2(float angle);
