#include "kv_cache.h"

kv_cache *kv_cache_create()
{
    kv_cache* cache = malloc(sizeof(kv_cache));
    return cache;
}

void kv_cache_init(kv_cache *cache)
{
    cache->num_token = MAX_SEQ_LEN;
    for (int i = 0; i < NUM_HEAD; i++)
    {
        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            vector_init(&(cache->k_cache[i][j]), 1);
            vector_init(&(cache->v_cache[i][j]), 1);
        }
    }
}