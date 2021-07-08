
#include <cortexm/task.h>
#include <fcntl.h>
#include <sos/debug.h>
#include <sos/led.h>
#include <sos/link/types.h>
#include <sos/sos.h>
#include <string.h>
#include <device/ffifo.h>

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

#if 0
    stm32h735g_dk_init_ospi_ram();
    SOS_DEBUG_LINE_TRACE();
#endif


    const pio_attr_t attr = { .o_flags = PIO_FLAG_SET_INPUT, .o_pinmask = (1<<13) };
    sos_config.sys.pio_set_attributes(2, &attr);
    sos_debug_printf("PC13 is %d\n", sos_config.sys.pio_read(2, attr.o_pinmask));

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
