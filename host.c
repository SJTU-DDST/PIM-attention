#include "attention/attention.h"

int main()
{
    int64_t begin, last;
    query *q = query_create();
    query_init(q);
    kv_cache *kv = kv_cache_create();
    kv_cache_init(kv);
    answer *ans = answer_create();

    kv_cache *fuse = kv_cache_create();
    kv_cache_init(fuse);
    begin = usec();
    multi_head_attention(q, kv, ans);
    last = usec();
    // for (int i = 0; i < NUM_HEAD; i++)
    // {
    //     vector_dump(&(ans->vectors[i]));
    // }
    printf("multi_head_attention elapse time: %ld\n", last - begin);


    dpu_set_context *dpu_set = dpu_set_context_create();
    dpu_set_context_dpu_run(dpu_set);
    dpu_set_context_log_read(dpu_set);
    dpu_set_context_free(dpu_set);

    return 0;
}