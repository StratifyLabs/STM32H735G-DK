
#ifndef CONFIG_H_
#define CONFIG_H_

#include <sos/arch.h>
#include <sos/debug.h>

#include "config/os_config.h"
#include "sl_config.h"

#define SYSTEM_MEMORY_SIZE (64 * 1024)
#define CONFIG_STDIO_BUFFER_SIZE 512
#define CONFIG_SYSTEM_CLOCK 100000000

#define SOS_BOARD_STDIO_BUFFER_SIZE 512
#define SOS_BOARD_DEBUG_FLAGS 0
#define SOS_BOARD_FLAGS 0
#define SOS_BOARD_TASK_TOTAL 16
#define VECTOR_TABLE_ADDRESS 0x08000000

#define SOS_BOARD_USB_DP_PIN mcu_pin(0,12)
#define SOS_BOARD_USB_DM_PIN mcu_pin(0,11)

// Total number of tasks (threads) for the entire system
#define CONFIG_TASK_TOTAL 16


#endif /* CONFIG_H_ */
