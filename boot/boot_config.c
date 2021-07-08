//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <sdk/types.h>
#include <sos/arch.h>
#include <sos/config.h>
#include <sos/fs/devfs.h>
#include <sos/boot/boot_debug.h>

#include <mcu/flash.h>

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
  //dstr("event:"); dint(event); dstr("\n");

}

int boot_is_bootloader_requested() {

  //check for SW boot request
  u32 * address = (u32*)sos_config.boot.software_bootloader_request_address;
  const int is_software_request = (*address == sos_config.boot.software_bootloader_request_value);
  *address = 0;
  if( is_software_request ){
    return 1;
  }

  GPIO_InitTypeDef init = {};
  init.Pin = (1<<13);
  init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
  init.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &init);
  cortexm_delay_ms(3);
  //check the button -- PC13 is high when button is pressed
  if( HAL_GPIO_ReadPin(GPIOC, init.Pin) == GPIO_PIN_SET ){
    //return 1;
  }


  return 0;
}

int boot_flash_erase_page(const devfs_handle_t *handle, void *ctl) {
  return mcu_flash_erasepage(handle, ctl);
}

int boot_flash_write_page(const devfs_handle_t *handle, void *ctl) {
  return mcu_flash_writepage(handle, ctl);
}

