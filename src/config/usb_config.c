#include <stm32/stm32_config.h>

int usb_set_attributes(const devfs_handle_t *handle, void *ctl) {
  return stm32_usb_set_attributes(handle, ctl);
}

int usb_set_action(const devfs_handle_t *handle, mcu_action_t *action) {
  return stm32_usb_set_action(handle, action);
}

void usb_write_endpoint(const devfs_handle_t *handle, u32 endpoint_num,
                        const void *src, u32 size) {
  stm32_usb_write_endpoint(handle, endpoint_num, src, size);
}

int usb_read_endpoint(const devfs_handle_t *handle, u32 endpoint_num,
                      void *dest) {
  return stm32_usb_read_endpoint(handle, endpoint_num, dest);
}
