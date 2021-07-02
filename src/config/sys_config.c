//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include "sys_config.h"

void sys_initialize() {
  //initialize the board
  //this is one of the first things called
  //it should initialize the CLOCK/PLL
  //run in ROOT mode before the scheduler is started
}

void sys_get_serial_number(mcu_sn_t *serial_number) {
  //populate serial_number
}

int sys_kernel_request(int request, void *arg) {
  //these are custom requests to allow applications
  //to execute kernel functions
  return -1;
}

const void *sys_kernel_request_api(u32 request) {
  //this allows creatined "shared" libraries
  //you return a pointer to a function table
  return NULL;
}

void sys_pio_set_attributes(int port, const pio_attr_t *attr) {
  //convenience function to configuring IO
  //always called in ROOT mode
}

void sys_pio_write(int port, u32 mask, int value) {
  //convenience function to writing IO
  //always called in ROOT mode
}

u32 sys_pio_read(int port, u32 mask) { 
    //convenience function to reading IO
  //always called in ROOT mode
  return 0; 
}
