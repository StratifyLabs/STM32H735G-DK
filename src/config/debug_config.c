
//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include "debug_config.h"


void debug_initialize() {
  //initialize the serial debug output
  //initialize the debug LED
}

void debug_write(const void *buf, int nbyte) {
  //write the serial debut output
}

void debug_enable_led() {
  //turn the debug LED on
}

void debug_disable_led() {
  //turn the debug LED off
}

void debug_trace_event(void * event){
  //write the event to the trace ffifo
}