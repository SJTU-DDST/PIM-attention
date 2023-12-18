#ifndef _DPU_SET_CONTEXT_H
#define _DPU_SET_CONTEXT_H
#include <dpu.h>
#include <assert.h>
#include <stdint.h>

#ifndef NR_DPUS
#define NR_DPUS 1
#endif

#ifndef DPU_BINARY
#define DPU_BINARY "./dpu_task"
#endif

typedef struct _dpu_set_context
{
    struct dpu_set_t dpu_set;
} dpu_set_context;

// dpu_set_context
dpu_set_context *dpu_set_context_create(void);
void dpu_set_context_dpu_run(dpu_set_context *set);
void dpu_set_context_free(dpu_set_context *set);
void dpu_set_context_log_read(dpu_set_context *set);

#endif