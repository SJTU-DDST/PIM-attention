#include <gtest/gtest.h>
#include "../attention/dpu_set_context.h"
#include "../attention/attention.hpp"
#include "../attention/host_util.h"
#include "../model/model.h"

TEST(DPU_SET_TEST, HelloWorld) {
    #define ParaType MODEL_PARA_TYPE
    token<ParaType> q;
    token<ParaType> ans;
    dpu_set_context dpu_set;
    int64_t begin, last, cur;

    begin = usec();
    last = begin;
    cur = begin;
    dpu_set.dpu_set_context_push_token(q);
    last = cur;
    cur = usec();
    printf("push elapse time: %ld\n", cur - last);
    dpu_set.dpu_set_context_dpu_run();
    last = cur;
    cur = usec();
    printf("run elapse time: %ld\n", cur - last);
    dpu_set.dpu_set_context_pull_token(ans);
    last = cur;
    cur = usec();
    printf("pull elapse time: %ld\n", cur - last);
    std::cout << ans.vectors[0];
    printf("sum elapse time: %ld\n", cur - begin);

    begin = usec();
    last = begin;
    cur = begin;
    dpu_set.dpu_set_context_push_token(q);
    last = cur;
    cur = usec();
    printf("push elapse time: %ld\n", cur - last);
    dpu_set.dpu_set_context_dpu_run();
    last = cur;
    cur = usec();
    printf("run elapse time: %ld\n", cur - last);
    dpu_set.dpu_set_context_pull_token(ans);
    last = cur;
    cur = usec();
    printf("pull elapse time: %ld\n", cur - last);
    std::cout << ans.vectors[0];
    printf("sum elapse time: %ld\n", cur - begin);
}
