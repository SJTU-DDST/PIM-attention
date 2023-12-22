#include <gtest/gtest.h>

#include "../attention/attention.hpp"
#include "../attention/host_util.h"
#include "../model/model.h"

TEST(AttentionTest, OnlyCPU) {
    #define ParaType MODEL_PARA_TYPE
    int64_t begin, last;
    token<ParaType> q;
    token<ParaType> ans(0);
    kv_cache<ParaType> *kv = new kv_cache<ParaType>();
    kv_cache<ParaType> *fuse = new kv_cache<ParaType>(2);

    begin = usec();
    multi_head_attention(q, *kv, ans);
    last = usec();

    std::cout << ans.vectors[0];

    printf("multi_head_attention elapse time: %ld\n", last - begin);
    delete kv;
    delete fuse;
}
