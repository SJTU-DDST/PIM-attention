#include "dpu_set_context.h"

dpu_set_context::dpu_set_context()
{
    DPU_ASSERT(dpu_alloc(NR_DPUS, NULL, &dpu_set));
    DPU_ASSERT(dpu_load(dpu_set, DPU_BINARY, NULL));
}

dpu_set_context::~dpu_set_context()
{
    DPU_ASSERT(dpu_free(dpu_set));
}

void dpu_set_context::dpu_set_context_dpu_run(){
    DPU_ASSERT(dpu_launch(dpu_set, DPU_SYNCHRONOUS));
}

void dpu_set_context::dpu_set_context_log_read(){
    struct dpu_set_t dpu;
    DPU_FOREACH(dpu_set, dpu)
    {
        DPU_ASSERT(dpu_log_read(dpu, stdout));
    }
}