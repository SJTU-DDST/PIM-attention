#ifndef __ATTENTION_H
#define __ATTENTION_H

#include "token.h"
#include "kv_cache.h"

void multi_head_attention(query* q, kv_cache* kv, answer* ans);

#endif