
#ifndef CONFIG_H_
#define CONFIG_H_

#include <sos/arch.h>
#include <sos/debug.h>

#include "config/os_config.h"
#include "sl_config.h"

#define SYSTEM_MEMORY_SIZE (64 * 1024)
#define CONFIG_STDIO_BUFFER_SIZE 512
#define CONFIG_SYSTEM_CLOCK 292000000

#define SOS_BOARD_STDIO_BUFFER_SIZE 512
#define SOS_BOARD_DEBUG_FLAGS                                                  \
  (SOS_DEBUG_MESSAGE | SOS_DEBUG_DEVICE | SOS_DEBUG_SYS | SOS_DEBUG_USER0 |    \
   SOS_DEBUG_USER1 | SOS_DEBUG_LINK)
#define SOS_BOARD_FLAGS 0
#define SOS_BOARD_TASK_TOTAL 16
#define VECTOR_TABLE_ADDRESS 0x08000000


//USB Pins are configured at Boot
#define SOS_BOARD_USB_DP_PIN mcu_pin(0xff, 0xff)
#define SOS_BOARD_USB_DM_PIN mcu_pin(0xff, 0xff)

// Total number of tasks (threads) for the entire system
#define CONFIG_TASK_TOTAL 16

#endif /* CONFIG_H_ */
