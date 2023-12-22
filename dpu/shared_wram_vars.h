#ifndef __SHARED_WRAM_VARS_H
#define __SHARED_WRAM_VARS_H

#include "mram_space_manage.h"
#include "vector.h"
#include "kv_cache.h"
#include <defs.h>

#define PROCESS_GRAIN_SIZE 8

extern int global_init_flag;
extern __mram_noinit A_vector gloal_A_vetor;
extern __mram_noinit vector global_inter_O_vectors[NR_SLAVE_TASKLETS];
extern vector_dpu_ptr global_Q_vector;
extern vector_dpu_ptr global_O_vector;
extern __mram_ptr kv_cache *global_KV_cache;

#endif