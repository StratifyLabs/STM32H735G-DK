//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include <device/device_fifo.h>
#include <fcntl.h>
#include <sos/debug.h>
#include <sos/dev/pio.h>
#include <string.h>
#include <unistd.h>

#include "link_config.h"

#define USB_DEVICE_FIFO_BUFFER_SIZE 64
u8 usb_device_fifo_buffer[USB_DEVICE_FIFO_BUFFER_SIZE] MCU_SYS_MEM;
u8 usb_device_fifo_read_buffer[USB_DEVICE_FIFO_BUFFER_SIZE] MCU_SYS_MEM;
device_fifo_state_t usb_device_fifo_state MCU_SYS_MEM;
usb_state_t usb_device_state MCU_SYS_MEM;
const usb_config_t usb_device_config = {.port = SOS_BOARD_USB_PORT, .attr = {}};
const device_fifo_config_t usb_device_fifo_config = {
    .device = DEVFS_DEVICE("usb", mcu_usb, 0, &usb_device_config,
                           &usb_device_state, 0666, SYSFS_ROOT, S_IFCHR),
    .read_location = SOS_LINK_TRANSPORT_USB_BULK_ENDPOINT,
    .write_location = SOS_LINK_TRANSPORT_USB_BULK_ENDPOINT | 0x80,
    .fifo =
        {
            .buffer = usb_device_fifo_buffer,
            .size = USB_DEVICE_FIFO_BUFFER_SIZE,
        },
    .read_buffer = usb_device_fifo_read_buffer,
    .read_buffer_size = USB_DEVICE_FIFO_BUFFER_SIZE,
};


static link_transport_phy_t
link_transport_open(const char *name, const void *options);

link_transport_driver_t link_transport = {
  .handle = -1,
  .open = link_transport_open,
  .read = sos_link_transport_usb_read,
  .write = sos_link_transport_usb_write,
  .close = sos_link_transport_usb_close,
  .wait = sos_link_transport_usb_wait,
  .flush = sos_link_transport_usb_flush,
  .timeout = 500,
  .o_flags = 0, // no checksums -- checksums already happen over USB
  .transport_read = link1_transport_slaveread,
  .transport_write = link1_transport_slavewrite};

static usbd_control_t m_usb_control;
static link_transport_phy_t m_fd;

const usb_attr_t m_usb_attr = {
  .o_flags = USB_FLAG_SET_DEVICE,
  .pin_assignment.dp = {0, 11},
  .pin_assignment.dm = {0, 12},
  .pin_assignment.id = {0xff, 0xff},
  .pin_assignment.vbus = {0xff, 0xff},
  .freq = 0
};

link_transport_phy_t
link_transport_open(const char *name, const void *options) {

  sos_debug_log_info(SOS_DEBUG_USER0, "Open USB");
  m_fd = sos_link_transport_usb_open(
    name,
    &m_usb_control,
    &sos_link_transport_usb_link_constants,
    &usb_device_fifo_config.device.handle,
    &m_usb_attr); // USB pin is active high


  return m_fd;
}
