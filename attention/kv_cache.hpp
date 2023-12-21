#ifndef __KV_CACHE_H
#define __KV_CACHE_H

#include "vector.hpp"

template <typename Type>
class kv_cache
{
public:
    vector<Type> k_cache[NUM_HEAD][MAX_SEQ_LEN];
    vector<Type> v_cache[NUM_HEAD][MAX_SEQ_LEN];
    kv_cache(Type elem = 1)
    {
        for (int i = 0; i < NUM_HEAD; i++)
        {
            for (int j = 0; j < MAX_SEQ_LEN; j++)
            {
                k_cache[i][j] = vector<Type>(elem);
                v_cache[i][j] = vector<Type>(elem);
            }
        }
    }
    ~kv_cache() {}
};

#endif