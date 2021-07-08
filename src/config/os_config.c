
#include <cortexm/mpu.h>
#include <cortexm/task.h>
#include <device/ffifo.h>
#include <fcntl.h>
#include <sos/debug.h>
#include <sos/led.h>
#include <sos/link/types.h>
#include <sos/sos.h>
#include <string.h>

#include "config.h"
#include "os_config.h"
#include "stm32/stm32h735g-dk.h"

void os_event_handler(int event, void *args) {
  switch (event) {
  case SOS_EVENT_ROOT_RESET:

    break;

  case SOS_EVENT_ROOT_FATAL:
    // start the bootloader on a fatal event
    // mcu_core_invokebootloader(0, 0);
    sos_debug_printf("Fatal\n");
    if (args != 0) {
      sos_debug_log_error(SOS_DEBUG_SYS, "Fatal Error %s", (const char *)args);
    } else {
      sos_debug_log_error(SOS_DEBUG_SYS, "Fatal Error unknown");
    }
    while (1) {
      ;
    }
    break;

  case SOS_EVENT_ROOT_MPU_INITIALIZED:
    SOS_DEBUG_LINE_TRACE();
    stm32h735g_dk_init_ospi_ram();
    SOS_DEBUG_LINE_TRACE();

#if 0
    // Allow full access to video memory
    mpu_enable_region(TASK_SYSTEM_SECRET_KEY_REGION + 1, (void *)CONFIG_VIDEO_MEMORY_ADDRESS,
                      CONFIG_VIDEO_MEMORY_SIZE, MPU_ACCESS_PRW_URW,
                      MPU_MEMORY_EXTERNAL_SRAM,
                      0 // executable
    );
#endif
    //background access to app region -- allows caching for general access by appfs
    mpu_enable_region(TASK_APPLICATION_DATA_USER_REGION, (void *)CONFIG_APP_MEMORY_ADDRESS,
                      CONFIG_APP_MEMORY_SIZE, MPU_ACCESS_PRW_UR,
                      MPU_MEMORY_EXTERNAL_SRAM,
                      0 // executable
                      );

    break;

  case SOS_EVENT_ROOT_INVALID_PIN_ASSIGNMENT: {
    const mcu_pin_t *pin = args;
    sos_debug_log_error(SOS_DEBUG_SYS, "bad pin assignment %d.%d", pin->port,
                        pin->pin);
  } break;

  case SOS_EVENT_START_LINK:

#if INCLUDE_ETHERNET
    // start LWIP
    sos_debug_log_info(SOS_DEBUG_USER0, "Start LWIP");
    usleep(500 * 1000);
    lwip_api.startup(&lwip_api);
#endif

    sos_debug_log_info(SOS_DEBUG_USER0, "Start LED %d");
    sos_led_startup();
    sos_debug_log_info(SOS_DEBUG_USER0, "Start Link");
    break;
  }
}
