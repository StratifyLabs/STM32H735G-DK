//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <sos/arch.h>

#include <sos/fs/appfs.h>
#include <sos/dev/appfs.h>
#include <device/appfs.h>
#include <device/mem.h>
#include <mcu/flash.h>

#include "fs_config.h"
#include "config.h"


//configure the application filesystem to use the extra flash and RAM
//available in the system
#define APPFS_RAM_PAGES 32
u32 ram_usage_table[APPFS_RAM_USAGE_WORDS(APPFS_RAM_PAGES)] MCU_SYS_MEM;

const devfs_device_t flash0
  = DEVFS_DEVICE("flash0", mcu_flash, 0, 0, 0, 0666, SYSFS_ROOT, S_IFBLK);

const appfs_mem_config_t appfs_mem_config = {
  .usage_size = sizeof(ram_usage_table),
  .usage = ram_usage_table,
  .flash_driver = &flash0,
  .section_count = 2,
  .sections = {
    {.o_flags = MEM_FLAG_IS_FLASH,
     .page_count = 4,
     .page_size = 16 * 1024UL,
     .address = 0x00000000},
    {.o_flags = MEM_FLAG_IS_RAM,
     .page_count = APPFS_RAM_PAGES,
     .page_size = MCU_RAM_PAGE_SIZE,
     .address = 0x00000000}}};

const devfs_device_t mem0 = DEVFS_DEVICE(
  "mem0",
  appfs_mem,
  0,
  &appfs_mem_config,
  0,
  0666,
  SYSFS_ROOT,
  S_IFBLK);

const sysfs_t sysfs_list[] = {
  APPFS_MOUNT(
    "/app",
    &mem0,
    0777,
    SYSFS_ROOT), // the folder for ram/flash applications
  DEVFS_MOUNT("/dev", devfs_list, 0777, SYSFS_ROOT), // the list of devices
  SYSFS_MOUNT(
    "/",
    sysfs_list,
    0777,
    SYSFS_ROOT), // the root filesystem (must be last)
  SYSFS_TERMINATOR};
