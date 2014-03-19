#include <stm32f4xx.h>
#include "lis3dsh.h"

void t2_LIS3DSH_setup(void);
uint8_t accel_data_ready(void);
void EXTILine0_Config(void);
