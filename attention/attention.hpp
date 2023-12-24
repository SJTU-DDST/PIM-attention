#ifndef __ATTENTION_H
#define __ATTENTION_H

#include "token.hpp"
#include "kv_cache.hpp"
#include <omp.h>

template <typename Type>
void multi_head_attention(token<Type> &q, kv_cache<Type> &kv, token<Type> &ans)
{
    #pragma omp parallel for num_threads(NUM_CPU_THREAD)
    for (int i = 0; i < NUM_HEAD; i++)
    {
        Type score[MAX_SEQ_LEN];
        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            score[j] = q.vectors[i] * kv.k_cache[i][j];
        }

        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            score[j] /= DIM_HEAD;
        }

        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            ans.vectors[i].vector_copy_add(kv.v_cache[i][j], score[j]);
        }
    }
}

#endif