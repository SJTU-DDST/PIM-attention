#include "op_norm.h"

void op_norm_run()
{
    uint32_t slave_tasklet_id = me() - 1;
    __dma_aligned MODEL_PARA_TYPE buffer_A[PROCESS_GRAIN_SIZE];

    for (int i = slave_tasklet_id * PROCESS_GRAIN_SIZE; i < MAX_SEQ_LEN; i += PROCESS_GRAIN_SIZE * NR_SLAVE_TASKLETS)
    {
        mram_read(gloal_A_vetor.data + i, buffer_A, sizeof(MODEL_PARA_TYPE) * PROCESS_GRAIN_SIZE);
        for (int j = 0; j < PROCESS_GRAIN_SIZE; j++)
        {
            buffer_A[j] /= DIM_HEAD;
        }
        mram_write(buffer_A, gloal_A_vetor.data + i, sizeof(MODEL_PARA_TYPE) * PROCESS_GRAIN_SIZE);
    }
}