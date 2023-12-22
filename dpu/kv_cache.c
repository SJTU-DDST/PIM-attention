#include "kv_cache.h"

vector_dpu_ptr kv_cache_get_kth_k_vector(__mram_ptr kv_cache *kv, uint32_t k)
{
    return (vector_dpu_ptr)(kv->k_cache[k]);
}

vector_dpu_ptr kv_cache_get_kth_v_vector(__mram_ptr kv_cache *kv, uint32_t k)
{
    return (vector_dpu_ptr)(kv->v_cache[k]);
}

void kv_cache_init(__mram_ptr kv_cache *kv, MODEL_PARA_TYPE default_elem)
{
    vector_dpu_ptr ptr;
    vector_cache cache;

    vector_cache_init(&cache, default_elem);
    for (int i = 0; i < MAX_SEQ_LEN; i++)
    {
        ptr = kv_cache_get_kth_k_vector(kv, i);
        vector_store(&cache, ptr);
        ptr = kv_cache_get_kth_v_vector(kv, i);
        vector_store(&cache, ptr);
    }
}