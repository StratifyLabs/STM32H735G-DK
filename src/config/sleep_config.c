

//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include "config.h"

void sleep_idle() { __WFI(); }

void sleep_hibernate(int seconds) {
  // set deep sleep
  __WFI();
}

void sleep_powerdown() {
  // set deep sleep with standby
  __WFI();
}
