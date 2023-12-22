#include "shared_wram_vars.h"

int global_init_flag = 0;

vector_dpu_ptr global_Q_vector = (vector_dpu_ptr)(Q_VECTOR_SPACE_ADDR);
vector_dpu_ptr global_O_vector = (vector_dpu_ptr)(O_VECTOR_SPACE_ADDR);
__mram_ptr kv_cache *global_KV_cache = (__mram_ptr kv_cache *)(KV_CACHE_SPACE_ADDR);
__mram_noinit A_vector gloal_A_vetor;
__mram_noinit vector global_inter_O_vectors[NR_SLAVE_TASKLETS];
