
#include <sos/dev/appfs.h>
#include <device/appfs.h>
#include <mcu/flash.h>

#include <fatfs/fatfs.h>

#include "config.h"
#include "fs_config.h"
#include "devfs_config.h"

#define RAM_PAGES (320 - (CONFIG_SYSTEM_MEMORY_SIZE / 1024UL))
#define FLASH_START (0x08000000 + 128 * 1024UL)
#define RAM_START (0x24000000 + CONFIG_SYSTEM_MEMORY_SIZE)

#define DEVFS_OFFSET 1

// Application Filesystem ------------------------------------------
static u32 ram_usage_table[APPFS_RAM_USAGE_WORDS(RAM_PAGES)] MCU_SYS_MEM;

// flash doesn't need config or state
static const devfs_device_t flash0 =
    DEVFS_DEVICE("flash0", mcu_flash, 0, 0, 0, 0666, SYSFS_ROOT, S_IFBLK);

const appfs_mem_config_t appfs_mem_config = {
    .usage_size = sizeof(ram_usage_table),
    .section_count = 2,
    .usage = ram_usage_table,
    .flash_driver = &flash0,
    .sections = {
        {.o_flags = MEM_FLAG_IS_FLASH,
         .page_count = 3,
         .page_size = 128 * 1024UL,
         .address = FLASH_START},
        // the last 4 128K flash pages are used for the OS
        {.o_flags = MEM_FLAG_IS_RAM,
         .page_count = RAM_PAGES,
         .page_size = MCU_RAM_PAGE_SIZE,
         .address = RAM_START},
    }};

const devfs_device_t mem0 = DEVFS_DEVICE(
    "mem0", appfs_mem, 0, &appfs_mem_config, 0, 0666, SYSFS_ROOT, S_IFBLK);


static void svcall_is_fatfs_drive_present(void *args) {
  // card detect is PD3
  int *is_present = args;
  *is_present
      = (sos_config.sys.pio_read(CONFIG_CARD_PRESENT_PORT, CONFIG_CARD_PRESENT_PINMASK) == 0);
}

static int is_fatfs_drive_present() {
  int is_present = 0;
  cortexm_svcall(svcall_is_fatfs_drive_present, &is_present);
  return is_present;
}

fatfs_state_t fatfs_state;
const fatfs_config_t fatfs_configuration = {
    .drive = {
        .devfs = &(sysfs_list[DEVFS_OFFSET]),
        .name = "drive0",
        .state = &fatfs_state.drive
    },
    .is_drive_present = is_fatfs_drive_present,
    .partition = {
        .block_offset = 0,
        .block_count = 0
    },
    .wait_busy_microseconds = 25,
    .wait_busy_timeout_count = 10000,
    .vol_id = 0
};


// Root Filesystem---------------------------------------------------

/*
 * This is the root filesystem that determines what is mounted at /.
 *
 * The default is /app (for installing and running applciations in RAM and
 * flash) and /dev which provides the device tree defined above.
 *
 * Additional filesystems (such as FatFs) can be added if the hardware and
 * drivers are provided by the board.
 *
 */



const sysfs_t sysfs_list[] = {
    // managing applications
    APPFS_MOUNT("/app", &mem0, 0777, SYSFS_ROOT),
    // the list of devices
    DEVFS_MOUNT("/dev", devfs_list, 0777, SYSFS_ROOT),
    FATFS_MOUNT("/home", &fatfs_configuration, 0777, SYSFS_ROOT),
    // root mount
    SYSFS_MOUNT("/", sysfs_list, 0777, SYSFS_ROOT), SYSFS_TERMINATOR};
