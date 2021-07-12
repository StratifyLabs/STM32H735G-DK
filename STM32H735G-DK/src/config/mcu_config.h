//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_MCU_CONFIG_H
#define CONFIG_MCU_CONFIG_H

#include <sdk/types.h>

void mcu_reset_watchdog_timer();
void mcu_set_interrupt_priority(int number, int priority);
int mcu_set_pin_function(const mcu_pin_t *pin, int function, int periph_port);

#endif // CONFIG_MCU_CONFIG_H
