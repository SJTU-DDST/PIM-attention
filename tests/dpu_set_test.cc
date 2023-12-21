#include <gtest/gtest.h>
#include "../attention/dpu_set_context.h"

TEST(DPU_SET_TEST, HelloWorld) {
    dpu_set_context dpu_set;
    dpu_set.dpu_set_context_dpu_run();
    dpu_set.dpu_set_context_log_read();
}
