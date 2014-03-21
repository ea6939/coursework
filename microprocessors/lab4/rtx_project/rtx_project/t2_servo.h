#define SERVO_TIMER_ARR 19999 // 20000 - 1 
#define SERVO_TIMER_PRESCALER 83 // 70 - 1 (divide bus freq by prescaler to get 1MHz)
#define TIMER_BUS_FREQUENCY 84000000 // 84 Mhz

void servo_TIM_Config(void);
void servo_setup(void);
void turn_to_angle(float angle);
