
#include <sos/arch.h>
#include <stm32_config.h>

#include "config.h"

//--------------------------------------------MCU
// Configuration-------------------------------------------------

#define USB_RX_BUFFER_SIZE 1024

static char stm32_usb_rx_buffer[USB_RX_BUFFER_SIZE] MCU_SYS_MEM;

//STM32H735 has 4KB of USB RAM
//each word is 32-bits
//128words = 512 bytes
#define SOS_BOARD_RX_FIFO_WORDS 128
#define SOS_BOARD_TX0_FIFO_WORDS 32
#define SOS_BOARD_TX1_FIFO_WORDS 32
#define SOS_BOARD_TX2_FIFO_WORDS 32
#define SOS_BOARD_TX3_FIFO_WORDS 64
#define SOS_BOARD_TX4_FIFO_WORDS 0
#define SOS_BOARD_TX5_FIFO_WORDS 0

const stm32_config_t stm32_config = {
    .flash_program_millivolts = 3300,
    .usb =
        {
            .rx_buffer = stm32_usb_rx_buffer,
            .rx_buffer_size = USB_RX_BUFFER_SIZE,
            .rx_fifo_word_size =
                SOS_BOARD_RX_FIFO_WORDS, // RX fifo for all endpoints
            .tx_fifo_word_size[0] = SOS_BOARD_TX0_FIFO_WORDS, // TX endpoint 0
            .tx_fifo_word_size[1] = SOS_BOARD_TX1_FIFO_WORDS, // TX endpoint 1
            .tx_fifo_word_size[2] = SOS_BOARD_TX2_FIFO_WORDS, // TX endpoint 2
            .tx_fifo_word_size[3] = SOS_BOARD_TX3_FIFO_WORDS, // TX endpoint 3
            .tx_fifo_word_size[4] = SOS_BOARD_TX4_FIFO_WORDS, // TX endpoint 4
            .tx_fifo_word_size[5] = SOS_BOARD_TX5_FIFO_WORDS  // TX endpoint 5
        }
};
