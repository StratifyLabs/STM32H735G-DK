//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_FS_CONFIG_H
#define CONFIG_FS_CONFIG_H

#include <sos/config.h>
#include <sos/fs/appfs.h>
#include <sos/fs/sysfs.h>

extern const sysfs_t sysfs_list[];

#if _IS_BOOT
#define DEVFS_OFFSET 0
#else
#define DEVFS_OFFSET 1
#endif

#endif // CONFIG_FS_CONFIG_H
