// Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <sdk/types.h>

#include <sos/arch.h>
#include <sos/boot/boot_debug.h>
#include <sos/config.h>
#include <sos/fs/devfs.h>

#include <mcu/flash.h>

#include <stm32h7xx/stm32h7xx_hal.h>
#include <stm32h7xx/stm32h7xx_hal_gpio.h>

#include "boot_link_config.h"

const struct __sFILE_fake __sf_fake_stdin;
const struct __sFILE_fake __sf_fake_stdout;
const struct __sFILE_fake __sf_fake_stderr;

#if __KERNEL_START_ADDRESS == __BOOT_START_ADDRESS
#error "Bootloader will hardfault if kernel and boot start are the same address"
#endif

#include "../src/config.h"

void boot_event_handler(int event, void *args) {
  MCU_UNUSED_ARGUMENT(event);
  MCU_UNUSED_ARGUMENT(args);
  // dstr("event:"); dint(event); dstr("\n");

  cortexm_auth_handle_event(event, args);
}

void boot_invoke_bootloader(void *args) {
  MCU_UNUSED_ARGUMENT(args);
  // write SW location with key and then reset
  u32 *bootloader_software_request_address =
      (u32 *)sos_config.boot.software_bootloader_request_address;
  *bootloader_software_request_address =
      sos_config.boot.software_bootloader_request_value;

  sos_config.cache.clean_data();
  cortexm_reset(0);
}

int boot_is_bootloader_requested() {
  // check for SW boot request
  u32 *address = (u32 *)sos_config.boot.software_bootloader_request_address;
  const int is_software_request =
      (*address == sos_config.boot.software_bootloader_request_value);
  *address = 0;
  if (is_software_request) {
    return 1;
  }

  __HAL_RCC_GPIOC_CLK_ENABLE();
  const pio_attr_t attr = {.o_flags = PIO_FLAG_SET_INPUT,
                           .o_pinmask = (1 << 13)};
  sos_config.sys.pio_set_attributes(2, &attr);
  const u32 value = sos_config.sys.pio_read(2, attr.o_pinmask);
  if (value != 0) {
    return 1;
  }

  return 0;
}

int boot_flash_erase_page(const devfs_handle_t *handle, void *ctl) {
  return mcu_flash_erasepage(handle, ctl);
}

int boot_flash_write_page(const devfs_handle_t *handle, void *ctl) {
  return mcu_flash_writepage(handle, ctl);
}
