//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_USB_CONFIG_H
#define CONFIG_USB_CONFIG_H

#include <sos/config.h>

int usb_set_attributes(const devfs_handle_t *handle, void *ctl);
int usb_set_action(const devfs_handle_t *handle, mcu_action_t *action);
void usb_write_endpoint(const devfs_handle_t *handle, u32 endpoint_num,
                        const void *src, u32 size);
int usb_read_endpoint(const devfs_handle_t *handle, u32 endpoint_num,
                      void *dest);

#endif // CONFIG_USB_CONFIG_H
