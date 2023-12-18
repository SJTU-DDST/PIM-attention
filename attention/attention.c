#include "attention.h"

void multi_head_attention(query *q, kv_cache *kv, answer *ans)
{
    int32_t score[MAX_SEQ_LEN];
    vector *head_ans;

    answer_init(ans);
    for (int i = 0; i < NUM_HEAD; i++)
    {
        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            score[j] = vector_dot(&(q->vectors[i]), &(kv->k_cache[i][j]));
        }

        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            score[j] /= DIM_HEAD;
        }

        head_ans = &(ans->vectors[i]);
        for (int j = 0; j < MAX_SEQ_LEN; j++)
        {
            vector_add(head_ans, &(kv->v_cache[i][j]), score[j]);
        }
    }
}
