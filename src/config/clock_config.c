
#include <stm32/stm32_config.h>

#include "config.h"
#include "clock_config.h"

void clock_initialize(
    int (*handle_match_channel0)(void *context, const mcu_event_t *data),
    int (*handle_match_channel1)(void *context, const mcu_event_t *data),
    int (*handle_overflow)(void *context, const mcu_event_t *data)) {
  stm32_clock_initialize(handle_match_channel0, handle_match_channel1,
                         handle_overflow);
}

void clock_enable() {
  stm32_clock_enable();
}

u32 clock_disable() {
  return stm32_clock_disable();
}

void clock_set_channel(const mcu_channel_t *channel) {
  stm32_clock_set_channel(channel);
}

void clock_get_channel(mcu_channel_t *channel) {
  stm32_clock_get_channel(channel);
}

u32 clock_microseconds() { return stm32_clock_microseconds(); }
u32 clock_nanoseconds() { return stm32_clock_nanoseconds(); }
