#include "vector.h"

vector *vector_create()
{
    vector *v = malloc(sizeof(vector));
    return v;
}

void vector_init(vector *v, int32_t dft)
{
    for (int i = 0; i < DIM_HEAD; i++)
    {
        v->data[i] = dft;
    }
}

int32_t vector_dot(vector *a, vector *b)
{
    int32_t score = 0;
    for (int i = 0; i < DIM_HEAD; i++)
    {
        score += a->data[i] * b->data[i];
    }
    return score;
}

void vector_add(vector *a, vector *b, int32_t k)
{
    for (int i = 0; i < DIM_HEAD; i++)
    {
        a->data[i] = k * b->data[i];
    }
}

void vector_dump(vector *v)
{
    for (int i = 0; i < DIM_HEAD; i++)
    {
        printf("%d ", v->data[i]);
    }
    printf("\n");
}