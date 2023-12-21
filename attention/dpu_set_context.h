#ifndef _DPU_SET_CONTEXT_H
#define _DPU_SET_CONTEXT_H

extern "C" {
    #include <dpu.h>
}
#include <cassert>
#include <cstdint>

#ifndef NR_DPUS
#define NR_DPUS 1
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
    void dpu_set_context_dpu_run();
    void dpu_set_context_log_read();
    ~dpu_set_context();
};

#endif