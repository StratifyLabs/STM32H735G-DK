//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <device/device_fifo.h>
#include <fcntl.h>
#include <mcu/pio.h>
#include <unistd.h>
#include <stm32/stm32_types.h>

#include "boot_link_config.h"
#include "config.h"

usb_state_t usb_device_state MCU_SYS_MEM;
const usb_config_t usb_device_config = {.port = 0, .attr = {}};
const devfs_handle_t usb_handle = {
  .port = 0, .config = &usb_device_config, .state = &usb_device_state};

static link_transport_phy_t link_transport_open(const char *name,
                                                const void *options);

link_transport_driver_t boot_link_usb_transport = {
  .handle = -1,
  .open = link_transport_open,
  .read = boot_link_transport_usb_read,
  .write = boot_link_transport_usb_write,
  .close = boot_link_transport_usb_close,
  .wait = boot_link_transport_usb_wait,
  .flush = boot_link_transport_usb_flush,
  .transport_read = link1_transport_slaveread,
  .transport_write = link1_transport_slavewrite,
  .o_flags = 0,
  .timeout = 500};

static usbd_control_t m_usb_control;

link_transport_phy_t link_transport_open(const char *name,
                                         const void *options) {
  link_transport_phy_t fd;
  usb_attr_t usb_attr = {0};

  // initialize the USB
  memset(&(usb_attr.pin_assignment), 0xff, sizeof(usb_pin_assignment_t));
  usb_attr.o_flags = USB_FLAG_SET_DEVICE;
  usb_attr.pin_assignment.dp = mcu_pin(0xff, 0xff);
  usb_attr.pin_assignment.dm = mcu_pin(0xff, 0xff);
  // usb_attr.freq = mcu_board_config.core_osc_freq;
  fd = boot_link_transport_usb_open(name, &m_usb_control,
                                    &sos_link_transport_usb_link_constants,
                                    &usb_handle, &usb_attr, mcu_pin(0xff, 0xff),
                                    1); // active high up pin

  return fd;
}
