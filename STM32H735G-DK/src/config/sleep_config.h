//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_SLEEP_CONFIG_H
#define CONFIG_SLEEP_CONFIG_H

#include <sos/config.h>

void sleep_idle();
void sleep_hibernate(int seconds);
void sleep_powerdown();

#endif // CONFIG_SLEEP_CONFIG_H
