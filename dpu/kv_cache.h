#ifndef __KV_CACHE_H
#define __KV_CACHE_H

#include "vector.h"

typedef struct _kv_cache
{
    MODEL_PARA_TYPE k_cache[MAX_SEQ_LEN][VECTOR_SIZE];
    MODEL_PARA_TYPE v_cache[MAX_SEQ_LEN][VECTOR_SIZE];
} kv_cache;

vector_dpu_ptr kv_cache_get_kth_k_vector(__mram_ptr kv_cache *kv, uint32_t k);
vector_dpu_ptr kv_cache_get_kth_v_vector(__mram_ptr kv_cache *kv, uint32_t k);
void kv_cache_init(__mram_ptr kv_cache *kv, MODEL_PARA_TYPE default_elem);

#endif