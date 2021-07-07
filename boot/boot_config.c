//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <sdk/types.h>
#include <sos/arch.h>
#include <sos/fs/devfs.h>
#include <sos/boot/boot_debug.h>

#include <mcu/flash.h>

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
  //dstr("event:"); dint(event); dstr("\n");

}

int boot_is_bootloader_requested() {
  return 0;
}

int boot_flash_erase_page(const devfs_handle_t *handle, void *ctl) {
  return mcu_flash_erasepage(handle, ctl);
}

int boot_flash_write_page(const devfs_handle_t *handle, void *ctl) {
  return mcu_flash_writepage(handle, ctl);
}

