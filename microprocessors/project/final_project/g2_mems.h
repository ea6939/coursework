#include <stm32f4xx.h>
#include "lis3dsh.h"

void g2_LIS3DSH_setup(void);
uint8_t accel_data_ready(void);
//void EXTILine0_Config(void);
void MEMS_TIM5_Configuration(void);
void calibrate_mems_sensor(int, int);
void read_accel(void);
void update_orientation(void);
float get_pitch(void);
float get_roll(void);
