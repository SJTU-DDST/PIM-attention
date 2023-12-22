#include "test.h"

void test()
{
    kv_cache_init(global_KV_cache, 1);
    vector_cache cache1, cache2;
    vector_dpu_ptr ptr1, ptr2;
    ptr1 = kv_cache_get_kth_k_vector(global_KV_cache, 0);
    ptr2 = kv_cache_get_kth_k_vector(global_KV_cache, 1);
    printf("ptr1: %p, ptr: %p\n", ptr1, ptr2);
    vector_load(&cache1, ptr1);
    vector_load(&cache2, ptr2);
    MODEL_PARA_TYPE ret = vector_cache_dot(&cache1, &cache2);
    printf("vector_cache_dot: %d\n", ret);
    vector_cache_add(&cache1, &cache2, 2);
    vector_store(&cache1, global_O_vector);
    vector_dump(global_O_vector);
}