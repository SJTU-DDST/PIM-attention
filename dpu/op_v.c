#include "op_v.h"

void op_v_run()
{
    uint32_t slave_tasklet_id = me() - 1;
    vector_cache cache_o, cache_v;
    vector_dpu_ptr v;
    __dma_aligned MODEL_PARA_TYPE buffer_A[PROCESS_GRAIN_SIZE];

    vector_cache_init(&cache_o, 0);
    for (int i = slave_tasklet_id * PROCESS_GRAIN_SIZE; i < MAX_SEQ_LEN; i += PROCESS_GRAIN_SIZE * NR_SLAVE_TASKLETS)
    {
        mram_read(gloal_A_vetor.data + i, buffer_A, sizeof(MODEL_PARA_TYPE) * PROCESS_GRAIN_SIZE);
        for (int j = 0; j < PROCESS_GRAIN_SIZE; j++)
        {
            int k = i + j;
            v = kv_cache_get_kth_v_vector(global_KV_cache, k);
            if (k < MAX_SEQ_LEN)
            {
                vector_load(&cache_v, v);
                vector_cache_add(&cache_o, &cache_v, buffer_A[j]);
            }
        }
    }
    mram_write(cache_o.data, &(global_inter_O_vectors[slave_tasklet_id]), sizeof(MODEL_PARA_TYPE) * VECTOR_SIZE);
}

void op_v_reduce()
{
    vector_cache cache_o, cache_v;
    vector_dpu_ptr v;
    vector_cache_init(&cache_o, 0);
    for (int i = 0; i < NR_SLAVE_TASKLETS; i++)
    {
        v = (vector_dpu_ptr)&(global_inter_O_vectors[i]);
        vector_load(&cache_v, v);
        vector_cache_add(&cache_o, &cache_v, 1);
    }
    mram_write(cache_o.data, global_O_vector, sizeof(MODEL_PARA_TYPE) * VECTOR_SIZE);
}