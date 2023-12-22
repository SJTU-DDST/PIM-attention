#ifndef __MRAM_SPACE_MANAGE_H
#define __MRAM_SPACE_MANAGE_H

#include <mram.h>
#include "../model/model.h"

#ifndef NR_SLAVE_TASKLETS
#define NR_SLAVE_TASKLETS (NR_TASKLETS - 1)
#endif

#define Q_VECTOR_SPACE_ADDR ((__mram_ptr void *)(DPU_MRAM_HEAP_POINTER))
#define Q_VECTOR_SIZE (sizeof(MODEL_PARA_TYPE) * DIM_HEAD)

#define O_VECTOR_SPACE_ADDR ((__mram_ptr void *)(Q_VECTOR_SPACE_ADDR + Q_VECTOR_SIZE))
#define O_VECTOR_SIZE (sizeof(MODEL_PARA_TYPE) * DIM_HEAD)

#define KV_CACHE_SPACE_ADDR ((__mram_ptr void *)(O_VECTOR_SPACE_ADDR + O_VECTOR_SIZE))
#define KV_CACHE_SIZE (sizeof(MODEL_PARA_TYPE) * DIM_HEAD * MAX_SEQ_LEN)

#endif