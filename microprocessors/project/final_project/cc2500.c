/*!
* 
* @file g2_keypad.c
* @author Clark Gredona 260458872
* @author Harsh Aurora 260394216
* @author Loren Lugosch 260404057
* @author Radhika Chandra 260427945
* @brief Another library for wireless functinoality
*/


#include "cc2500.h"
#include "smartrf_cc2500.h"
#include "g2_wireless.h"

/* READ = 0x80, WRITE = 0x00 */
#define READWRITE_CMD              ((uint8_t)0x80)
/* BURST/STATUS = 0x40, NO BURST/STATUS = 0x00 */
#define BURSTSTATUS_CMD                  ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x3D)
/* timeout count */
#define CC2500_TIMEOUT  (uint32_t)0xffffffff

#define CC2500_CHIP_RDYn 0x80


uint32_t cc2500_timeout;


uint8_t CC2500_SendByte(uint8_t byte);
void CC2500_LowLevelInit(void);
void CC2500_ChipRDYn(void);
//uint8_t assert_address();


/**
  * @brief  Low level init and additional config
  * @retval None
  */
void CC2500_Init(void) {

  CC2500_LowLevelInit();
	CC2500_ChipsetConfig();
}

/**
  * @brief  Reads status reg
	* @param StatusAddr: The address of the 
  * @retval None
  */
uint8_t CC2500_ReadStatusReg(uint8_t StatusAddr) {
  uint8_t status;
	
	if(IS_CC2500_STATUSREG(StatusAddr)) { // do something cooler to check
    StatusAddr |= BURSTSTATUS_CMD;
    CC2500_Read(&status, StatusAddr, 1);
		return status;
  }
	return 0;
}

/**
  * @brief  Send strobe to chipset
	* @param  strobe
	* @param  buf: Which buffer (TX or RX) to use the strobe on
  * @retval None
  */
uint8_t CC2500_Strobe(CommandStrobe strobe, FIFOBuffer buf) 
{
    uint8_t status;
    
    if (buf == RX) strobe |= READWRITE_CMD;
		GPIO_ResetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
		
		while(GPIO_ReadInputDataBit(CC2500_SPI_MISO_GPIO_PORT, CC2500_SPI_MISO_PIN) == Bit_SET);
    status = CC2500_SendByte(strobe);
    
		GPIO_SetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
    
		return status;
}

/**
  * @brief  Send strobe to chipset
	* @param  strobe
	* @param  buf: Which buffer (TX or RX) to use the strobe on
  * @retval None
  */
void CC2500_ChipsetConfig()
{
	// See cc2500+datasheet.pdf for what these regs mean.
	// Can probably do these in burst mode.
	//uint8_t buf = SMARTRF_SETTING_GDO0
	//CC2500_Write(&buf, CC2500_CFGREG_IOCFG0_ADDR, 1);
	
	uint8_t buf = SMARTRF_SETTING_FSCTRL1;
	CC2500_Write(&buf, CC2500_CFGREG_FSCTRL1_ADDR, 1);
	buf = SMARTRF_SETTING_FSCTRL0;
	CC2500_Write(&buf, CC2500_CFGREG_FSCTRL0_ADDR, 1);
	
	buf = SMARTRF_SETTING_FREQ2;
	CC2500_Write(&buf, CC2500_CFGREG_FREQ2_ADDR, 1);
	buf = SMARTRF_SETTING_FREQ1;
	CC2500_Write(&buf, CC2500_CFGREG_FREQ1_ADDR, 1);
	buf = SMARTRF_SETTING_FREQ0;
	CC2500_Write(&buf, CC2500_CFGREG_FREQ0_ADDR, 1);
	
	buf = SMARTRF_SETTING_MDMCFG4;
	CC2500_Write(&buf, CC2500_CFGREG_MDMCFG4_ADDR, 1);
	buf = SMARTRF_SETTING_MDMCFG3;
	CC2500_Write(&buf, CC2500_CFGREG_MDMCFG3_ADDR, 1);
	buf = SMARTRF_SETTING_MDMCFG2;
	CC2500_Write(&buf, CC2500_CFGREG_MDMCFG2_ADDR, 1);
	buf = 0x42; //SMARTRF_SETTING_MDMCFG1; //causes error?
	CC2500_Write(&buf, CC2500_CFGREG_MDMCFG1_ADDR, 1);
	buf = SMARTRF_SETTING_MDMCFG0;
	CC2500_Write(&buf, CC2500_CFGREG_MDMCFG0_ADDR, 1);
	
	buf = SMARTRF_SETTING_CHANNR;
	CC2500_Write(&buf, CC2500_CFGREG_CHANNR_ADDR, 1);
	buf = SMARTRF_SETTING_DEVIATN;
	CC2500_Write(&buf, CC2500_CFGREG_DEVIATN_ADDR, 1);
	buf = SMARTRF_SETTING_FREND1;
	CC2500_Write(&buf, CC2500_CFGREG_FREND1_ADDR, 1);
	buf = SMARTRF_SETTING_FREND0;
	CC2500_Write(&buf, CC2500_CFGREG_FREND0_ADDR, 1);
	
	buf = SMARTRF_SETTING_MCSM0;
	CC2500_Write(&buf, CC2500_CFGREG_MCSM0_ADDR, 1);
	buf = SMARTRF_SETTING_FOCCFG;
	CC2500_Write(&buf, CC2500_CFGREG_FOCCFG_ADDR, 1);
	buf = SMARTRF_SETTING_BSCFG;
	CC2500_Write(&buf, CC2500_CFGREG_BSCFG_ADDR, 1);
	
	buf = SMARTRF_SETTING_AGCCTRL2;
	CC2500_Write(&buf, CC2500_CFGREG_AGCCTRL2_ADDR, 1);
	buf = SMARTRF_SETTING_AGCCTRL1;
	CC2500_Write(&buf, CC2500_CFGREG_AGCCTRL1_ADDR, 1);
	buf = SMARTRF_SETTING_AGCCTRL0;
	CC2500_Write(&buf, CC2500_CFGREG_AGCCTRL0_ADDR, 1);
	
	buf = SMARTRF_SETTING_FSCAL3;
	CC2500_Write(&buf, CC2500_CFGREG_FSCAL3_ADDR, 1);
	buf = SMARTRF_SETTING_FSCAL2;
	CC2500_Write(&buf, CC2500_CFGREG_FSCAL2_ADDR, 1);
	buf = SMARTRF_SETTING_FSCAL1;
	CC2500_Write(&buf, CC2500_CFGREG_FSCAL1_ADDR, 1);
	buf = SMARTRF_SETTING_FSCAL0;
	CC2500_Write(&buf, CC2500_CFGREG_FSCAL0_ADDR, 1);
	buf = SMARTRF_SETTING_FSTEST;
	CC2500_Write(&buf, CC2500_CFGREG_FSTEST_ADDR, 1);
	
	buf = SMARTRF_SETTING_TEST2;
	CC2500_Write(&buf, CC2500_CFGREG_TEST2_ADDR, 1);
	buf = SMARTRF_SETTING_TEST1;
	CC2500_Write(&buf, CC2500_CFGREG_TEST1_ADDR, 1);
	buf = SMARTRF_SETTING_TEST0;
	CC2500_Write(&buf, CC2500_CFGREG_TEST0_ADDR, 1);
	
	buf = SMARTRF_SETTING_FIFOTHR;
	CC2500_Write(&buf, CC2500_CFGREG_FIFOTHR_ADDR, 1);
	buf = SMARTRF_SETTING_IOCFG2;
	CC2500_Write(&buf, CC2500_CFGREG_IOCFG2_ADDR, 1);
	buf = SMARTRF_SETTING_IOCFG0;
	CC2500_Write(&buf, CC2500_CFGREG_IOCFG0_ADDR, 1);
	
	buf = SMARTRF_SETTING_PKTCTRL1;
	CC2500_Write(&buf, CC2500_CFGREG_PKTCTRL1_ADDR, 1);
	buf = SMARTRF_SETTING_PKTCTRL0;
	CC2500_Write(&buf, CC2500_CFGREG_PKTCTRL0_ADDR, 1);
	buf = SMARTRF_SETTING_PKTLEN; // 1 byte
	CC2500_Write(&buf, CC2500_CFGREG_PKTLEN_ADDR, 1);
		
	buf = SMARTRF_SETTING_ADDR; // 1 byte
	CC2500_Write(&buf, CC2500_CFGREG_ADDR_ADDR, 1);
		
	//buf = SMARTRF_SETTING_ADDR;
	//CC2500_Write(&buf, CC2500_CFGREG_PKTLEN_ADDR, 1);
  CC2500_Strobe(CC2500_CMDSTROBE_SFRX, TX);
  CC2500_Strobe(CC2500_CMDSTROBE_SFTX, TX);
  CC2500_Strobe(CC2500_CMDSTROBE_SIDLE, TX);
}

/**
  * @brief  Writes one byte to the CC2500
  * @param  pBuffer       : pointer to the buffer  containing the data to be written to the CC2500
  * @param  WriteAddr     : CC2500's internal address to write to
  * @param  NumByteToWrite: Number of bytes to write
  * @retval None
  */
void CC2500_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
  
  /* Burst bit = 1 if write burst */
  if(NumByteToWrite > 0x01)
    WriteAddr |= BURSTSTATUS_CMD;
  
  /* set NSS low */
  GPIO_ResetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
  
  /* send the write address */
  CC2500_SendByte(WriteAddr);
  
  /* write data from buffer */
  while(NumByteToWrite > 0x00) {
    CC2500_SendByte(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }
  
  /* set NSS high */ 
  GPIO_SetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
}


/**
  * @brief  Reads a block of data from the CC2500 registers
  * @param  pBuffer       : pointer to the buffer that receives the data read from the CC2500
  * @param  ReadAddr      : CC2500's internal address to read from
  * @param  NumByteToRead : number of bytes to read from the CC2500
  * @retval None
  */
void CC2500_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead) {
  
  /* set MSB = 1 to indicate read, set bit_6 = 1 if read burst */
  if(NumByteToRead > 0x01)
    ReadAddr |= (READWRITE_CMD | BURSTSTATUS_CMD);
  else 
    ReadAddr |= READWRITE_CMD;
  
  /* set NSS low */
   GPIO_ResetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
  
  /* send the read address */
  CC2500_SendByte(ReadAddr);
  
  /* store the data in the buffer */
  while(NumByteToRead > 0x00) {
    /* send dummy byte to maintain SCK */
    *pBuffer = CC2500_SendByte(DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }
  
  /* set NSS high */ 
  GPIO_SetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
}

/**
  * @brief  Sends a Byte through the SPI interface and return the Byte received 
  *         from the SPI bus.
  * @param  byte : Byte to send.
  * @retval The received byte value
  */
uint8_t CC2500_SendByte(uint8_t byte) {
  
  /* wait till Tx(SPI_DR) register empty flag is set  */
  cc2500_timeout  = CC2500_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(CC2500_SPI, SPI_I2S_FLAG_TXE) == RESET)
    if(cc2500_timeout-- == 0) 
      break; // TODO: Some default timeout handling, eg return 0x00 || return timeout handler;
  
  /* write the data into Tx(SPI_DR) register */
  SPI_I2S_SendData(CC2500_SPI, byte);
  
  /* wait till Rx(SPI_DR) register NOT empty flag is set  */
  cc2500_timeout  = CC2500_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(CC2500_SPI, SPI_I2S_FLAG_RXNE) == RESET) 
    if(cc2500_timeout-- == 0) 
      break; // TODO: Some default timeout handling, eg return 0x00 || return timeout handler;
  
  /* return the contents of the Rx(SPI_DR) register */
  return (uint8_t)SPI_I2S_ReceiveData(CC2500_SPI);
}


/**
  * @brief  Initializes the SPI interface used to drive the CC2500 chip
  * @param  None
  * @retval None
  */
void CC2500_LowLevelInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  /* enable the SPI periph clock */
  RCC_APB1PeriphClockCmd(CC2500_SPI_CLK, ENABLE);

  /* enable NSS, SCK, MOSI and MISO GPIO clocks */
  RCC_AHB1PeriphClockCmd(CC2500_SPI_SCK_GPIO_CLK | CC2500_SPI_MISO_GPIO_CLK | CC2500_SPI_MOSI_GPIO_CLK | CC2500_SPI_NSS_GPIO_CLK | CC2500_SPI_INT_GPIO_CLK, ENABLE);

  /* configure the GPIO pins for AF mode */
 // GPIO_PinAFConfig(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_SOURCE, CC2500_SPI_NSS_AF);
  GPIO_PinAFConfig(CC2500_SPI_SCK_GPIO_PORT, CC2500_SPI_SCK_SOURCE, CC2500_SPI_SCK_AF);
  GPIO_PinAFConfig(CC2500_SPI_MISO_GPIO_PORT, CC2500_SPI_MISO_SOURCE, CC2500_SPI_MISO_AF);
  GPIO_PinAFConfig(CC2500_SPI_MOSI_GPIO_PORT, CC2500_SPI_MOSI_SOURCE, CC2500_SPI_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* SPI SCK pin initialization */
  GPIO_InitStructure.GPIO_Pin = CC2500_SPI_SCK_PIN;
  GPIO_Init(CC2500_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin initialization */
  GPIO_InitStructure.GPIO_Pin =  CC2500_SPI_MOSI_PIN;
  GPIO_Init(CC2500_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* SPI MISO pin initialization */
  GPIO_InitStructure.GPIO_Pin = CC2500_SPI_MISO_PIN;
  GPIO_Init(CC2500_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* SPI NSS pin initialization */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = CC2500_SPI_NSS_PIN;
  GPIO_Init(CC2500_SPI_NSS_GPIO_PORT, &GPIO_InitStructure);
  
  /* SPI INT pin initialization */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = CC2500_SPI_INT_PIN;
  GPIO_Init(CC2500_SPI_INT_GPIO_PORT, &GPIO_InitStructure);
  
  /* SPI configuration */
  SPI_I2S_DeInit(CC2500_SPI);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(CC2500_SPI, &SPI_InitStructure);
    
  /* enable NSS software control */
  //SPI_SSOutputCmd(CC2500_SPI, ENABLE);

  /* Enable SPI2  */
  SPI_Cmd(CC2500_SPI, ENABLE);
  
  /* deselect : NSS high */
  //SPI_NSSInternalSoftwareConfig(CC2500_SPI, SET);
  GPIO_SetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN);
	
	/* Configure interrupt for GDO packet interrupts*/
	
	EXTI_InitTypeDef   EXTI_InitStructure;	
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable GPIOA clock */
  /*RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  */
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PA1 pin as input floating */
  /*GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  */

  /* Connect EXTI Line1 to PA1 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource11);

  /* Configure EXTI Line1 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line1 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
}


