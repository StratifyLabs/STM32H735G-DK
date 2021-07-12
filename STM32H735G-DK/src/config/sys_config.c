

#include <stm32_config.h>

#if _IS_BOOT == 0
#include <lvgl_api.h>
#endif

#include "stm32/stm32h735g-dk.h"
#include "config.h"
#include "lvgl_config.h"

void sys_initialize() {
  stm32_initialize();
  SystemClock_Config();
  stm32_initialize_systick();
}

void sys_get_serial_number(mcu_sn_t *serial_number) {
  stm32_get_serial_number(serial_number);
}

int sys_kernel_request(int request, void *arg) {
  MCU_UNUSED_ARGUMENT(arg);

#if _IS_BOOT == 0
  if( request == LVGL_REQUEST_START ){
    lvgl_config_start();
    return 0;
  }
#else
  MCU_UNUSED_ARGUMENT(request);
#endif

  return -1;
}

const void *sys_kernel_request_api(u32 request) {
  switch (request) {
#if !_IS_BOOT
  case LVGL_API_REQUEST:
    return &lvgl_api;
#endif
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
