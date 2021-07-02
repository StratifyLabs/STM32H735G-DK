// Copyright and license

//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <sos/config.h>
#include <sos/dev/sys.h>
#include <sos/sos.h>
#include <sos/symbols.h>

#include "cache_config.h"
#include "clock_config.h"
#include "debug_config.h"
#include "fs_config.h"
#include "link_config.h"
#include "mcu_config.h"
#include "os_config.h"
#include "sleep_config.h"
#include "sys_config.h"
#include "usb_config.h"

#include "config.h"
#include "link_config.h"

#if _IS_BOOT
#include <mcu/flash.h>
#define VECTOR_TABLE_ADDRESS __BOOT_START_ADDRESS
#include "../boot/boot_config.h"
#include "../boot/boot_link_config.h"
#else
#define VECTOR_TABLE_ADDRESS __KERNEL_START_ADDRESS
#endif

SOS_DECLARE_SECRET_KEY_32(secret_key)

const sos_config_t sos_config = {
#if !_IS_BOOT
  .fs = {.devfs_list = devfs_list,
         .rootfs_list = sysfs_list,
         .stdin_dev = "/dev/stdio-in",
         .stdout_dev = "/dev/stdio-out",
         .stderr_dev = "/dev/stdio-out",
         .trace_dev = "/dev/trace"},

  .clock = {.initialize = clock_initialize,
            .enable = clock_enable,
            .disable = clock_disable,
            .set_channel = clock_set_channel,
            .get_channel = clock_get_channel,
            .microseconds = clock_microseconds,
            .nanoseconds = NULL},

  .task = {.task_total = CONFIG_TASK_TOTAL,
           .start_stack_size = SOS_DEFAULT_START_STACK_SIZE,
           .start = sos_default_thread,
           .start_args = &link_transport},

  .sleep = {.idle = sleep_idle,
            .hibernate = sleep_hibernate,
            .powerdown = sleep_powerdown},

#endif
  .usb = {.control_endpoint_max_size = 64,
          .set_attributes = usb_set_attributes,
          .set_action = usb_set_action,
          .write_endpoint = usb_write_endpoint,
          .read_endpoint = usb_read_endpoint},

  .cache = {.enable = cache_enable,
            .disable = cache_disable,
            .invalidate_instruction = cache_invalidate_instruction,
            .invalidate_data = cache_invalidate_data,
            .invalidate_data_block = cache_invalidate_data_block,
            .clean_data = cache_clean_data,
            .clean_data_block = cache_clean_data_block,
            .external_sram_policy = SOS_CACHE_DEFAULT_POLICY,
            .sram_policy = SOS_CACHE_DEFAULT_POLICY,
            .flash_policy= SOS_CACHE_DEFAULT_POLICY,
            .peripherals_policy= SOS_CACHE_PERIPHERALS_POLICY,
            .lcd_policy= SOS_CACHE_PERIPHERALS_POLICY},

  .mcu = {.interrupt_request_total = MCU_LAST_IRQ + 1,
          .interrupt_middle_priority = MCU_MIDDLE_IRQ_PRIORITY,
          .set_interrupt_priority = mcu_set_interrupt_priority,
          .reset_watchdog_timer = mcu_reset_watchdog_timer,
          .set_pin_function = mcu_set_pin_function},

  .sys = {.initialize = sys_initialize,
          .bootloader_start_address = __BOOT_START_ADDRESS,
          .memory_size = SYSTEM_MEMORY_SIZE,
          .get_serial_number = sys_get_serial_number,
          .os_mpu_text_mask = 0,
          .flags =
            SYS_FLAG_IS_STDIO_FIFO | SYS_FLAG_IS_TRACE,
          .name = SL_CONFIG_NAME,
          .version = SL_CONFIG_VERSION_STRING,
          .git_hash = SOS_GIT_HASH,
          .mcu_git_hash = NULL,
          .id = SL_CONFIG_DOCUMENT_ID,
          .team_id = SL_CONFIG_TEAM_ID,
#if _IS_BOOT
          .secret_key_size = 32,
          .secret_key_address = secret_key,
#else
    .secret_key_size = 0,
    .secret_key_address = 0,
#endif
          .vector_table = (void *)(VECTOR_TABLE_ADDRESS),
          .pio_write = sys_pio_write,
          .pio_read = sys_pio_read,
          .pio_set_attributes = sys_pio_set_attributes,
          .core_clock_frequency = CONFIG_SYSTEM_CLOCK,
#if !_IS_BOOT
          .kernel_request = sys_kernel_request,
          .kernel_request_api = sys_kernel_request_api
#endif
  },

  .debug = {.initialize = debug_initialize,
            .write = debug_write,
#if _IS_BOOT
            .trace_event = NULL,
#else
            .trace_event = debug_trace_event,
#endif
            .disable_led = debug_disable_led,
            .enable_led = debug_enable_led,
            .flags = SOS_BOARD_DEBUG_FLAGS},

#if _IS_BOOT
  .boot = {.api = {.code_size = (u32)&_etext,
                   .exec = boot_invoke_bootloader,
                   .event = boot_event_handler},
           .program_start_address = __KERNEL_START_ADDRESS,
           .software_bootloader_request_address = 0x20004000,
           .software_bootloader_request_value = 0x55AA55AA,
           .is_bootloader_requested = boot_is_bootloader_requested,
           .flash_handle = {.port = 0},
           .flash_erase_page = mcu_flash_erasepage,
           .flash_write_page = mcu_flash_writepage,
           .link_transport_driver = &boot_link_usb_transport},
  .event_handler = boot_event_handler,
#else
  .event_handler = os_event_handler,
#endif
  .socket_api = NULL};

// This declares the task tables required by Stratify OS
SOS_DECLARE_TASK_TABLE(SOS_BOARD_TASK_TOTAL);


