#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdint.h>
#include "../model/model.h"
#include <malloc.h>

typedef struct _vector
{
    int32_t data[DIM_HEAD];
} vector;

vector *vector_create();
void vector_init(vector *v, int32_t dft);
int32_t vector_dot(vector *a, vector *b);
void vector_add(vector *a, vector *b, int32_t k);
void vector_dump(vector* v);

#endif