

#include <stm32_config.h>

#if _IS_BOOT == 0
#include <lvgl_api.h>
#endif

#include <micro_ecc_api.h>
#include <tinycrypt_api.h>


#include "stm32/stm32h735g-dk.h"
#include "sys_config.h"
#include "lvgl_config.h"

const appfs_public_key_t public_keys[] = {
    {.index = 0,
     .id = "RhnmvxQ8D4tlh02L8693",
     .value = {0x35, 0x67, 0x14, 0xf1, 0xe0, 0xbc, 0xc4, 0x71, 0xb5, 0x42, 0x08,
               0xde, 0x23, 0x3f, 0xb0, 0x09, 0x85, 0xcc, 0x8d, 0xbf, 0x42, 0x42,
               0xa3, 0x7f, 0x97, 0x7d, 0x9e, 0x77, 0xaa, 0x67, 0x09, 0x93, 0x2d,
               0x44, 0xe1, 0x00, 0x04, 0x5b, 0x69, 0xa5, 0xd2, 0xcf, 0x9d, 0x38,
               0x11, 0x35, 0x41, 0x72, 0x0b, 0x27, 0xa4, 0x41, 0xaa, 0x61, 0x28,
               0x7e, 0x3b, 0x4f, 0x0d, 0x09, 0x55, 0x6d, 0x18, 0xda},
     // allow all APPFS flags when installing: e.g. APPFS_FLAG_IS_AUTHENTICATED
     .o_flags = 0xffffffff},
    {.index = 1,
     .id = "162ZEPiD33bF1T8diV0t",
     .value = {0x3b, 0x79, 0x1c, 0x4e, 0x97, 0x9e, 0x19, 0xbf, 0x34, 0x65, 0xba,
               0xd7, 0x39, 0x08, 0xa4, 0x7b, 0x3c, 0x24, 0x3e, 0xde, 0x3c, 0x34,
               0x89, 0x24, 0x54, 0x22, 0x0b, 0xcb, 0xb8, 0xc4, 0xb9, 0x5c, 0x23,
               0xd5, 0x71, 0x58, 0xf2, 0x28, 0xfe, 0x1a, 0xb5, 0xa8, 0x35, 0xfe,
               0xa5, 0x5a, 0xb9, 0x0d, 0x02, 0xc1, 0x32, 0x48, 0x3d, 0xea, 0x71,
               0x74, 0x14, 0x67, 0x50, 0xdd, 0xaa, 0x41, 0x2d, 0x2a},
     // allow all APPFS flags when installing: e.g. APPFS_FLAG_IS_AUTHENTICATED
     .o_flags = 0xffffffff}};

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
  if( request == LVGL_REQUEST_GET_FONT ){
    return lvgl_get_font(arg);
  }
  if( request == LVGL_REQUEST_GET_THEME ){
    return lvgl_get_theme(arg);
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
  case CRYPT_SHA256_API_REQUEST:
    return &tinycrypt_sha256_api;
  case CRYPT_ECC_API_REQUEST:
    return &micro_ecc_api;
#endif
#if INCLUDE_ETHERNET && INCLUDE_TLS && !_IS_BOOT
  case MBEDTLS_API_REQUEST:
    return &mbedtls_api; // about 200KB
#endif
#if INCLUDE_JANSSON_API && !_IS_BOOT
  case JANSSON_API_REQUEST:
    return &jansson_api; // about 20KB
#endif

#if _IS_BOOT
  case CRYPT_ECC_ROOT_API_REQUEST:
    return &micro_ecc_root_api;
  case CRYPT_SHA256_ROOT_API_REQUEST:
    return &tinycrypt_sha256_root_api;
#endif

  }
  return NULL;
}

void sys_pio_set_attributes(int port, const pio_attr_t *attr) {
  stm32_pio_set_attributes(port, attr);
}

void sys_pio_write(int port, u32 mask, int value) {
  stm32_pio_write(port, mask, value);
}

u32 sys_pio_read(int port, u32 mask) { return stm32_pio_read(port, mask); }

int sys_get_public_key(u32 index, appfs_public_key_t *dest) {
  if (index < sizeof(public_keys) / sizeof(appfs_public_key_t)) {
    *dest = public_keys[index];
    return 0;
  }

  *dest = (appfs_public_key_t){};
  return -1;
}
