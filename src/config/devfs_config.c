
#include <device/auth.h>
#include <device/cfifo.h>
#include <device/device_fifo.h>
#include <device/fifo.h>
#include <device/stream_ffifo.h>
#include <device/sys.h>
#include <device/uartfifo.h>
#include <device/usbfifo.h>

#include <errno.h>
#include <fcntl.h>
#include <mcu/mcu.h>
#include <mcu/periph.h>
#include <sos/debug.h>
#include <sos/fs/appfs.h>
#include <sos/fs/devfs.h>
#include <sos/fs/sffs.h>
#include <sos/fs/sysfs.h>
#include <sos/link.h>
#include <sos/sos.h>
#include <sys/lock.h>

#include <stm32/stm32_types.h>

#include "config.h"
#include "link_config.h"
#include "sl_config.h"

#if INCLUDE_ETHERNET
#include "ethernet/lwip_config.h"
#include "ethernet/netif_lan8742a.h"
#endif

//--------------------------------------------Device
// Filesystem-------------------------------------------------

/*
 * Defaults configurations
 *
 * This provides the default pin assignments and settings for peripherals. If
 * the defaults are not provided, the application must specify them.
 *
 * Defaults should be added for peripherals that are dedicated for use on the
 * board. For example, if a UART has an external connection and label on the
 * board, the BSP should provide the default configuration.
 *
 *
 *
 */

adc_state_t adc0_dma_state MCU_SYS_MEM;
const stm32_adc_dma_config_t adc0_dma_config = {
    .adc_config = {.attr =
                       {
                           .o_flags =
                               ADC_FLAG_SET_CONVERTER | ADC_FLAG_SET_CHANNELS |
                               ADC_FLAG_IS_SCAN_MODE | ADC_FLAG_IS_TRIGGER_TMR,
                           .pin_assignment =
                               {
                                   .channel[0] = {0, 3},      // PA3 ADC0-IN3
                                   .channel[1] = {2, 0},      // PC0 ADC0-IN10
                                   .channel[2] = {2, 3},      // PC3 ADC0-IN13
                                   .channel[3] = {0xff, 0xff} // Not used
                               },
                           .freq = 0,
                           // Trigger on timer3 TRGO (/dev/tim2)
                           .trigger = {2, 0},
                           .width = 12,
                           .channel_count = 3, // used with scan mode
                           // these are used for individual channel config
                           .channel = 0,      // not used for default config
                           .rank = 0,         // not used
                           .sampling_time = 0 // not used
                       }},
    .dma_config = {.dma_number = STM32_DMA2, // 2 for ADC1
                   .stream_number = 0,       // 0 for ADC1
                   .channel_number = 0,      // 0 for ADC1
                   .o_flags = STM32_DMA_FLAG_IS_CIRCULAR |
                              STM32_DMA_FLAG_IS_FIFO |
                              STM32_DMA_FLAG_IS_PERIPH_TO_MEMORY |
                              STM32_DMA_FLAG_IS_MEMORY_HALFWORD |
                              STM32_DMA_FLAG_IS_PERIPH_HALFWORD |
                              STM32_DMA_FLAG_IS_MEMORY_SINGLE,
                   .priority = STM32_DMA_PRIORITY_HIGH}};

#define ADC_PACKET_SIZE 512

char adc0_stream_ffifo_rx_buffer[2 * ADC_PACKET_SIZE];
stream_ffifo_state_t adc0_stream_ffifo_state MCU_SYS_MEM;
const stream_ffifo_config_t adc0_stream_ffifo_config = {
    .device = DEVFS_DEVICE("adc0", mcu_adc_dma, 0, &adc0_dma_config,
                           &adc0_dma_state, 0777, SYSFS_ROOT, S_IFCHR),
    .tx_loc = 0,
    .rx_loc = ADC_LOC_IS_GROUP,
    .tx = {.frame_count = 0, .frame_size = 0, .buffer = 0},
    .rx = {.frame_count = 2,
           .frame_size = ADC_PACKET_SIZE,
           .buffer = adc0_stream_ffifo_rx_buffer}};

char uart1_fifo_buffer[64];
fifo_config_t uart1_fifo_config = {.size = 64, .buffer = uart1_fifo_buffer};

uart_config_t uart1_config = {
    .attr = {.o_flags = UART_FLAG_SET_LINE_CODING_DEFAULT,
             .freq = 115200,
             .width = 8,
             .pin_assignment = {.tx = {0, 0},
                                .rx = {0, 0},
                                .rts = {0xff, 0xff},
                                .cts = {0xff, 0xff}}},
    .fifo_config = &uart1_fifo_config};

#define UART_DMA_FLAGS                                                         \
  STM32_DMA_FLAG_IS_MEMORY_SINGLE | STM32_DMA_FLAG_IS_PERIPH_SINGLE |          \
      STM32_DMA_FLAG_IS_PERIPH_BYTE | STM32_DMA_FLAG_IS_MEMORY_BYTE

uart_state_t uart1_state MCU_SYS_MEM;
stm32_uart_dma_config_t uart1_dma_config = {
    .uart_config = {.attr = {.o_flags = UART_FLAG_SET_LINE_CODING_DEFAULT,
                             .freq = 115200,
                             .width = 8,
                             .pin_assignment = {.tx = {0, 0},
                                                .rx = {0, 0},
                                                .rts = {0xff, 0xff},
                                                .cts = {0xff, 0xff}}},
                    .fifo_config = &uart1_fifo_config},
    .dma_config = {
        .rx = {.dma_number = 0,
               .stream_number = 0,
               .channel_number = 0,
               .priority = STM32_DMA_PRIORITY_LOW,
               .o_flags = STM32_DMA_FLAG_IS_PERIPH_TO_MEMORY | UART_DMA_FLAGS |
                          STM32_DMA_FLAG_IS_CIRCULAR},
        .tx = {.dma_number = 0,
               .stream_number = 0,
               .channel_number = 0,
               .priority = STM32_DMA_PRIORITY_LOW,
               .o_flags = STM32_DMA_FLAG_IS_MEMORY_TO_PERIPH | UART_DMA_FLAGS |
                          STM32_DMA_FLAG_IS_NORMAL}}};

// I2C1
i2c_state_t i2c0_state MCU_SYS_MEM;
const i2c_config_t i2c0_config = {
    .port = 0,
    .attr = {.o_flags = I2C_FLAG_SET_MASTER,
             .freq = 100000,
             .pin_assignment = {.scl = {0, 0}, .sda = {0, 0}}}};

// I2C2
i2c_state_t i2c1_state MCU_SYS_MEM;
const i2c_config_t i2c1_config = {
    .port = 0,
    .attr = {.o_flags = I2C_FLAG_SET_MASTER,
             .freq = 100000,
             .pin_assignment = {.scl = {0, 0}, .sda = {0, 0}}}};

#define SPI_DMA_FLAGS                                                          \
  STM32_DMA_FLAG_IS_NORMAL | STM32_DMA_FLAG_IS_MEMORY_SINGLE |                 \
      STM32_DMA_FLAG_IS_PERIPH_SINGLE | STM32_DMA_FLAG_IS_PERIPH_BYTE |        \
      STM32_DMA_FLAG_IS_MEMORY_BYTE

spi_state_t spi0_state MCU_SYS_MEM;
const stm32_spi_dma_config_t spi0_dma_config = {
    .spi_config = {.port = 0,
                   .attr = {.o_flags =
                                SPI_FLAG_SET_MASTER | SPI_FLAG_IS_FORMAT_SPI |
                                SPI_FLAG_IS_MODE0 | SPI_FLAG_SET_FULL_DUPLEX,
                            .width = 8,
                            .freq = 1000000UL,
                            .pin_assignment = {.miso = {0, 0},
                                               .mosi = {0, 0},
                                               .sck = {0, 0},
                                               .cs = {0, 0}}}},
    .dma_config = {.rx =
                       {
                           .dma_number = 0,
                           .stream_number = 0,
                           .channel_number = 0,
                           .priority = STM32_DMA_PRIORITY_LOW,
                           .o_flags = STM32_DMA_FLAG_IS_PERIPH_TO_MEMORY |
                                      SPI_DMA_FLAGS,
                       },
                   .tx = {.dma_number = 0,
                          .stream_number = 0,
                          .channel_number = 0,
                          .priority = STM32_DMA_PRIORITY_LOW,
                          .o_flags = STM32_DMA_FLAG_IS_MEMORY_TO_PERIPH |
                                     SPI_DMA_FLAGS}}};

spi_state_t spi2_state MCU_SYS_MEM;
const stm32_spi_dma_config_t spi2_dma_config = {
    .spi_config = {.port = 2,
                   .attr = {.o_flags =
                                SPI_FLAG_SET_MASTER | SPI_FLAG_IS_FORMAT_SPI |
                                SPI_FLAG_IS_MODE0 | SPI_FLAG_SET_FULL_DUPLEX,
                            .width = 8,
                            .freq = 1000000UL,
                            .pin_assignment = {.miso = {0, 0},
                                               .mosi = {0, 0},
                                               .sck = {0, 0},
                                               .cs = {0, 0}}}},
    .dma_config = {.rx =
                       {
                           .dma_number = 0,
                           .stream_number = 0,
                           .channel_number = 0,
                           .priority = STM32_DMA_PRIORITY_LOW,
                           .o_flags = STM32_DMA_FLAG_IS_PERIPH_TO_MEMORY |
                                      SPI_DMA_FLAGS,
                       },
                   .tx = {.dma_number = 0,
                          .stream_number = 0,
                          .channel_number = 0,
                          .priority = STM32_DMA_PRIORITY_LOW,
                          .o_flags = STM32_DMA_FLAG_IS_MEMORY_TO_PERIPH |
                                     SPI_DMA_FLAGS}}};

#if INCLUDE_ETHERNET

// these use DMA and can't be tightly coupled
u8 eth_tx_buffer[STM32_ETH_DMA_BUFFER_SIZE];
u8 eth_rx_buffer[STM32_ETH_DMA_BUFFER_SIZE];

netif_lan8742a_state_t netif_lan8742a_state MCU_SYS_MEM;
const stm32_eth_dma_config_t
    eth0_config =
        {
            .eth_config = {.port = 0,
                           .attr =
                               {
                                   .o_flags =
                                       ETH_FLAG_SET_INTERFACE | ETH_FLAG_START |
                                       ETH_FLAG_IS_RMII |
                                       ETH_FLAG_IS_FULLDUPLEX |
                                       ETH_FLAG_IS_AUTONEGOTIATION_ENABLED,
                                   .pin_assignment =
                                       {
                                           .rmii = {.clk = {0, 1},    // PA1
                                                    .txd0 = {6, 13},  // PG13
                                                    .txd1 = {1, 13},  // PB13
                                                    .tx_en = {6, 11}, // PG11
                                                    .rxd0 = {2, 4},   // PC4
                                                    .rxd1 = {2, 5},   // PC5
                                                    .crs_dv = {0, 7}, // PA7
                                                    .rx_er = {0xff, 0xff}, //??
                                                    .unused[0] = {0xff, 0xff},
                                                    .unused[1] = {0xff, 0xff},
                                                    .unused[2] = {0xff, 0xff},
                                                    .unused[3] = {0xff, 0xff},
                                                    .unused[4] = {0xff, 0xff},
                                                    .unused[5] = {0xff, 0xff},
                                                    .unused[6] = {0xff, 0xff},
                                                    .unused[7] = {0xff, 0xff}},
                                           .mdio = {0, 2}, // PA2
                                           .mdc = {2, 1}   // PC1
                                       },
                                   .mac_address[0] = 0x00,
                                   .mac_address[1] = 0x80,
                                   .mac_address[2] = 0xe1,
                                   .mac_address[3] = 0x00,
                                   .mac_address[4] = 0x00,
                                   .mac_address[5] = 0x08,
                                   .mac_address[6] = 0x00, // unused
                                   .mac_address[7] = 0x00, // unused
                                   .mac_address[8] = 0x00, // unused
                                   .mac_address[9] = 0x00, // unused
                                   .phy_address = 0 // address of PHY CHIP
                               }},
            .tx_buffer = eth_tx_buffer,
            .rx_buffer = eth_rx_buffer};

#endif

#if !defined SOS_BOARD_USB_PORT
#define SOS_BOARD_USB_PORT 0
#endif

#define USB_DEVICE_FIFO_BUFFER_SIZE 64
char usb_device_fifo_buffer[USB_DEVICE_FIFO_BUFFER_SIZE] MCU_SYS_MEM;
u8 usb_device_fifo_read_buffer[USB_DEVICE_FIFO_BUFFER_SIZE] MCU_SYS_MEM;
device_fifo_state_t usb_device_fifo_state MCU_SYS_MEM;
usb_state_t usb_device_state MCU_SYS_MEM;
const usb_config_t usb_device_config = {
    .port = SOS_BOARD_USB_PORT, .attr = {
                                    .pin_assignment = {
                                        .dm = {0xff, 0xff},
                                        .dp = {0xff, 0xff},
                                        .id = {0xff, 0xff},
                                        .vbus = {0xff, 0xff},
                                    }
                                }};
const device_fifo_config_t usb_device_fifo_config = {
    .device = DEVFS_DEVICE("usb", mcu_usb, 0, &usb_device_config,
                           &usb_device_state, 0666, SYSFS_ROOT, S_IFCHR),
    .read_location = SOS_LINK_TRANSPORT_USB_BULK_ENDPOINT,
    .write_location = SOS_LINK_TRANSPORT_USB_BULK_ENDPOINT | 0x80,
    .fifo =
        {
            .buffer = usb_device_fifo_buffer,
            .size = USB_DEVICE_FIFO_BUFFER_SIZE,
        },
    .read_buffer = usb_device_fifo_read_buffer,
    .read_buffer_size = USB_DEVICE_FIFO_BUFFER_SIZE,
};

// Coming Soon
// SD Card as DMA
// I2S2
// I2S3
// SAI1A/B

FIFO_DECLARE_CONFIG_STATE(stdio_in, CONFIG_STDIO_BUFFER_SIZE);
FIFO_DECLARE_CONFIG_STATE(stdio_out, CONFIG_STDIO_BUFFER_SIZE);

pio_state_t pio_state[8] MCU_SYS_MEM;
const pio_config_t pio_config[8] = {{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}};

tmr_state_t tmr0_state MCU_SYS_MEM;
const tmr_config_t tmr0_config = {
    .port = 0,
    .attr = {.pin_assignment = {.channel[0] = {0xff, 0xff},
                                .channel[1] = {0xff, 0xff},
                                .channel[2] = {0xff, 0xff},
                                .channel[3] = {0xff, 0xff}}}};

tmr_state_t tmr2_state MCU_SYS_MEM;
const tmr_config_t tmr2_config = {
    .port = 2,
    .attr = {.pin_assignment = {.channel[0] = {0xff, 0xff},
                                .channel[1] = {0xff, 0xff},
                                .channel[2] = {0xff, 0xff},
                                .channel[3] = {0xff, 0xff}}}};

tmr_state_t tmr3_state MCU_SYS_MEM;
const tmr_config_t tmr3_config = {
    .port = 3,
    .attr = {.pin_assignment = {.channel[0] = {0xff, 0xff},
                                .channel[1] = {0xff, 0xff},
                                .channel[2] = {0xff, 0xff},
                                .channel[3] = {0xff, 0xff}}}};

/* This is the list of devices that will show up in the /dev folder.
 */
const devfs_device_t devfs_list[] = {
    // System devices
#if 0
    DEVFS_DEVICE("trace", ffifo, 0, &board_trace_config, &board_trace_state,
                 0666, SYSFS_ROOT, S_IFCHR),
#endif
    DEVFS_DEVICE("stdio-out", fifo, 0, &stdio_out_config, &stdio_out_state,
                 0666, SYSFS_ROOT, S_IFCHR),
    DEVFS_DEVICE("stdio-in", fifo, 0, &stdio_in_config, &stdio_in_state, 0666,
                 SYSFS_ROOT, S_IFCHR),
    DEVFS_DEVICE("link-phy-usb", device_fifo, SOS_BOARD_USB_PORT,
                 &usb_device_fifo_config, &usb_device_fifo_state, 0666,
                 SYSFS_ROOT, S_IFCHR),
    DEVFS_DEVICE("sys", sys, 0, 0, 0, 0666, SYSFS_ROOT, S_IFCHR),
    DEVFS_DEVICE("auth", auth, 0, 0, 0, 0666, SYSFS_ROOT, S_IFCHR),
    // DEVFS_DEVICE("rtc", mcu_rtc, 0, 0, 0, 0666, SYSFS_ROOT, S_IFCHR),

    // MCU peripherals
    DEVFS_DEVICE("adc0", stream_ffifo, 0, &adc0_stream_ffifo_config,
                 &adc0_stream_ffifo_state, 0666, SYSFS_ROOT, S_IFCHR),

    DEVFS_DEVICE("core", mcu_core, 0, 0, 0, 0666, SYSFS_ROOT, S_IFCHR),

#if INCLUDE_ETHERNET
    DEVFS_DEVICE("eth0", netif_lan8742a, 0, &eth0_config, &netif_lan8742a_state,
                 0666, SYSFS_ROOT, S_IFCHR),
#endif

    DEVFS_DEVICE("i2c0", mcu_i2c, 0, &i2c0_config, &i2c0_state, 0666,
                 SYSFS_ROOT, S_IFCHR),
    DEVFS_DEVICE("i2c1", mcu_i2c, 1, &i2c1_config, &i2c1_state, 0666,
                 SYSFS_ROOT, S_IFCHR),

    DEVFS_DEVICE("pio0", mcu_pio, 0, pio_config + 0, pio_state + 0, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOA
    DEVFS_DEVICE("pio1", mcu_pio, 1, pio_config + 1, pio_state + 1, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOB
    DEVFS_DEVICE("pio2", mcu_pio, 2, pio_config + 2, pio_state + 2, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOC
    DEVFS_DEVICE("pio3", mcu_pio, 3, pio_config + 3, pio_state + 3, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOD
    DEVFS_DEVICE("pio4", mcu_pio, 4, pio_config + 4, pio_state + 4, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOE
    DEVFS_DEVICE("pio5", mcu_pio, 5, pio_config + 5, pio_state + 5, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOF
    DEVFS_DEVICE("pio6", mcu_pio, 6, pio_config + 6, pio_state + 6, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOG
    DEVFS_DEVICE("pio7", mcu_pio, 7, pio_config + 7, pio_state + 7, 0666,
                 SYSFS_ROOT,
                 S_IFCHR), // GPIOH

    DEVFS_DEVICE("spi0", mcu_spi, 0, &spi0_dma_config, &spi0_state, 0666,
                 SYSFS_ROOT, S_IFCHR),
    DEVFS_DEVICE("spi2", mcu_spi, 0, &spi2_dma_config, &spi2_state, 0666,
                 SYSFS_ROOT, S_IFCHR),

    // TIM1
    DEVFS_DEVICE("tmr0", mcu_tmr, 0, &tmr0_config, &tmr0_state, 0666,
                 SYSFS_ROOT, S_IFCHR),
    // TIM3
    DEVFS_DEVICE("tmr2", mcu_tmr, 2, &tmr2_config, &tmr2_state, 0666,
                 SYSFS_ROOT, S_IFCHR),
    // TIM4
    DEVFS_DEVICE("tmr3", mcu_tmr, 3, &tmr3_config, &tmr3_state, 0666,
                 SYSFS_ROOT, S_IFCHR),

    DEVFS_TERMINATOR};
