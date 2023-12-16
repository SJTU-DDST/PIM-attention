#include "token.h"

query *query_create()
{
    query *q = malloc(sizeof(query));
    return q;
}
void query_init(query *q)
{
    for (int i = 0; i < NUM_HEAD; i++)
    {
        vector_init(&(q->vectors[i]), 1);
    }
}

answer *answer_create()
{
    answer *ans = malloc(sizeof(query));
    return ans;
}
void answer_init(answer *ans)
{
    for (int i = 0; i < NUM_HEAD; i++)
    {
        vector_init(&(ans->vectors[i]), 1);
    }
}