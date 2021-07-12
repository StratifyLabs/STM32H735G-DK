//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_DEBUG_CONFIG_H
#define CONFIG_DEBUG_CONFIG_H

#include <sos/config.h>
#include <sos/link/types.h>
#include <device/ffifo.h>

#include "config.h"


void debug_initialize();
void debug_write(const void *buf, int nbyte);
void debug_enable_led();
void debug_disable_led();
void debug_trace_event(void *event);

#endif // CONFIG_DEBUG_CONFIG_H
