#ifndef _DPU_SET_CONTEXT_H
#define _DPU_SET_CONTEXT_H

extern "C"
{
#include <dpu.h>
}
#include <cassert>
#include <cstdint>
#include "../model/model.h"
#include "token.hpp"

#ifndef NR_DPUS
#define NR_DPUS NUM_HEAD
#endif

#ifndef DPU_BINARY
#define DPU_BINARY "./dpu_task"
#endif

class dpu_set_context
{
private:
    struct dpu_set_t dpu_set;

public:
    dpu_set_context();
    template <typename Type>
    void dpu_set_context_push_token(token<Type> &q);
    template <typename Type>
    void dpu_set_context_pull_token(token<Type> &ans);
    void dpu_set_context_dpu_run();
    void dpu_set_context_log_read();
    ~dpu_set_context();
};

template <typename Type>
void dpu_set_context::dpu_set_context_push_token(token<Type> &q)
{
    struct dpu_set_t dpu;
    uint32_t each_dpu;

    DPU_FOREACH(dpu_set, dpu, each_dpu)
    {
        DPU_ASSERT(dpu_prepare_xfer(dpu, &(q.vectors[each_dpu])));
    }
    DPU_ASSERT(dpu_push_xfer(dpu_set, DPU_XFER_TO_DPU, DPU_MRAM_HEAP_POINTER_NAME, 0,
                             sizeof(vector<Type>), DPU_XFER_DEFAULT));
}

template <typename Type>
void dpu_set_context::dpu_set_context_pull_token(token<Type> &ans)
{
    struct dpu_set_t dpu;
    uint32_t each_dpu;

    DPU_FOREACH(dpu_set, dpu, each_dpu)
    {
        DPU_ASSERT(dpu_prepare_xfer(dpu, &(ans.vectors[each_dpu])));
    }
    DPU_ASSERT(dpu_push_xfer(dpu_set, DPU_XFER_FROM_DPU, DPU_MRAM_HEAP_POINTER_NAME, sizeof(vector<Type>),
                             sizeof(vector<Type>), DPU_XFER_DEFAULT));
}

#endif