#include "op_k.h"

void op_k_run()
{
    uint32_t slave_tasklet_id = me() - 1;
    vector_cache cache_q, cache_v;
    vector_dpu_ptr v;
    __dma_aligned MODEL_PARA_TYPE buffer_A[PROCESS_GRAIN_SIZE];

    vector_load(&cache_q, global_Q_vector);
    for (int i = slave_tasklet_id * PROCESS_GRAIN_SIZE; i < MAX_SEQ_LEN; i += PROCESS_GRAIN_SIZE * NR_SLAVE_TASKLETS)
    {
        for (int j = 0; j < PROCESS_GRAIN_SIZE; j++)
        {
            int k = i + j;
            v = kv_cache_get_kth_k_vector(global_KV_cache, k);
            if (k < MAX_SEQ_LEN)
            {
                vector_load(&cache_v, v);
                buffer_A[j] = vector_cache_dot(&cache_q, &cache_v);
            }
        }
        mram_write(buffer_A, gloal_A_vetor.data + i, sizeof(MODEL_PARA_TYPE) * PROCESS_GRAIN_SIZE);
    }
}