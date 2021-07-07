

#include "config.h"

void sleep_idle() {

  //H7 cannot sleep while USB is connected

  //__WFI();
}

void sleep_hibernate(int seconds) {
  // set deep sleep
  __WFI();
}

void sleep_powerdown() {
  // set deep sleep with standby
  __WFI();
}
