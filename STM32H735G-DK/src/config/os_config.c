
#include <cortexm/mpu.h>
#include <cortexm/task.h>
#include <device/ffifo.h>
#include <fcntl.h>
#include <sos/debug.h>
#include <sos/led.h>
#include <sos/link/types.h>
#include <sos/sos.h>
#include <string.h>

#include <device/device_fifo.h>

#include "config.h"
#include "lvgl_config.h"
#include "os_config.h"
#include "stm32/stm32h735g-dk.h"

#include "stm32/stm32h735g_discovery_lcd.h"

void svcall_flush_video_memory(void *args) {
  CORTEXM_SVCALL_ENTER();
  MCU_UNUSED_ARGUMENT(args);
  SOS_DEBUG_LINE_TRACE();

  BSP_LCD_WritePixel(0, 10, 10, 0xffff);

  sos_config.cache.clean_data_block((void *)CONFIG_VIDEO_MEMORY_ADDRESS,
                                    CONFIG_VIDEO_MEMORY_SIZE);
}

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
    // Allow full access to video memory
    SOS_DEBUG_LINE_TRACE();
    mpu_enable_region(TASK_APPLICATION_DATA_USER_REGION - 1,
                      (void *)CONFIG_VIDEO_MEMORY_ADDRESS,
                      CONFIG_VIDEO_MEMORY_SIZE, MPU_ACCESS_PRW_URW,
                      MPU_MEMORY_EXTERNAL_SRAM,
                      0 // executable
    );

    SOS_DEBUG_LINE_TRACE();
    // background access to app region -- allows caching for general access by
    // appfs
    mpu_enable_region(TASK_APPLICATION_DATA_USER_REGION,
                      (void *)CONFIG_APP_MEMORY_ADDRESS, CONFIG_APP_MEMORY_SIZE,
                      MPU_ACCESS_PRW_UR, MPU_MEMORY_EXTERNAL_SRAM,
                      0 // executable
    );
    SOS_DEBUG_LINE_TRACE();
    break;

  case SOS_EVENT_ROOT_INVALID_PIN_ASSIGNMENT: {
    const mcu_pin_t *pin = args;
    sos_debug_log_error(SOS_DEBUG_SYS, "bad pin assignment %d.%d", pin->port,
                        pin->pin);
  } break;

  case SOS_EVENT_START_LINK:
    SOS_DEBUG_LINE_TRACE();
#if _IS_BOOT == 0
    SOS_DEBUG_LINE_TRACE();
    usleep(5000);
    lvgl_config_initialize_display();
    SOS_DEBUG_LINE_TRACE();
#endif

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

pthread_t os_start_thread(void *(*thread_function)(void *),
                          void *thread_argument, u32 stack_size,
                          int scheduler_policy, int scheduler_priority) {
  int result;
  pthread_attr_t attr;
  pthread_t tmp;

  pthread_attr_init(&attr);

  if (pthread_attr_setstacksize(&attr, stack_size) < 0) {
    sos_debug_log_error(SOS_DEBUG_SOCKET, "Failed to set stack size");
  }

  if (pthread_attr_setschedpolicy(&attr, scheduler_policy) < 0) {
    sos_debug_log_error(SOS_DEBUG_SOCKET, "Failed to set policy");
  }

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  struct sched_param param;
  param.sched_priority = scheduler_priority;

  if (pthread_attr_setschedparam(&attr, &param) < 0) {
    sos_debug_log_error(SOS_DEBUG_SOCKET, "Failed to set priority");
  }

  result = pthread_create(&tmp, &attr, thread_function, thread_argument);
  if (result < 0) {
    sos_debug_log_error(SOS_DEBUG_SOCKET, "Failed to create thread");
  }

  return tmp;
}
