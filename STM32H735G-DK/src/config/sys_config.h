//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_SYS_CONFIG_H
#define CONFIG_SYS_CONFIG_H

#include <sos/config.h>
#include <sos/dev/appfs.h>

void sys_initialize();
int sys_kernel_request(int req, void *arg);
const void *sys_kernel_request_api(u32 request);
void sys_get_serial_number(mcu_sn_t *serial_number);
void sys_pio_set_attributes(int port, const pio_attr_t *attr);
void sys_pio_write(int port, u32 mask, int value);
u32 sys_pio_read(int port, u32 mask);
int sys_get_public_key(u32 index, appfs_public_key_t *dest);

#endif // CONFIG_SYS_CONFIG_H
