//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include "usb_config.h"

int usb_set_attributes(const devfs_handle_t *handle, void *ctl) {
  //allows the USB stack to set USB attributes
  return 0;
}

int usb_set_action(const devfs_handle_t *handle, mcu_action_t *action) {
  //ROOT function to install an action (callback) to the USB driver
  return 0;
}

void usb_write_endpoint(const devfs_handle_t *handle, u32 endpoint_num,
                        const void *src, u32 size) {
    //ROOT function to write a USB endpoint
}

int usb_read_endpoint(const devfs_handle_t *handle, u32 endpoint_num,
                      void *dest) {
  //ROOT function to read a USB endpoint
  return 0;
}
