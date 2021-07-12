#ifndef BOOT_CONFIG_H
#define BOOT_CONFIG_H

#include <sos/fs/devfs.h>

void boot_event_handler(int event, void *args);
int boot_is_bootloader_requested();
int boot_flash_erase_page(const devfs_handle_t *handle, void *ctl);
int boot_flash_write_page(const devfs_handle_t *handle, void *ctl);

#endif // BOOT_CONFIG_H
