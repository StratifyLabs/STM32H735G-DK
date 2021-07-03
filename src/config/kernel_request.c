
#include <jansson/jansson_api.h>
#include <mbedtls_api.h>
#include <sdk/api.h>

#include "config.h"

int os_kernel_request(int req, void *arg) { return -1; }

const void *os_kernel_request_api(u32 request) {
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
