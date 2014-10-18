/*!
* 
* @file g2_wireless.c
* @author Clark Gredona 260458872
* @author Harsh Aurora 260394216
* @author Loren Lugosch 260404057
* @author Radhika Chandra 260427945
* @brief Functionality for wireless transmission
*/

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "g2_wireless.h"
#include "smartrf_cc2500.h"

/**
  * @brief Low level setup of SPI and GPIO
  * @retval None
  */
void g2_wireless_gpio_spi_setup()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  /* Enable the SPI periph */
  RCC_APB2PeriphClockCmd(WIRELESS_SPI_CLK, ENABLE);

  /* Enable SCK, MOSI and MISO GPIO clocks */
  RCC_AHB1PeriphClockCmd(WIRELESS_SPI_SCK_GPIO_CLK | WIRELESS_SPI_MISO_GPIO_CLK | WIRELESS_SPI_MOSI_GPIO_CLK, ENABLE);

  /* Enable CS  GPIO clock */
  RCC_AHB1PeriphClockCmd(WIRELESS_SPI_CS_GPIO_CLK, ENABLE);
  
  /* Enable INT1 GPIO clock */
  //RCC_AHB1PeriphClockCmd(WIRELESS_SPI_INT1_GPIO_CLK, ENABLE);
  
  /* Enable INT2 GPIO clock */
  //RCC_AHB1PeriphClockCmd(WIRELESS_SPI_INT2_GPIO_CLK, ENABLE);

  GPIO_PinAFConfig(WIRELESS_SPI_SCK_GPIO_PORT, WIRELESS_SPI_SCK_SOURCE, WIRELESS_SPI_SCK_AF);
  GPIO_PinAFConfig(WIRELESS_SPI_MISO_GPIO_PORT, WIRELESS_SPI_MISO_SOURCE, WIRELESS_SPI_MISO_AF);
  GPIO_PinAFConfig(WIRELESS_SPI_MOSI_GPIO_PORT, WIRELESS_SPI_MOSI_SOURCE, WIRELESS_SPI_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = WIRELESS_SPI_SCK_PIN;
  GPIO_Init(WIRELESS_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  WIRELESS_SPI_MOSI_PIN;
  GPIO_Init(WIRELESS_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin = WIRELESS_SPI_MISO_PIN;
  GPIO_Init(WIRELESS_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(WIRELESS_SPI);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //max frequency used is 6.5 MHz for burst transmission, and 42 / 8 < 6.5
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(WIRELESS_SPI, &SPI_InitStructure);

  /* Enable SPI2  */
  SPI_Cmd(WIRELESS_SPI, ENABLE);

  /* Configure GPIO PIN for Lis Chip select */
  GPIO_InitStructure.GPIO_Pin = WIRELESS_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(WIRELESS_SPI_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Deselect : Chip Select high */
  GPIO_SetBits(WIRELESS_SPI_CS_GPIO_PORT, WIRELESS_SPI_CS_PIN);
  
  /* Configure GPIO PINs to detect Interrupts */
//   GPIO_InitStructure.GPIO_Pin = WIRELESS_SPI_INT1_PIN;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
//   GPIO_Init(WIRELESS_SPI_INT1_GPIO_PORT, &GPIO_InitStructure);
//   
//   GPIO_InitStructure.GPIO_Pin = WIRELESS_SPI_INT2_PIN;
//   GPIO_Init(WIRELESS_SPI_INT2_GPIO_PORT, &GPIO_InitStructure);
    
}




/**
  * @brief Sends data
	* @param data: the data to be sent
  * @retval None
  */
void g2_wireless_send_data(uint8_t data) 
{
    
    
	SPI_I2S_SendData(WIRELESS_SPI,data);
    
    
    //after first write, always need to wait for MISO (CHIP_RDYn) to go low before writing address header again
    //not sure if this is the best place to put this though
    
    /*while(SPI_I2S_ReceiveData(WIRELESS_SPI) & CHIP_RDYN_MASK) {

    }*/
    
}

/**
  * @brief  Configures the rows given a KeyPinMode
  * @param KeyPinmode: the key pin mode.  Can be either MODE_IN or MODE_OUT corresponding to GPIO mode
  * @retval None
  */
void g2_send_command_strobe(uint8_t command) {
    
    
}

/**
  * @brief  Configures the rows given a KeyPinMode
  * @param KeyPinmode: the key pin mode.  Can be either MODE_IN or MODE_OUT corresponding to GPIO mode
  * @retval None
  */
void g2_read_register(uint8_t address, uint8_t* result) {
    g2_wireless_send_data(address | READ_SINGLE);
    
    *result = SPI_I2S_ReceiveData(WIRELESS_SPI); //I'm not sure if this will read the register at the specified address or the status byte.
    

}    
