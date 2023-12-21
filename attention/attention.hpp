#ifndef __ATTENTION_H
#define __ATTENTION_H

#include "token.hpp"
#include "kv_cache.hpp"

template <typename Type>
void multi_head_attention(token<Type> &q, kv_cache<Type> &kv, token<Type> &ans)
{
    Type score[MAX_SEQ_LEN];

    for (int i = 0; i < NUM_HEAD; i++)
    {
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