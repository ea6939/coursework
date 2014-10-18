/*!
@file g2_mems.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for orientation using accelerometer
*/

#include "g2_mems.h"
#include "math.h"
#include "atan_LUT.h"
#include "g2_filtering.h"
#include <stm32f4xx.h>
#include "system_stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "lis3dsh.h"

#define X_UP 0
#define X_DOWN 1
#define Y_UP 2
#define Y_DOWN 3
#define Z_UP 4
#define Z_DOWN 5
#define D 10

EXTI_InitTypeDef   EXTI_InitStructure;
LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_Interrupt_InitStructure;

float offset[3] = {30.7, 12.3, 40.0}; //{0};

float accel[3];
float filtered_accel[3]; // x,y,z after filtering
float accel_samples_x[D]; //filtered samples of x dimension in array
float accel_samples_y[D]; //filtered samples of y dimension in array
float accel_samples_z[D]; //filtered samples of z dimension in array

/*!
@brief MEMS accel'r setup
@post Accelerometer will be set up with 3 axes and 100 Hz sampling
The accelerometer is configured to sample (but not to give interrupts)
*/
void g2_LIS3DSH_setup(void)
{
	/* configure the accelerometer */
	LIS3DSH_InitTypeDef MEMS_SETUP;

	MEMS_SETUP.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_100; // 100 Hz sampling frequency
	MEMS_SETUP.Axes_Enable = LIS3DSH_X_ENABLE | LIS3DSH_Y_ENABLE | LIS3DSH_Z_ENABLE; // all three axes
	MEMS_SETUP.Continous_Update  = LIS3DSH_ContinousUpdate_Disabled;
	MEMS_SETUP.AA_Filter_BW = LIS3DSH_AA_BW_800; // since "DC" application, AA filter doesn't matter
	MEMS_SETUP.Full_Scale = LIS3DSH_FULLSCALE_4;
	MEMS_SETUP.Self_Test = LIS3DSH_SELFTEST_NORMAL; // allows user to check functionality of sensor (don't use)

	LIS3DSH_Init(&MEMS_SETUP); //we'll need this to activate SPI

	// no MEMS interrupts
	LIS3DSH_Interrupt_InitStructure.Dataready_Interrupt =  LIS3DSH_DATA_READY_INTERRUPT_DISABLED;
	LIS3DSH_DataReadyInterruptConfig(&LIS3DSH_Interrupt_InitStructure);
}

/*!
@brief Get new values and filter
@post accel will contain latest sample, filtered_accel will contain a value
Check if data ready, then sample the accelerometer, then filter.
*/
void update_orientation() 
{ 
	while(LIS3DSH_STATUS && 0x04 != 0x04); // check if ready
	LIS3DSH_ReadACC(accel);

	for (int i = 0; i < 3; i++) { accel[i] -= offset[i]; } // subtract calibration offset
  shift_in_float_value(accel[0], accel_samples_x, &filtered_accel[0], D);
  shift_in_float_value(accel[1], accel_samples_y, &filtered_accel[1], D);
  shift_in_float_value(accel[2], accel_samples_z, &filtered_accel[2], D);
}

/*!
@brief Calculates and returns pitch using filtered acceleration values.
*/
float get_pitch()
{
	return atan_table((filtered_accel[0])/sqrt((filtered_accel[1]*filtered_accel[1])+(filtered_accel[2]*filtered_accel[2])));
}

/*!
@brief Calculates and returns roll using filtered acceleration values.
*/
float get_roll()
{
	return atan_table((filtered_accel[1])/sqrt((filtered_accel[0]*filtered_accel[0])+(filtered_accel[2]*filtered_accel[2])));
}

/*!
@brief Calculates offset values by averaging in a certain position.
Offsets can then be read off and written into the program by hand.
*/
void calibrate_mems_sensor(int calibration_position, int ready)
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
    
		update_orientation(); // don't need the return
	}
}

/*!
@brief Sets up 100 Hz sampling interrupts.
@post Timer configured at 100 Hz
Sets up timer for MEMS at appropriate sampling frequency. 
*/
void MEMS_TIM5_Configuration(void){

	uint16_t PrescalerValue = 0;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_ClocksTypeDef RCC_ClockFreq;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_GetClocksFreq(&RCC_ClockFreq);
	PrescalerValue = (uint16_t) (RCC_ClockFreq.PCLK1_Frequency / 1000) - 1;

	TIM_TimeBaseStructure.TIM_Period = 20;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef   NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM5, ENABLE);
}
