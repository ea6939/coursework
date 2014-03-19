/*!
@file main.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Lab 3 main program.
*/

//#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "math.h"
#include "atan_LUT.h"
#include "t2_mems.h"
#include "lis3dsh.h"
#include "t2_gpio.h"
#include "t2_display.h"
#include "t2_servo.h"
#include "t2_filtering.h"
//#include "stm32f4_discovery_lis302dl.h"

#define X_UP 0
#define X_DOWN 1
#define Y_UP 2
#define Y_DOWN 3
#define Z_UP 4
#define Z_DOWN 5
#define D 10

void calibrate_mems_sensor(int);
void update_angles(void);

float accel[3]; // 0 - x, 1 - y, 2 - z
float filtered_accel[3]; // x,y,z after filtering
float accel_samples_x[D]; //filtered samples of x dimension in array
float accel_samples_y[D]; //filtered samples of y dimension in array
float accel_samples_z[D]; //filtered samples of z dimension in array
float offset[3] = {30.7, 12.3, 40.0}; //{0};
float pitch;
float roll;
int ready = 0;


void EXTI0_IRQHandler(void)
{
	ready = 1;
	EXTI_ClearITPendingBit(EXTI_Line0);
}

int main()
{
	t2_LIS3DSH_setup(); // setup accel, accel interrupts
	EXTILine0_Config();
	seven_segment_GPIO_setup();
  //calibrate_mems_sensor(Z_UP);
	servo_setup();
	
	while(1){
		if (ready) {
			ready = 0;
			update_angles();
			turn_to_angle(pitch);
		}
		display_multidigit_number(pitch);
	}
}

void update_angles(void)
{
	LIS3DSH_ReadACC(accel);
	for (int i = 0; i < 3; i++) { accel[i] -= offset[i]; } // subtract calibration offset
  shift_in_float_value(accel[0], accel_samples_x, &filtered_accel[0], D);
  shift_in_float_value(accel[1], accel_samples_y, &filtered_accel[1], D);
  shift_in_float_value(accel[2], accel_samples_z, &filtered_accel[2], D);
			
	pitch = atan_table((filtered_accel[0])/sqrt((filtered_accel[1]*filtered_accel[1])+(filtered_accel[2]*filtered_accel[2])));
	roll = atan_table((filtered_accel[1])/sqrt((filtered_accel[0]*filtered_accel[0])+(filtered_accel[2]*filtered_accel[2])));
}

void calibrate_mems_sensor(int calibration_position)
{
	int number_of_samples_acquired = 0;
	offset[0] = 0;
	offset[1] = 0;
	offset[2] = 0;
	int x_g, y_g, z_g = 0;
	
	switch(calibration_position){
		case X_UP:
			x_g = 1000;
			break;
		case X_DOWN:
			x_g = -1000;
			break;
		case Y_UP:
			y_g = 1000;
			break;
		case Y_DOWN:
			y_g = -1000;
			break;
		case Z_UP:
			z_g = 1000;
			break;
		case Z_DOWN:
			z_g = -1000;
			break;
		default:
			break;
	}
	while(1) {
    while(!ready);
		LIS3DSH_ReadACC(accel);
		number_of_samples_acquired++;
		if (fabs(accel[0]) < 10000) { offset[0] = ((number_of_samples_acquired - 1) * offset[0] + (accel[0] - x_g))/number_of_samples_acquired; }
		offset[1] = ((number_of_samples_acquired - 1) * offset[1] + (accel[1] - y_g))/number_of_samples_acquired;
		offset[2] = ((number_of_samples_acquired - 1) * offset[2] + (accel[2] - z_g))/number_of_samples_acquired;
    
		
		update_angles();
	}
}



