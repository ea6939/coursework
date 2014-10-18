
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _wireless_driver
#define _wireless_driver
#endif

#define WIRELESS_SPI                       SPI2
#define WIRELESS_SPI_CLK                   RCC_APB1Periph_SPI2 

#define WIRELESS_SPI_SCK_PIN               GPIO_Pin_13                  /* PB.13 */
#define WIRELESS_SPI_SCK_GPIO_PORT         GPIOB                       /* GPIOB*/
#define WIRELESS_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define WIRELESS_SPI_SCK_SOURCE            GPIO_PinSource13
#define WIRELESS_SPI_SCK_AF                GPIO_AF_SPI2

#define WIRELESS_SPI_MISO_PIN              GPIO_Pin_14                  /* PA.14 */
#define WIRELESS_SPI_MISO_GPIO_PORT        GPIOB                       /* GPIOB */
#define WIRELESS_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define WIRELESS_SPI_MISO_SOURCE           GPIO_PinSource14
#define WIRELESS_SPI_MISO_AF               GPIO_AF_SPI2

#define WIRELESS_SPI_MOSI_PIN              GPIO_Pin_15                  /* PA.15 */
#define WIRELESS_SPI_MOSI_GPIO_PORT        GPIOB                       /* GPIOB */
#define WIRELESS_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define WIRELESS_SPI_MOSI_SOURCE           GPIO_PinSource15
#define WIRELESS_SPI_MOSI_AF               GPIO_AF_SPI2

#define WIRELESS_SPI_CS_PIN                GPIO_Pin_3                  /* PE.03 */
#define WIRELESS_SPI_CS_GPIO_PORT          GPIOE                       /* GPIOE */
#define WIRELESS_SPI_CS_GPIO_CLK           RCC_AHB1Periph_GPIOE

/*
Chip status byte definition masks
AND the chip status register with these masks to determine the status
Taken from page 7 of the CC2500 SPI design note
*/
#define CHIP_RDYN_MASK                           0x80  //Stays high until power and crystal have stabilized.  Should always be low
#define RX_MASK                                  0x10   //receive mode
#define TX_MASK                                  0x20  //transit mode
#define FSTXON_MASK                              0x30  //fast TX ready
#define CALIBRATE_MASK                           0x40   //Frequency synthesizer calibration is ready
#define SETTLING_MASK                            0x50  //PLL is settling
#define RXFIFO_OVERFLOW_MASK                     0x60  //RX FIFO has overflowed.  Read out any useful data, then flush the FIFO with SFRX
#define TXFIFO_OVERFLOW_MASK                     0x70   //TX FIFO has underflowed.  Acknowledge with SFTX

#define FIFO_BYTES_AVAILALBE_MASK           0x0f  //The number of bytes available 

/*
Command strobe register addresses
Accessing these registers will initiate the internal change of an internal state or mode
*/

#define SRES                          0x30  //Reset chip.
#define SFSTXON                                  0x31   //Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA):
                                                            //Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
#define SXOFF                                  0x32 //Turn off crystal oscillator.
#define SCAL                              0x33  //Calibrate frequency synthesizer and turn it off. SCAL can be strobed from IDLE mode without
                                                 //setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
#define SRX                           0x34   //Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1.
#define STX                            0x35  //In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1.
                                             //If in RX state and CCA is enabled: Only go to TX if channel is clear.
#define SIDLE                     0x36  //Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable.
#define SFRX                     0x3A   //Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states.
#define SFTX                     0x3B   //TX FIFO has underflowed.  Acknowledge with SFTX
#define SNOP                     0x3D   //No operation. May be used to get access to the chip status byte.

/**
Status register addresses

*/
#define VERSION                 0x31

#define RX_FIFO                 0xBF

#define READ_SINGLE             0x80

// #define WIRELESS_SPI_INT1_PIN              GPIO_Pin_0                  /* PE.00 */
// #define WIRELESS_SPI_INT1_GPIO_PORT        GPIOE                       /* GPIOE */
// #define WIRELESS_SPI_INT1_GPIO_CLK         RCC_AHB1Periph_GPIOE
// #define WIRELESS_SPI_INT1_EXTI_LINE        EXTI_Line0
// #define WIRELESS_SPI_INT1_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
// #define WIRELESS_SPI_INT1_EXTI_PIN_SOURCE  EXTI_PinSource0
// #define WIRELESS_SPI_INT1_EXTI_IRQn        EXTI0_IRQn 

// #define WIRELESS_SPI_INT2_PIN              GPIO_Pin_1                  /* PE.01 */
// #define WIRELESS_SPI_INT2_GPIO_PORT        GPIOE                       /* GPIOE */
// #define WIRELESS_SPI_INT2_GPIO_CLK         RCC_AHB1Periph_GPIOE
// #define WIRELESS_SPI_INT2_EXTI_LINE        EXTI_Line1
// #define WIRELESS_SPI_INT2_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
// #define WIRELESS_SPI_INT2_EXTI_PIN_SOURCE  EXTI_PinSource1
// #define WIRELESS_SPI_INT2_EXTI_IRQn        EXTI1_IRQn 

void g2_wireless_gpio_spi_setup(void);
void g2_wireless_send_data(uint8_t data);
void g2_wireless_reset(void);
void g2_send_command_strobe(uint8_t command);
void g2_read_register(uint8_t address, uint8_t* result);


