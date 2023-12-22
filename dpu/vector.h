#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdint.h>
#include <mram.h>
#include <stdio.h>
#include "../model/model.h"

#define VECTOR_SIZE DIM_HEAD
typedef __mram_ptr MODEL_PARA_TYPE *vector_dpu_ptr;

typedef struct _vector
{
    MODEL_PARA_TYPE data[VECTOR_SIZE];
} vector;

typedef struct _A_vector
{
    MODEL_PARA_TYPE data[MAX_SEQ_LEN];
} A_vector;

typedef __dma_aligned struct _vector_cache
{
    MODEL_PARA_TYPE data[VECTOR_SIZE];
} vector_cache;

void vector_init(vector_dpu_ptr v, MODEL_PARA_TYPE default_elem);
MODEL_PARA_TYPE vector_dot(vector_dpu_ptr a, vector_dpu_ptr b);
void vector_add(vector_dpu_ptr a, vector_dpu_ptr b, MODEL_PARA_TYPE k);
void vector_dump(vector_dpu_ptr a);

void vector_load(vector_cache *vc, vector_dpu_ptr v);
void vector_store(vector_cache *vc, vector_dpu_ptr v);
void vector_cache_init(vector_cache *vc, MODEL_PARA_TYPE default_elem);
MODEL_PARA_TYPE vector_cache_dot(vector_cache *vca,vector_cache *vcb);
void vector_cache_add(vector_cache *vca,vector_cache *vcb, MODEL_PARA_TYPE k);

#endif