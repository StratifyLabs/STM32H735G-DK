
#include <stm32/stm32_config.h>


#include "stm32/stm32h735g-dk.h"
#include "config.h"

void sys_initialize() {
  stm32_initialize();
  SystemClock_Config();
  stm32_initialize_systick();
}

void sys_get_serial_number(mcu_sn_t *serial_number) {
  stm32_get_serial_number(serial_number);
}

int sys_kernel_request(int req, void *arg) {
  MCU_UNUSED_ARGUMENT(req);
  MCU_UNUSED_ARGUMENT(arg);
  return -1;
}

const void *sys_kernel_request_api(u32 request) {
  switch (request) {
#if INCLUDE_AUTH
  case CRYPT_SHA256_API_REQUEST:
    return &mbedtls_crypt_sha256_api;
#endif
#if INCLUDE_ETHERNET && INCLUDE_TLS
  case MBEDTLS_API_REQUEST:
    return &mbedtls_api; // about 200KB
#endif
#if INCLUDE_JANSSON_API
  case JANSSON_API_REQUEST:
    return &jansson_api; // about 20KB
#endif
  }
  return 0;
}

void sys_pio_set_attributes(int port, const pio_attr_t *attr) {
  stm32_pio_set_attributes(port, attr);
}

void sys_pio_write(int port, u32 mask, int value) {
  stm32_pio_write(port, mask, value);
}

u32 sys_pio_read(int port, u32 mask) { return stm32_pio_read(port, mask); }
