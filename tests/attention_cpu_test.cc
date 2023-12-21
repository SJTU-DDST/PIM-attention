#include <gtest/gtest.h>

#include "../attention/attention.hpp"

TEST(AttentionTest, OnlyCPU) {
    #define ParaType int32_t
    token<ParaType> q;
    token<ParaType> ans(0);
    kv_cache<ParaType> *kv = new kv_cache<ParaType>();
    kv_cache<ParaType> *fuse = new kv_cache<ParaType>(2);

    multi_head_attention(q, *kv, ans);

    delete kv;
    delete fuse;
}
