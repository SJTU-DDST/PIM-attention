#ifndef __TOKEN_H
#define __TOKEN_H

#include "vector.h"

typedef struct _query
{
    vector vectors[NUM_HEAD];
} query;

typedef query answer;

query *query_create();
void query_init(query *q);

answer *answer_create();
void answer_init(answer *ans);

#endif