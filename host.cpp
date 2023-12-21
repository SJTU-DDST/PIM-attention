#include "attention/attention.hpp"
#include "attention/host_util.h"
#include "attention/dpu_set_context.h"
#include <string>

#define ParaType int32_t

int main()
{
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

    dpu_set_context dpu_set;
    dpu_set.dpu_set_context_dpu_run();
    dpu_set.dpu_set_context_log_read();
    
    return 0;
}