//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_CLOCK_CONFIG_H
#define CONFIG_CLOCK_CONFIG_H

#include <sos/config.h>

void clock_initialize(
  int (*handle_match_channel0)(void *context, const mcu_event_t *data),
  int (*handle_match_channel1)(void *context, const mcu_event_t *data),
  int (*handle_overflow)(void *context, const mcu_event_t *data));
void clock_enable();
u32 clock_disable();
void clock_set_channel(const mcu_channel_t *channel);
void clock_get_channel(mcu_channel_t *channel);
u32 clock_microseconds();
u32 clock_nanoseconds();

#endif // CONFIG_CLOCK_CONFIG_H
