//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include "config.h"

#define USE_CACHE 0

void cache_enable() {
#if USE_CACHE
  SCB_EnableICache();
  SCB_EnableDCache();
#endif
}

void cache_disable() {
#if USE_CACHE
  SCB_DisableICache();
  SCB_DisableDCache();
#endif
}
void cache_invalidate_instruction() {
#if USE_CACHE
  SCB_InvalidateICache();
#endif
}
void cache_invalidate_data() {
#if USE_CACHE
  SCB_InvalidateDCache();
#endif
}
void cache_invalidate_data_block(void *address, size_t size) {
#if USE_CACHE
  SCB_InvalidateDCache_by_Addr(address, size);
#else
  MCU_UNUSED_ARGUMENT(address);
  MCU_UNUSED_ARGUMENT(size);
#endif
}
void cache_clean_data() {
#if USE_CACHE
    SCB_CleanDCache();
#endif
}
void cache_clean_data_block(void *address, size_t size) {
#if USE_CACHE
  SCB_CleanDCache_by_Addr(addr, size);
#else
  MCU_UNUSED_ARGUMENT(address);
  MCU_UNUSED_ARGUMENT(size);
#endif
}
