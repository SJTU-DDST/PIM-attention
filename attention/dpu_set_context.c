#include "dpu_set_context.h"

dpu_set_context *dpu_set_context_create()
{
    dpu_set_context *set;
    set = malloc(sizeof(dpu_set_context));
    if (!set)
    {
        return NULL;
    }

    DPU_ASSERT(dpu_alloc(NR_DPUS, NULL, &(set->dpu_set)));
    DPU_ASSERT(dpu_load(set->dpu_set, DPU_BINARY, NULL));

    return set;
}

void dpu_set_context_free(dpu_set_context *set)
{
    DPU_ASSERT(dpu_free(set->dpu_set));
    free(set);
}

void dpu_set_context_dpu_run(dpu_set_context *set)
{
    DPU_ASSERT(dpu_launch(set->dpu_set, DPU_SYNCHRONOUS));
    // dpu_set_context_log_read(set);
}

void dpu_set_context_log_read(dpu_set_context *set)
{
    struct dpu_set_t dpu;
    DPU_FOREACH(set->dpu_set, dpu)
    {
        DPU_ASSERT(dpu_log_read(dpu, stdout));
    }
}