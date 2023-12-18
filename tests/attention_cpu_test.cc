#include <gtest/gtest.h>

extern "C" {
    #include "../attention/attention.h"
}

TEST(AttentionTest, OnlyCPU) {
    query *q = query_create();
    query_init(q);
    kv_cache *kv = kv_cache_create();
    kv_cache_init(kv);
    answer *ans = answer_create();
    
    kv_cache *fuse = kv_cache_create();
    kv_cache_init(fuse);

    multi_head_attention(q, kv, ans);
}
