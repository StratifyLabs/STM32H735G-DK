//Copyright 2021 Stratify Labs, See LICENSE.md for details

#ifndef CONFIG_CACHE_CONFIG_H
#define CONFIG_CACHE_CONFIG_H

#include <sos/config.h>

void cache_enable();
void cache_disable();
void cache_invalidate_instruction();
void cache_invalidate_data();
void cache_invalidate_data_block(void *address, size_t size);
void cache_clean_data();
void cache_clean_data_block(void *address, size_t size);

#endif // CONFIG_CACHE_CONFIG_H
