
//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <sos/events.h>
#include <sos/debug.h>
#include <cortexm/cortexm.h>

#include "os_config.h"

void os_event_handler(int event, void *args) {

  switch (event) {

  case SOS_EVENT_ROOT_FATAL:
    // start the bootloader on a fatal event
    // mcu_core_invokebootloader(0, 0);
    if (args != 0) {
      sos_debug_printf("Fatal Error %s\n", (const char *)args);
    } else {
      sos_debug_printf("Fatal Error unknown\n");
    }
    cortexm_reset(NULL);
    break;

  case SOS_EVENT_START_LINK:
    break;

  }
}

