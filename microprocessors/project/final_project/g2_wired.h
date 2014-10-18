#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"

#define WIRED_SPI                       SPI2
#define WIRED_SPI_CLK                   RCC_APB1Periph_SPI2 

#define WIRED_SPI_INT_PIN               GPIO_Pin_11                  /* PB.11 */
#define WIRED_SPI_INT_GPIO_PORT         GPIOB                        /* GPIOB*/
#define WIRED_SPI_INT_GPIO_CLK          RCC_AHB1Periph_GPIOB

#define WIRED_SPI_NSS_PIN               GPIO_Pin_12                  /* PB.12 */
#define WIRED_SPI_NSS_GPIO_PORT         GPIOB                        /* GPIOB*/
#define WIRED_SPI_NSS_GPIO_CLK          RCC_AHB1Periph_GPIOB
//#define WIRED_SPI_NSS_SOURCE            GPIO_PinSource12
//#define WIRED_SPI_NSS_AF                GPIO_AF_SPI2

#define WIRED_SPI_SCK_PIN               GPIO_Pin_13                  /* PB.13 */
#define WIRED_SPI_SCK_GPIO_PORT         GPIOB                        /* GPIOB*/
#define WIRED_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define WIRED_SPI_SCK_SOURCE            GPIO_PinSource13
#define WIRED_SPI_SCK_AF                GPIO_AF_SPI2

#define WIRED_SPI_MISO_PIN              GPIO_Pin_14                  /* PB.14 */
#define WIRED_SPI_MISO_GPIO_PORT        GPIOB                        /* GPIOB */
#define WIRED_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define WIRED_SPI_MISO_SOURCE           GPIO_PinSource14
#define WIRED_SPI_MISO_AF               GPIO_AF_SPI2

#define WIRED_SPI_MOSI_PIN              GPIO_Pin_15                  /* PB.15 */
#define WIRED_SPI_MOSI_GPIO_PORT        GPIOB                        /* GPIOB */
#define WIRED_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define WIRED_SPI_MOSI_SOURCE           GPIO_PinSource15
#define WIRED_SPI_MOSI_AF               GPIO_AF_SPI2

void g2_wired_comm_setup(void);