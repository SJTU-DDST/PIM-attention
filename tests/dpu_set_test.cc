
#include <gtest/gtest.h>

extern "C" {
    #include "../attention/dpu_set_context.h"
}

TEST(DPU_SET_TEST, HelloWorld) {
    dpu_set_context *dpu_set = dpu_set_context_create();
    dpu_set_context_dpu_run(dpu_set);
    dpu_set_context_log_read(dpu_set);
    dpu_set_context_free(dpu_set);
}
