
#include <sos/arch.h>
#include <stm32/stm32_config.h>

#include "config.h"

void mcu_reset_watchdog_timer() {}

void mcu_set_interrupt_priority(int number, int priority) {
  NVIC_SetPriority((IRQn_Type)number, priority);
}

int mcu_set_pin_function(const mcu_pin_t *pin, int function, int periph_port) {
  return stm32_mcu_set_pin_function(pin, function, periph_port);
}
