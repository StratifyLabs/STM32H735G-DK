
//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_LINK_CONFIG_H_
#define CONFIG_LINK_CONFIG_H_

#include <sos/link/transport_usb_link.h>
#include <device/device_fifo.h>

extern link_transport_driver_t link_transport;

extern const device_fifo_config_t usb_device_fifo_config;
extern device_fifo_state_t usb_device_fifo_state;

#endif /* CONFIG_LINK_CONFIG_H_ */
