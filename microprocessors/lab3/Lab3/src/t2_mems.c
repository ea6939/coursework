#include "t2_mems.h"
#include <stm32f4xx.h>
#include "system_stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "lis3dsh.h"

EXTI_InitTypeDef   EXTI_InitStructure;
LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_Interrupt_InitStructure;

void t2_LIS3DSH_setup(void)
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
	
	/* activate the MEMS interrupts */
	LIS3DSH_Interrupt_InitStructure.Dataready_Interrupt =  LIS3DSH_DATA_READY_INTERRUPT_ENABLED;
	LIS3DSH_Interrupt_InitStructure.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL;
	LIS3DSH_Interrupt_InitStructure.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_PULSED;
	LIS3DSH_DataReadyInterruptConfig(&LIS3DSH_Interrupt_InitStructure);
}


/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  * Copied from example EXTI project.
  */
void EXTILine0_Config(void)
{
  
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable GPIOE clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PE0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // PE0 is hardwired to MEMS interrupt
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PE0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
