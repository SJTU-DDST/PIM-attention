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

int main()
{
    int64_t begin, last;
    query *q = query_create();
    query_init(q);
    kv_cache *kv = kv_cache_create();
    kv_cache_init(kv);
    answer *ans = answer_create();

    kv_cache *fuse = kv_cache_create();
    kv_cache_init(fuse);
    begin = usec();
    multi_head_attention(q, kv, ans);
    last = usec();
    // for (int i = 0; i < NUM_HEAD; i++)
    // {
    //     vector_dump(&(ans->vectors[i]));
    // }
    printf("multi_head_attention elapse time: %ld\n", last - begin);
    return 0;
}