#include <sos/fs/devfs.h>

#include "devfs_config.h"
#include "link_config.h"


//list of devices for the /dev folder
const devfs_device_t devfs_list[] = {
  // System devices
  // DEVFS_DEVICE(entry name, driver prefix, port number, configuration, state,
  // access, user, type),
  DEVFS_CHAR_DEVICE(
    "stdio-out",
    fifo,
    &stdio_out_config,
    &stdio_out_state,
    0666,
    SYSFS_ROOT),
  DEVFS_CHAR_DEVICE(
    "stdio-in",
    fifo,
    &stdio_in_config,
    &stdio_in_state,
    0666,
    SYSFS_ROOT),
    // system devices
  DEVFS_CHAR_DEVICE("link-phy-usb", device_fifo, &usb_device_fifo_config,
                &usb_device_fifo_state, 0666, SYSFS_ROOT),
  DEVFS_CHAR_DEVICE("sys", sys, 0, 0, 0666, SYSFS_ROOT),
  //add additional devices here
  DEVFS_TERMINATOR};
