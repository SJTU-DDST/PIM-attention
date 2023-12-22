#include "vector.h"

#define VECTOR_BUFFER_SIZE 32

void vector_init(vector_dpu_ptr v, MODEL_PARA_TYPE default_elem)
{
    __dma_aligned MODEL_PARA_TYPE buffer[VECTOR_BUFFER_SIZE] = {default_elem};
    for (int i = 0; i < VECTOR_SIZE; i += VECTOR_BUFFER_SIZE)
    {
        mram_write(buffer, v + i, sizeof(MODEL_PARA_TYPE) * VECTOR_BUFFER_SIZE);
    }
}

MODEL_PARA_TYPE vector_dot(vector_dpu_ptr a, vector_dpu_ptr b)
{
    MODEL_PARA_TYPE score = 0;
    __dma_aligned MODEL_PARA_TYPE buffer_a[VECTOR_BUFFER_SIZE];
    __dma_aligned MODEL_PARA_TYPE buffer_b[VECTOR_BUFFER_SIZE];

    for (int i = 0; i < VECTOR_SIZE; i += VECTOR_BUFFER_SIZE)
    {
        mram_read(a + i, buffer_a, sizeof(MODEL_PARA_TYPE) * VECTOR_BUFFER_SIZE);
        mram_read(b + i, buffer_b, sizeof(MODEL_PARA_TYPE) * VECTOR_BUFFER_SIZE);
        for (int j = 0; j < VECTOR_BUFFER_SIZE; j++)
        {
            score += buffer_a[j] * buffer_b[j];
        }
    }

    return score;
}

void vector_add(vector_dpu_ptr a, vector_dpu_ptr b, MODEL_PARA_TYPE k)
{
    __dma_aligned MODEL_PARA_TYPE buffer_a[VECTOR_BUFFER_SIZE];
    __dma_aligned MODEL_PARA_TYPE buffer_b[VECTOR_BUFFER_SIZE];

    for (int i = 0; i < VECTOR_SIZE; i += VECTOR_BUFFER_SIZE)
    {
        mram_read(a + i, buffer_a, sizeof(MODEL_PARA_TYPE) * VECTOR_BUFFER_SIZE);
        mram_read(b + i, buffer_b, sizeof(MODEL_PARA_TYPE) * VECTOR_BUFFER_SIZE);
        for (int j = 0; j < VECTOR_BUFFER_SIZE; j++)
        {
            buffer_a[j] += k * buffer_b[j];
        }
        mram_write(buffer_a, a + i, sizeof(MODEL_PARA_TYPE) * VECTOR_BUFFER_SIZE);
    }
}

void vector_dump(vector_dpu_ptr a)
{
    vector_cache cache;
    vector_load(&cache, a);
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        printf("%d ", cache.data[i]);
    }
    printf("\n");
}

void vector_load(vector_cache *vc, vector_dpu_ptr v)
{
    mram_read(v, vc->data, sizeof(MODEL_PARA_TYPE) * VECTOR_SIZE);
}

void vector_store(vector_cache *vc, vector_dpu_ptr v)
{
    mram_write(vc->data, v, sizeof(MODEL_PARA_TYPE) * VECTOR_SIZE);
}

void vector_cache_init(vector_cache *vc, MODEL_PARA_TYPE default_elem)
{
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        vc->data[i] = default_elem;
    }
}

MODEL_PARA_TYPE vector_cache_dot(vector_cache *vca, vector_cache *vcb)
{
    MODEL_PARA_TYPE score = 0;
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        score += vca->data[i] * vcb->data[i];
    }
    return score;
}

void vector_cache_add(vector_cache *vca, vector_cache *vcb, MODEL_PARA_TYPE k)
{
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        vca->data[i] += k * vcb->data[i];
    }
}