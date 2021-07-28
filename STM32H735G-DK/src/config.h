
#ifndef CONFIG_H_
#define CONFIG_H_

#include <sos/arch.h>
#include <sos/debug.h>

#include "config/os_config.h"
#include "sl_config.h"

#define CONFIG_SYSTEM_MEMORY_SIZE (256 * 1024)
#define CONFIG_SYSTEM_CLOCK 292000000

#define CONFIG_STDIO_BUFFER_SIZE 528

//RGB565 double buffer for video memory
#define CONFIG_VIDEO_MEMORY_SIZE (1024*1024UL)
#define CONFIG_VIDEO_MEMORY_ADDRESS (0x70000000)

#define CONFIG_APP_MEMORY_ADDRESS (CONFIG_VIDEO_MEMORY_ADDRESS + CONFIG_VIDEO_MEMORY_SIZE)
#define CONFIG_APP_MEMORY_SIZE (2048*1024UL)

#define CONFIG_LCD_INSTANCE 0

//Removing SOS_DEBUG_LINK causes the USB link protocol to fail

#define CONFIG_DEBUG_FLAGS                                                     \
  (SOS_DEBUG_MESSAGE | SOS_DEBUG_DEVICE | SOS_DEBUG_SYS| SOS_DEBUG_SCHEDULER |     \
   SOS_DEBUG_USER0 | SOS_DEBUG_USER1 )
#define CONFIG_BOARD_FLAGS 0

#define CONFIG_CARD_PRESENT_PORT 5
#define CONFIG_CARD_PRESENT_PINMASK (1 << 5)

#endif /* CONFIG_H_ */
