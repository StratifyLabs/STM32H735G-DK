
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

#if _IS_BOOT
#include "../boot/boot_config.h"
#endif

#include "config.h"
#include "lvgl_config.h"
#include "os_config.h"
#include "stm32/stm32h735g-dk.h"

#include "stm32/stm32h735g_discovery_lcd.h"

#define OS_CONFIG_VIDEO_MEMORY_MPU_REGION 0
#define OS_CONFIG_APP_MEMORY_MPU_REGION 1

void svcall_flush_video_memory(void *args) {
  CORTEXM_SVCALL_ENTER();
  MCU_UNUSED_ARGUMENT(args);
  SOS_DEBUG_LINE_TRACE();

  BSP_LCD_WritePixel(0, 10, 10, 0xffff);

  sos_config.cache.clean_data_block((void *)CONFIG_VIDEO_MEMORY_ADDRESS,
                                    CONFIG_VIDEO_MEMORY_SIZE);
}

#if _IS_BOOT
static void *stack_ptr;
static void (*app_reset)();
#endif

void os_event_handler(int event, void *args) {
  switch (event) {
  case SOS_EVENT_ROOT_RESET:
#if _IS_BOOT
    stack_ptr = (void *)(((u32 *)sos_config.boot.program_start_address)[0]);
    app_reset =
        (void (*)())((((u32 *)sos_config.boot.program_start_address)[1]));
    if (boot_is_bootloader_requested() == 0) {
      // execute the reset vector
      if ((u32)stack_ptr != 0xffffffff && (u32)app_reset != 0xffffffff) {
        app_reset();
      }
    }
#endif

    break;

  case SOS_EVENT_FATAL:
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
    mpu_enable_region(OS_CONFIG_VIDEO_MEMORY_MPU_REGION,
                      (void *)CONFIG_VIDEO_MEMORY_ADDRESS,
                      CONFIG_VIDEO_MEMORY_SIZE, MPU_ACCESS_PRW_URW,
                      MPU_MEMORY_EXTERNAL_SRAM,
                      0 // executable
    );

    // background access to app region -- allows caching for general access by
    // appfs
    mpu_enable_region(OS_CONFIG_APP_MEMORY_MPU_REGION,
                      (void *)CONFIG_APP_MEMORY_ADDRESS, CONFIG_APP_MEMORY_SIZE,
                      MPU_ACCESS_PRW_UR, MPU_MEMORY_EXTERNAL_SRAM,
                      0 // executable
    );
    break;

  case SOS_EVENT_ROOT_INVALID_PIN_ASSIGNMENT: {
    const mcu_pin_t *pin = args;
    sos_debug_log_error(SOS_DEBUG_SYS, "bad pin assignment %d.%d", pin->port,
                        pin->pin);
  } break;

  case SOS_EVENT_START_LINK:
#if _IS_BOOT == 0
    lvgl_config_initialize_display();
#endif

#if INCLUDE_ETHERNET
    // start LWIP
    sos_debug_log_info(SOS_DEBUG_USER0, "Start LWIP");
    usleep(500 * 1000);
    lwip_api.startup(&lwip_api);
#endif

    sos_debug_log_info(SOS_DEBUG_USER0, "Start LED %d");
#if _IS_BOOT
    sos_led_boot_startup();
#else
    sos_led_startup();
#endif
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
