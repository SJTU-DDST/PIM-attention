#ifndef __KV_CACHE_H
#define __KV_CACHE_H

#include <stdint.h>
#include "vector.h"

typedef struct _kv_cache
{
    uint32_t num_token;
    vector k_cache[NUM_HEAD][MAX_SEQ_LEN];
    vector v_cache[NUM_HEAD][MAX_SEQ_LEN];
} kv_cache;

kv_cache* kv_cache_create();
void kv_cache_init(kv_cache* cache);

#endif