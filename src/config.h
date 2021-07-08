
#ifndef CONFIG_H_
#define CONFIG_H_

#include <sos/arch.h>
#include <sos/debug.h>

#include "config/os_config.h"
#include "sl_config.h"

#define CONFIG_SYSTEM_MEMORY_SIZE (64 * 1024)
#define CONFIG_STDIO_BUFFER_SIZE 512
#define CONFIG_SYSTEM_CLOCK 292000000

#define CONFIG_STDIO_BUFFER_SIZE 512


//Removing SOS_DEBUG_LINK causes the USB link protocol to fail

#define CONFIG_DEBUG_FLAGS                                                     \
  (SOS_DEBUG_MESSAGE | SOS_DEBUG_DEVICE | SOS_DEBUG_SYS | SOS_DEBUG_LINK |     \
   SOS_DEBUG_USER0 | SOS_DEBUG_USER1)
#define CONFIG_BOARD_FLAGS 0

#define CONFIG_TASK_TOTAL 16

#define CONFIG_CARD_PRESENT_PORT 5
#define CONFIG_CARD_PRESENT_PINMASK (1 << 5)

#endif /* CONFIG_H_ */
